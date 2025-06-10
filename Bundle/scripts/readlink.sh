#!/bin/sh

readlink()
{
	local target=${1}

	cd `dirname ${target}`
	target=`basename ${target}`

	# Iterate down a (possible) chain of symlinks
	while [ -L "${target}" ]; do
		target=`readlink ${target}`
		cd `dirname ${target}`
		target=`basename ${target}`
	done

	# Compute the canonicalized name by finding the physical path
	# for the directory we're in and appending the target file.
	local directory=`pwd -P`
	local result=${directory}/${target}
	echo ${result}
}
