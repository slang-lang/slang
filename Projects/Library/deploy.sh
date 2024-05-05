#!/bin/bash

if [ x$1 == "x" ]; then
	echo "module name required"
	exit -1
else
	slang-pkg create $1
fi

REPO="stable"
if [ x$2 != "x" ]; then
	REPO="$2"
fi

scp *.json strato1:/home/madelmann/projects/slang-lang.org/repo/${REPO}/modules/
rm *.json

scp *.tar.gz strato1:/home/madelmann/projects/slang-lang.org/repo/${REPO}/modules/
rm *.tar.gz

