#!/bin/bash

if [ "$(head -n 1 README.md)" != "# git-gud" ]; then
  echo "ERROR! Run build script from the git-gud project root!"
fi

refresh_emcc() {
  echo "Adding emcc to PATH"
  if [ -f ./emsdk/emsdk_env.sh ]; then
    . ./emsdk/emsdk_env.sh >/dev/null 2>&1
  else
    return 1
  fi
}

install_emcc() {
  refresh_emcc && return 0
  echo "Failed to reload emsdk, so we need to reinstall"
  echo "Downloading..."
  git clone https://github.com/emscripten-core/emsdk.git >/dev/null 2>&1
  cd emsdk
  echo "Installing [1/3]..."
  git pull >/dev/null 2>&1
  echo "Installing [2/3]... (may take a while)"
  ./emsdk install latest >/dev/null 2>&1
  echo "Installing [3/3]..."
  ./emsdk activate latest >/dev/null 2>&1
  cd ..
  refresh_emcc
}

refresh_wabt() {
  echo "Adding wasm2wat to PATH"
  if [ -d ./wabt ]; then
    export PATH="$(pwd)/wabt/build:$PATH"
    return 0
  else
    return 1
  fi
}

install_wabt() {
  refresh_wabt && return 0
  cmake --version || echo "You need CMake to install wabt! Talk to Nic."
  echo "Failed to reload wabt, so we need to reinstall"
  echo "Downloading..."
  git clone --recursive https://github.com/WebAssembly/wabt >/dev/null 2>&1
  cd wabt
  mkdir build
  cd build
  echo "Building [1/2]..."
  cmake .. >/dev/null 2>&1
  echo "Building [2/2]... (may take a while)"
  make wasm2wat >/dev/null 2>&1
  cd ..
  refresh_wabt
}

echo "Checking if EMCC needs to be installed"
emcc --version >/dev/null 2>&1
echo ret $?
emcc --version >/dev/null 2>&1 || install_emcc

echo Compiling src/*.cpp to docs/hello.wasm
emcc src/*.cpp -O3 -o docs/hello.wasm -s WASM=1 --js-library src/lib.js >/dev/null

echo "Checking if WABT needs to be installed"
wasm2wat --help >/dev/null 2>&1
echo ret $?
wasm2wat --help >/dev/null 2>&1 || install_wabt

echo Generating WASM text representation
wasm2wat docs/hello.wasm > docs/hello.wat

echo "Compilation done!"
