
EXCLUDE=*.sh
RELEASE="ObjectiveScript-`cat version`_`svnversion`.tar.gz"

echo "Packing files for release ${RELEASE} ..."

tar cfvz ${RELEASE} --exclude=${EXCLUDE} *

echo "done."

