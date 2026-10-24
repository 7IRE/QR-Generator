// src/wasm_bindings.cpp
#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#include <string>
#include <vector>
#include "QR_Generator.hpp"

struct QRResult {
    int size;
    std::vector<int> data;
};

QRResult generate(const std::string& text, int correctionLevel) {
    if (correctionLevel < 0 || correctionLevel > 3) correctionLevel = 0;

    QR_Generator qr;
    auto matrix = qr.GenerateQR(text, correctionLevel);

    QRResult r;
    r.size = static_cast<int>(matrix.size());
    r.data.reserve(r.size * r.size);
    for (const auto& row : matrix) {
        for (int v : row) {
            r.data.push_back(v);
        }
    }
    return r;
}

EMSCRIPTEN_BINDINGS(qr_module) {
    emscripten::register_vector<int>("VectorInt");
    emscripten::value_object<QRResult>("QRResult")
        .field("size", &QRResult::size)
        .field("data", &QRResult::data);
    emscripten::function("generate", &generate);
}
#endif // __EMSCRIPTEN__