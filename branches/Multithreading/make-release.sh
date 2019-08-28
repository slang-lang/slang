#!/bin/bash

EXCLUDES="--exclude=.* --exclude=cmake-build* --exclude=make-package.cfg"
RELEASE="ObjectiveScript-$(cat version)_$(svnversion).tar.gz"

echo "Packing files for release ${RELEASE} ..."

# shellcheck disable=SC2086
tar cfvz "${RELEASE}" ${EXCLUDES} -- *

echo ""
echo "Uploading files..."

scp "${RELEASE}" README.txt madelmann@frs.sourceforge.net:/home/frs/project/objectivescript/

echo ""
echo "Cleanup..."

rm "${RELEASE}"

echo ""
echo "done."

