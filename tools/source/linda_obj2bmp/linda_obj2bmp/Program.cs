using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace linda_obj2bmp
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] files = Directory.GetFiles("bins", "*.D.OBJ", SearchOption.AllDirectories);
            foreach (string filename in files)
            {
                BinaryReader obj = new BinaryReader(File.OpenRead(filename));

                uint extraDataStart = obj.ReadUInt32();
                uint unkPtrsCnt = obj.ReadUInt32();

                List<uint> unkPtrs = new List<uint>();
                for (int i = 0; i < unkPtrsCnt; i++)
                {
                    unkPtrs.Add(obj.ReadUInt32());
                }

                uint paletteDataCnt = obj.ReadUInt32();

                List<ushort> paletteData = new List<ushort>();
                for (int i = 0; i < paletteDataCnt; i++)
                {
                    paletteData.Add(obj.ReadUInt16());
                }

                long dataPos = obj.BaseStream.Position;

                obj.BaseStream.Seek(extraDataStart, SeekOrigin.Begin);

                int w = obj.ReadUInt16();
                //w = w / 2;

                int h = obj.ReadUInt16();

                obj.BaseStream.Seek(dataPos, SeekOrigin.Begin);

                Bitmap bmp = new Bitmap(w, h);
                int r, g, b;
                for (int y = 0; y < h; y++)
                {
                    for (int x = 0; x < w; x++)
                    {
                        byte pixel = obj.ReadByte();


                        if (pixel != 0)
                        {
                            int boopme = 0;
                        }
                        r = (paletteData[pixel] & 0x1f) * 0x05;
                        g = ((paletteData[pixel] & 0x3e0) >> 5) * 0x05;
                        b = ((paletteData[pixel] & 0x7C00) >> 10) * 0x05;
                        Color c = Color.FromArgb(r, g, b);
                        bmp.SetPixel(x, y, c);

                    }
                }
                bmp.Save(filename + ".bmp", ImageFormat.Bmp);

                obj.Close();
            }
        }
    }
}