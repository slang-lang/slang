#!/bin/bash

if [ x$1 == "x" ]; then
	echo "module name required"
	exit -1
else
	odepend create $1
fi

REPO="stable"
if [ x$2 != "x" ]; then
	REPO="$2"
fi

scp *.json ticketsharing:/home/ubuntu/projects/objectivescript/repo/${REPO}/modules/
rm *.json

scp *.tar.gz ticketsharing:/home/ubuntu/projects/objectivescript/repo/${REPO}/modules/
rm *.tar.gz
