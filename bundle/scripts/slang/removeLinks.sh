#!/bin/bash

source /usr/lib/slang/scripts/realpath.sh

a=".slang/apps"   # Where symlinks live (e.g. /usr/local/bin)
b="$1"            # Directory you want to remove (e.g. /opt/mytool)

# Resolve absolute path of a and b (in case it’s a relative path)
#a=$(realpath "$a")
a=$(readlink -f "$a")
#b=$(realpath "$b")
b=$(readlink -f "$b")

if [ ! -d "$a" ] || [ ! -d "$b" ]; then
    echo "Usage: $0 <link_dir> <target_dir>"
    echo "Both arguments must be directories."
    exit 1
fi

#echo "Scanning for symlinks in '$a' pointing to anywhere inside '$b'..."

find "$a" -type l | while read -r link; do
    target=$(realpath "$link" 2>/dev/null)
    if [ -n "$target" ] && [[ "$target" == "$b"* ]]; then
        echo "Removing symlink $link -> $target"
        rm "${link}"
    fi
done
