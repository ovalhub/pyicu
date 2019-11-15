#! /bin/bash

# Fail on first non-successful command, and print out what it is doing.
set -ex

INSTALL_DIR="$HOME/icu4c"
BUILD_DIR="$HOME/build"

# Require an argument to pass to runConfigureICU
platform="${1?}"
version="${ICU_VERSION?}"
cache_tag="${INSTALL_DIR}/icu4c-${TRAVIS_OS_NAME?}-${version}.done"

# Installs icu4c on linux from source
ICU_URL="https://github.com/unicode-org/icu/releases/download/release-${version/./-}/icu4c-${version/./_}-src.tgz"

# If the INSTALL_DIR already exists, then it was cached and we do not need to rebuild.
if [ -f "${cache_tag}" ]
then
    echo "Found cached icu4c in ${INSTALL_DIR}, skipping build!"
    exit 0
fi

# Fetch
mkdir -p "${BUILD_DIR}"
wget -nv -O "${BUILD_DIR}/icu4c.tgz" "${ICU_URL}"

# Extract
tar -xzf "${BUILD_DIR}/icu4c.tgz" -C "${BUILD_DIR}"

# Configure/build
cd "${BUILD_DIR}/icu/source"
./runConfigureICU "${platform}" --prefix="${INSTALL_DIR}"
make

# Install
make install

# Add a tag to the installation directory to validate the cache
touch "${cache_tag}"
