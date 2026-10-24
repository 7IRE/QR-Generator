#!/bin/bash
set -e

echo "--- Installing Emscripten SDK ---"
if [ ! -d "/vercel/cache/emsdk" ]; then
  git clone https://github.com/emscripten-core/emsdk.git /vercel/cache/emsdk
fi
cd /vercel/cache/emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh

echo "--- Compiling C++ to WebAssembly ---"
cd "$VERCEL_PROJECT_DIRECTORY"

em++ \
  src/wasm_bindings.cpp src/QR_Generator.cpp \
  -Iinclude \
  -O3 \
  -std=c++17 \
  -lembind \
  -s MODULARIZE=1 \
  -s EXPORT_NAME="createQRModule" \
  -s ENVIRONMENT=node \
  -s ALLOW_MEMORY_GROWTH=1 \
  -o src/qr_module.js

echo "--- Build complete ---"