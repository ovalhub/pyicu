#! /bin/bash

# Fail on first non-successful command
set -e

#######
# Tools

# Grab the ICU source from the web then extract.
# Parameters:
#  version: ICU version to download
#  location: Directory to place the source and to extract the contents.
function fetch_icu {
    echo "Downloading and extracting ICU source..."
    local version="${1?}"
    local location="${2?}"
    local icu_url="https://github.com/unicode-org/icu/releases/download/release-${version/./-}/icu4c-${version/./_}-src.tgz"
    mkdir -p "${location}"
    wget -nv -O "${location}/icu4c.tgz" "${icu_url}"
    tar -xzf "${location}/icu4c.tgz" -C "${location}"
}

# Grab Python from the web then install
# Handles using a cached version if available
# Parameters:
#  version: Python version to install
function install_python_osx {
    echo "Installing Python version ${1?} using pyenv..."
    wget https://github.com/praekeltfoundation/travis-pyenv/releases/download/0.4.0/setup-pyenv.sh
    # shellcheck disable=SC1091
    PYENV_VERSION="${1}" PYENV_VERSION_STRING="Python ${1}" source setup-pyenv.sh
}

#############
# Environment

# Installation and build locations. Not the same so that we don't
# make the cache huge by storing source and build artifacts.
install_dir="$HOME/icu4c"
build_dir="$HOME/build"

# This will be used to uniquely determine if the correct cache is found or not.
cache_tag="${install_dir}/icu4c-${TRAVIS_OS_NAME?}-${ICU_VERSION}.done"

# The platform is used by runConfigureICU to determine what flags to set.
case "${TRAVIS_OS_NAME}" in
    osx) platform=MacOSX;;
    windows) platform=MSYS/MSVC ;;
    *) platform=Linux ;;
esac

# Map Travis python version to a full major.minor.patch version
if [ "${platform}" = Linux ]
then
    pyver="${TRAVIS_PYTHON_VERSION}"
else
    case "${TRAVIS_PYTHON_VERSION}" in
        2.7) pyver=2.7.17;;
        3.5) pyver=3.5.8;;
        3.6) pyver=3.6.9;;
        3.7) pyver=3.7.4;;
        *)
            if [ "${TRAVIS_PYTHON_VERSION}" != "3.8" ]
            then
                echo "Python version ${TRAVIS_PYTHON_VERSION} unset/unknown. Using default."
            fi
            pyver=3.8.0
            ;;
    esac
fi

echo "ICU environment information..."
echo "INSTALLATION DIRECTORY: ${install_dir}"
echo "BUILD DIRECTORY: ${build_dir}"
echo "PYTHON VERSION: ${pyver}"
echo "PLATFORM: ${platform}"
echo "ICU VERSION: ${ICU_VERSION}"

#######
# Logic

# Need to install Python macos (annoyingly).
if [ "${TRAVIS_OS_NAME}" = osx ]
then
    install_python_osx "${pyver}"
fi

# If the install_dir already exists, then it was cached and we do not need to rebuild.
if [ -f "${cache_tag}" ]
then
    echo "Found cached icu4c in ${install_dir}, skipping build!"
else
    # Grab the source, build, then install.
    fetch_icu "${ICU_VERSION}" "${build_dir}"
    cd "${build_dir}/icu/source"
    echo "Build and install ICU from source..."
    ./runConfigureICU "${platform}" --prefix="${install_dir}"
    make
    make install

    # Add a tag to the installation directory to validate the cache
    touch "${cache_tag}"
fi

##############
# Confirmation

echo "Displaying ICU build information as confirmation..."
export PATH="$HOME/icu4c/bin:${PATH}"
export LD_LIBRARY_PATH="$HOME/icu4c/lib"
export DYLD_LIBRARY_PATH="$HOME/icu4c/lib"
echo "which icuinfo: $(command -v icuinfo)"
echo "which icu-config: $(command -v icu-config)"
echo "icuinfo -v:"
icuinfo -v
echo "icu-config --version: $(icu-config --version)"
echo "icu-config --cxxflags: $(icu-config --cxxflags)"
echo "icu-config --cppflags: $(icu-config --cppflags)"
