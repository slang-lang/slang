#!/bin/bash

EXCLUDES="--exclude=*.sh --exclude=cmake-build*"
RELEASE="ObjectiveScript-`cat version`_`svnversion`.tar.gz"

echo "Packing files for release ${RELEASE} ..."

tar cfvz ${RELEASE} ${EXCLUDES} *

echo ""
echo "Uploading files..."

scp ${RELEASE} README.txt madelmann@frs.sourceforge.net:/home/frs/project/objectivescript/

echo ""
echo "Cleanup..."

rm ${RELEASE}

echo ""
echo "done."
