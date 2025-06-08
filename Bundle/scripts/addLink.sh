#!/bin/bash

source /var/lib/slang/scripts/readlink.sh

a="$1"   # Source of symlink (e.g. Library/JsonReader/JsonReader.slang)
b="$2"   # Where symlinks live (e.g. Library/.slang/apps/JsonReader.slang)

# Resolve absolute path of a and b (in case it’s a relative path)
a=$(readlink "$a")
b=$(readlink "$b")

echo "Installing symlink $a -> $b"
ln -sf "$a" "$b"    # override existing symlinks
#ln -s "$a" "$b"     # fail if a link already exists

