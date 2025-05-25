#!/bin/bash

source .slang/scripts/realpath.sh

a="$1"            # Directory you want to remove (e.g. /opt/mytool)
b=".slang/apps"   # Where symlinks live (e.g. /usr/local/bin)

# Resolve absolute path of a and b (in case it’s a relative path)
#a=$(realpath "$a")
#a=$(readlink -f "$a")
a=$(realpath "$a")
#b=$(realpath "$b")
#b=$(readlink -f "$b")
b=$(realpath "$b")

echo "Installing symlink $a -> $b"
#ln -sf "$a" "$b"
ln -s "$a" "$b"     # fail if a link already exists

