using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace linda_obj_decompress
{
    class Program
    {
        static int Decompress(MemoryStream source, MemoryStream dest, int decompLen)
        {
            uint isComp;
            int flagIdx = 0;
            uint flags = 0;

            do
            {
                while (true)
                {
                    if (source.Length - source.Position < 1)
                    {
                        return 0;
                    }
                    if (flagIdx == 0)
                    {
                        flags = (uint)source.ReadByte();
                        flagIdx = 8;
                    }
                    flagIdx--;
                    isComp = flags & 1;
                    flags = flags >> 1;

                    if (isComp == 0) break;

                    dest.WriteByte((byte)source.ReadByte());
                    decompLen--;
                }
                if (flagIdx == 0)
                {
                    flags = (uint)source.ReadByte();
                    flagIdx = 8;
                }
                
                flagIdx--;
                isComp = flags & 1;
                flags = flags >> 1;


                int run = 0;
                int offset = 0;
                if (isComp == 0)
                {
                    uint temp = (uint)(source.ReadByte() << 8 | source.ReadByte());
                    run = (int)(temp >> 0x0C);
                    offset = (int)(temp | 0xFFFFF000);
                    if (run == 0)
                    {
                        run = source.ReadByte();
                        if (run == 0)
                            return 0;
                    }
                }
                else
                {
                    uint temp = (uint)source.ReadByte();
                    run = (int)(temp >> 6);
                    offset = (int)(temp | 0xffffffc0);
                }

                run = run + 2;
                for (; run != 0; run--)
                {
                    dest.Seek(offset, SeekOrigin.End);
                    byte backByte = (byte)dest.ReadByte();

                    dest.Seek(0, SeekOrigin.End);
                    dest.WriteByte(backByte);
                }

            } while (true);
        }

        static void Main(string[] args)
        {
            MemoryStream source = new MemoryStream(File.ReadAllBytes("OPEN1.OBJ"));
            MemoryStream dest = new MemoryStream();

            byte[] decompLengthBytes = new byte[4];
            byte[] compLengthBytes = new byte[4];
            source.Read(decompLengthBytes, 0, 4);
            source.Read(compLengthBytes, 0, 4);

            byte[] unk1Bytes = new byte[4];
            source.Read(unk1Bytes, 0, 4);

            int decompLen = BitConverter.ToInt32(decompLengthBytes, 0);
            int compLen = BitConverter.ToInt32(compLengthBytes, 0);

            int unk1 = BitConverter.ToInt32(unk1Bytes, 0);

            Decompress(source, dest, compLen);

            if (File.Exists("OPEN1.D.OBJ"))
                File.Delete("OPEN1.D.OBJ");

            File.WriteAllBytes("OPEN1.D.OBJ", dest.ToArray());

        }
    }
}
