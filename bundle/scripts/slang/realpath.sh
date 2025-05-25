#!/bin/sh

realpath()
{
	local target=$1
	local dir
	local file

	# If no argument provided
	if [[ -z "$target" ]]; then
		echo "Usage: $0 <path>" >&2
		return 1
	fi

	# Resolve symlinks
	while [ -L "$target" ]; do
		target=$(readlink "$target")
	done

	# Absolute path resolution
	dir=$(cd -P -- "$(dirname "$target")" && pwd)
	file=$(basename "$target")
	echo "$dir/$file"
}

