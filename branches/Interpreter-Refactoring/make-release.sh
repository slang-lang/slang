
EXCLUDES="--exclude=*.sh --exclude=README.TXT"
RELEASE="ObjectiveScript-`cat version`_`svnversion`.tar.gz"

echo "Packing files for release ${RELEASE} ..."

tar cfvz ${RELEASE} ${EXCLUDES} *

echo "done."

