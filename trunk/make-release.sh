
EXCLUDES="--exclude=*.sh"
RELEASE="ObjectiveScript-`cat version`_`svnversion`.tar.gz"

echo "Packing files for release ${RELEASE} ..."

tar cfvz ${RELEASE} ${EXCLUDES} *

echo "Uploading files..."

scp ${RELEASE} README.TXT madelmann@frs.sourceforge.net:/home/frs/project/objectivescript/

echo "Cleanup..."

rm ${RELEASE}

echo "done."

