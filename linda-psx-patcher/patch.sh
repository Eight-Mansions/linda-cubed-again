#!/usr/bin/env bash
# apply_patch.sh — Bash translation of the original Linda-English patch BAT
# ----------------------------------------------------------------------
# Usage:  ./apply_patch.sh <path-to-BIN/ISO>
# (Dragging a file onto the script in most desktop environments passes its
#  path as $1, reproducing the “drag & drop” behaviour of the .bat file.)
# ----------------------------------------------------------------------

set -u                                  # abort on undefined variables

# ---------- configuration ---------------------------------------------------
filename="Linda-English"                # base name for the output
file_type="BIN"
patch_file="patch.xdelta"
patch_file_other="patch-other.xdelta"
xdelta_cmd="xdelta3"                    # CLI tool (install with: sudo apt install xdelta3)
# ---------------------------------------------------------------------------

# Work from the directory where the script itself resides (≈ pushd %~dp0)
script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$script_dir" || { echo "Cannot cd to $script_dir"; exit 1; }

# ---------------- argument / “drag-and-drop” check --------------------------
if [[ $# -lt 1 ]]; then
    cat <<EOF
To patch $file_type, don't just run this script.
Simply drag & drop the $file_type onto it, or invoke:

    $(basename "$0") /path/to/$file_type

EOF
    exit 1
fi

iso="$1"
echo "Patching $file_type …"

# ---------------- attempt first, then fallback patch ------------------------
dest_bin="${filename}.bin"

apply_patch () {
    local patch="$1"
    "$xdelta_cmd" -d -f -s "$iso" "patch_data/$patch" "$dest_bin" \
        >/dev/null 2>&1
}

if apply_patch "$patch_file"; then
    :   # first patch succeeded
elif apply_patch "$patch_file_other"; then
    :   # fallback patch succeeded
else
    cat <<EOF

Something went wrong while patching files.
You might be trying to patch the wrong $file_type; please try a different one.

EOF
    exit 1
fi

# ---------------- create minimal CUE sheet ----------------------------------
cat > "${filename}.cue" <<EOF
FILE "${filename}.bin" BINARY
  TRACK 01 MODE2/2352
    INDEX 01 00:00:00
EOF

cat <<EOF

Success!
Patched $file_type saved as ${filename}.bin and ${filename}.cue
(in the same folder as this script).

EOF


