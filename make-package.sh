#!/bin/bash

# set up essential stuff
CONFIG_FILE="make-package.cfg"
PLATFORM=$(uname -m)
VERSION=$(cat version)

# preparing config file if necessary
if [ -f ${CONFIG_FILE} ]; then
	test -f ${CONFIG_FILE} 
else
	echo "Preparing config file '${CONFIG_FILE}', please edit manually before proceeding."

	cp ${CONFIG_FILE}.tmp ${CONFIG_FILE}

	exit -1
fi

# read config file
source ${CONFIG_FILE}

if [ "x${1}" != "x" ]; then
	PLATFORM=${1}
fi

# set up environment
PACKAGE_DIRECTORY="${TARGET_DIRECTORY}/oscript-${VERSION}-${PLATFORM}"
PACKAGE_DIRECTORY_BIN="${PACKAGE_DIRECTORY}/usr/local/bin"
PACKAGE_DIRECTORY_SHARE="${PACKAGE_DIRECTORY}/usr/share/oscript"
PACKAGE_DIRECTORY_SHARED_LIBRARIES="${PACKAGE_DIRECTORY_SHARE}/libs"
PACKAGE_DIRECTORY_LIBRARY="${PACKAGE_DIRECTORY_SHARE}/Library"


echo "Building ObjectiveScript debian package version ${VERSION} for platform '${PLATFORM}'..."
echo ""

#echo "Removing old package directory."
rm -r ${PACKAGE_DIRECTORY} 2>&1

echo "Creating package directories '${PACKAGE_DIRECTORY}'."
#echo "PACKAGE_DIRECTORY='${PACKAGE_DIRECTORY}'"
#echo "PACKAGE_DIRECTORY_BIN='${PACKAGE_DIRECTORY_BIN}'"
#echo "PACKAGE_DIRECTORY_LIBRARY='${PACKAGE_DIRECTORY_LIBRARY}'"
echo ""

mkdir -p "${PACKAGE_DIRECTORY}"
mkdir -p "${PACKAGE_DIRECTORY_BIN}"
mkdir -p "${PACKAGE_DIRECTORY_SHARED_LIBRARIES}"
mkdir -p "${PACKAGE_DIRECTORY_LIBRARY}"

# copying DEBIAN base structure
cp -r Env/DEBIAN ${PACKAGE_DIRECTORY}

# add new binaries
echo "Deploying new binaries..."
cp ${SOURCE_DIRECTORY}/bin/odebugger/odebugger ${PACKAGE_DIRECTORY_BIN}
cp ${SOURCE_DIRECTORY}/bin/odepend/odepend ${PACKAGE_DIRECTORY_BIN}
cp ${SOURCE_DIRECTORY}/bin/oscript/oscript ${PACKAGE_DIRECTORY_BIN}

# add new libraries
echo "Deploying new libraries..."
cp -r Projects/Library/.odepend ${PACKAGE_DIRECTORY_LIBRARY}
cp -r Projects/Library/deploy.sh ${PACKAGE_DIRECTORY_LIBRARY}
cp -r Projects/Library/ObjectiveScript ${PACKAGE_DIRECTORY_LIBRARY}
cp -r Projects/Library/System ${PACKAGE_DIRECTORY_LIBRARY}

# add new shared libraries
echo "Deploying new shared libraries..."
cp ${EXTENSIONS_DIRECTORY}/lib/* ${PACKAGE_DIRECTORY_SHARED_LIBRARIES}
# remove MySQL extension since it is still statically linked into oscript
rm ${PACKAGE_DIRECTORY_SHARED_LIBRARIES}/libObjectiveScriptMysql*

echo ""
echo "Building package..."
dpkg-deb --build ${PACKAGE_DIRECTORY} > /dev/null

echo "Done."

