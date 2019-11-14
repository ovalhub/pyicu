#! /bin/bash

# Fail on first non-successful command, and print out what it is doing.
set -ex

# Require an argument to pass to runConfigureICU
platform="${1?}"

# Installs icu4c on linux from source
# Requires that the environment variable ICU_VERSION is set.
ICU_URL="https://github.com/unicode-org/icu/releases/download/release-${ICU_VERSION/./-}/icu4c-${ICU_VERSION/./_}-src.tgz"

# install ICU4C from source
mkdir -p "/tmp/icu4c"
wget -nv -O "/tmp/icu4c/icu4c.tgz" "${ICU_URL}"
tar -xzf "/tmp/icu4c/icu4c.tgz" -C "/tmp/icu4c"
cd "/tmp/icu4c/icu/source"
./runConfigureICU "${platform}" --prefix="/tmp/icu4c"
make
make install
