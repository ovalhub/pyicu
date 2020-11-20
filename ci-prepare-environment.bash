#! /bin/bash

# Fail on first non-successful command
set -e
# set -x  # turn on for debugging

case "$OSTYPE" in
  darwin*)  OS=osx ;; 
  linux*)   OS=linux ;;
  msys*)    OS=windows ;;
  *)        OS="unknown: $OSTYPE" ;;
esac

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

    # Download the source as zip on Windows and tgz otherwise
    if [ "${version%rc}" = "${version}" ]
    then
        local icu_url="https://github.com/unicode-org/icu/releases/download/release-${version/./-}/icu4c-${version/./_}-src.tgz"
    else
        local icu_url="https://github.com/unicode-org/icu/releases/download/release-${version/rc/-rc}/icu4c-${version}-src.tgz"
    fi
    if [ "${OS}" = windows ]; then icu_url="${icu_url%.tgz}.zip"; fi
    local src="${location}/${icu_url##*/}"

    # Download, then use different extraction tools on Windows vs. otherwise
    mkdir -p "${location}"
    wget -nv -O "${src}" "${icu_url}"
    if [ "${OS?}" = windows ]
    then
        7z x "${src}" -o"${location}"
    else
        tar -xzf "${src}" -C "${location}"
    fi
}

# Grab Python from the web then install on OSX
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
cache_tag="${install_dir}/icu4c-${OS?}-${ICU_VERSION}.done"

# The platform is used by runConfigureICU to determine what flags to set.
case "${OS}" in
    osx) platform=MacOSX;;
    windows) platform=Cygwin/MSVC ;;
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
        3.8) pyver=3.8.6;;
        *)
            if [ "${TRAVIS_PYTHON_VERSION}" != "3.9" ]
            then
                echo "Python version ${TRAVIS_PYTHON_VERSION} unset/unknown. Using default."
            fi
            pyver=3.9.0
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

# Need to install Python on macos and windows (annoyingly).
case "${OS}" in
    osx)
        install_python_osx "${pyver}";;
    windows)
        choco install python --version "${pyver}";;
esac

# If the install_dir already exists, then it was cached and we do not need to rebuild.
if [ -f "${cache_tag}" ]
then
    echo "Found cached icu4c in ${install_dir}, skipping build!"
else
    echo "Build and install ICU from source..."
    fetch_icu "${ICU_VERSION}" "${build_dir}"

    if [ "${OS}" = windows ]
    then
        # XXX: As-is, this seems to be broken and does not work.
        # It is unknown to me how to solve this at this time.
        # Good luck future maintainer.
        cd "${build_dir}/icu"
        PATH="/c/Program Files (x86)/Microsoft Visual Studio/2017/BuildTools/MSBuild/15.0/Bin:$PATH"
        MSBuild.exe source/allinone/allinone.sln -p:Configuration=Release -p:Platform=x64 -p:SkipUWP=true
        mkdir "${install_dir}"
        mv bin64 "${install_dir}/bin"
        mv lib64 "${install_dir}/lib"
        mv include "${install_dir}/include"
    else
        cd "${build_dir}/icu/source"
        ./runConfigureICU "${platform}" --prefix="${install_dir}"
        make
        make install
    fi

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
