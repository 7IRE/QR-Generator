#!/bin/bash
    set -e
    
    # 1. Save the repository root directory
    ROOT_DIR="$(pwd)"
    EMSDK_DIR="/tmp/emsdk"

    echo "--- Installing Emscripten SDK ---"
    # 2. Use /tmp (guaranteed writable) and shallow clone for fast download
    if [ ! -d "$EMSDK_DIR" ]; then
      git clone --depth 1 https://github.com/emscripten-core/emsdk.git "$EMSDK_DIR"
    fi

    cd "$EMSDK_DIR"
    ./emsdk install latest
    ./emsdk activate latest
    source ./emsdk_env.sh

    echo "--- Compiling C++ to WebAssembly ---"
    # 3. Return to the actual project root directory
    cd "$ROOT_DIR"

    # 4. Compile with ES6 export and embedded Wasm binary
    em++ \
      src/wasm_bindings.cpp src/QR_Generator.cpp \
      -Iinclude \
      -O3 \
      -std=c++17 \
      -lembind \
      -s MODULARIZE=1 \
      -s EXPORT_NAME="createQRModule" \
      -s EXPORT_ES6=1 \
      -s SINGLE_FILE=1 \
      -s ENVIRONMENT=node \
      -s ALLOW_MEMORY_GROWTH=1 \
      -o src/qr_module.js

    echo "--- Build complete ---"
