#!/bin/bash

# set up essential stuff
CONFIG_FILE="make-package.cfg"
PLATFORM=$(uname -m)
VERSION=$(cat version)

# preparing config file if necessary
if [ -f ${CONFIG_FILE} ]; then
	echo "Config exists"
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
PACKAGE_DIRECTORY_SHARE="${PACKAGE_DIRECTORY}/usr/share/oscript/Library"


echo "Building ObjectiveScript debian package version ${VERSION} for platform '${PLATFORM}'..."

echo "Creating package directories '${PACKAGE_DIRECTORY}'..."
echo "PACKAGE_DIRECTORY='${PACKAGE_DIRECTORY}'"
echo "PACKAGE_DIRECTORY_BIN='${PACKAGE_DIRECTORY_BIN}'"
echo "PACKAGE_DIRECTORY_SHARE='${PACKAGE_DIRECTORY_SHARE}'"

mkdir -p "${PACKAGE_DIRECTORY}"
mkdir -p "${PACKAGE_DIRECTORY_BIN}"
mkdir -p "${PACKAGE_DIRECTORY_SHARE}"

# copying DEBIAN base structure
cp -r Env/DEBIAN ${PACKAGE_DIRECTORY}

# remove old binaries
echo "Removing old binaries..."
rm ${PACKAGE_DIRECTORY_BIN}/odebugger
rm ${PACKAGE_DIRECTORY_BIN}/odepend
rm ${PACKAGE_DIRECTORY_BIN}/oscript

# add new binaries
echo "Deploying new binaries..."
cp ${SOURCE_DIRECTORY}/bin/odebugger/odebugger ${PACKAGE_DIRECTORY_BIN}
cp ${SOURCE_DIRECTORY}/bin/odepend/odepend ${PACKAGE_DIRECTORY_BIN}
cp ${SOURCE_DIRECTORY}/bin/oscript/oscript ${PACKAGE_DIRECTORY_BIN}

# remove old libraries
echo "Removing old libraries..."
rm -r ${PACKAGE_DIRECTORY_SHARE}/ObjectiveScript
rm -r ${PACKAGE_DIRECTORY_SHARE}/System

# add new libraries
echo "Deploying new libraries..."
cp -r Projects/Library/ObjectiveScript ${PACKAGE_DIRECTORY_SHARE}
cp -r Projects/Library/System ${PACKAGE_DIRECTORY_SHARE}

dpkg-deb --build ${PACKAGE_DIRECTORY}

echo "Done."

