# QR Code Generator (C++ & WebAssembly)

## Overview
This project is a **QR Code Generator** written in **C++17**. It features a dual deployment:
1. **Web Application:** Compiled to **WebAssembly (Wasm)** and deployed on **Vercel** with a modern web UI.
2. **Terminal Application:** Renders QR codes directly in your terminal using ANSI escape sequences.

---

## Features
- Generate QR codes from any string input.
- Supports **four error correction levels**:
  - Low (7% recovery)
  - Medium (15% recovery)
  - Quartile (25% recovery)
  - High (30% recovery)
- **Web UI:** Professional dark-mode interface with a download button.
- **100% Private:** Data is processed in-memory and never stored or shared.
- **Native Speed:** Core logic runs at native speed via WebAssembly.
- Terminal rendering using colored blocks (`ANSI escape codes`).
- Modular design with `QR_Generator` class for easy integration.
---

##  Requirements
- **C++17** or later
- **CMake ≥ 3.10**
- A terminal that supports ANSI escape sequences (Linux/macOS, or Windows with proper terminal emulator)

---

## Project Structure
QR-Generator/  
│─ api/  
│   ├── generate.js         # Vercel Serverless Function (QR generation + perf metrics)  
│   └── metrics.js          # Vercel Serverless Function (submission counters, GET only)  
│─ lib/  
│   └── vercel-kv.js       # Vercel KV / Upstash Redis counter helper (no-op when unconfigured)  
│─ public/  
│   └── index.html          # Web UI  
│─ scripts/  
│   └── build-wasm.sh      # Emscripten build script  
│─ src/  
│   ├── main.cpp           # Terminal entry point  
│   ├── QR_Generator.cpp   
│   └── wasm_bindings.cpp  # WebAssembly entry point  
│─ include/     
│   ├── QR_Generator.hpp   
│   └── includes.hpp   
│─ screenshots/  
│   └── terminal.png   
│─ CMakeLists.txt           # Terminal CMake build  
│─ vercel.json              # Vercel deployment config
│─ README.md            
│─ .gitignore            
└─ LICENSE            

---

## Web Deployment
This branch (`deployment`) is configured for zero-config deployment on Vercel.
1. Import the repository into Vercel.
2. Vercel automatically runs `scripts/build-wasm.sh` to compile the C++ to WebAssembly.
3. The frontend is served from `/public`, and the backend runs via the `/api` serverless function.

*(The CMake instructions above still apply for building the local terminal version).*

---

## Vercel Performance Metrics & Submissions

The Web UI tracks two things live:

1. **Per-generation performance** — every successful `/api/generate` response includes
   `perf.totalMs` (end-to-end) and `perf.wasmMs` (WASM-only). The output panel shows
   a `⚡ N ms` chip after each generation.

2. **Submission counters** — `api/generate.js` increments a daily key
   (`qr_count_YYYY-MM-DD`) and an all-time key (`qr_count_total`) in Vercel KV
   (Upstash Redis). `api/metrics.js` exposes them; the footer shows
   `Submissions today: N · Total: N`.

### Enabling the counters

Counters are a no-op until KV is wired up. In the Vercel dashboard
(Project → Settings → Environment Variables) set one of:

```
# Option A — Upstash REST (recommended)
QR_KV_REST_URL    = https://<your-upstash-instance>.upstash.io
QR_KV_REST_TOKEN  = <token>

# Option B — Vercel KV addon binding
QR_KV_TEAM_ID     = <team id>
QR_KV_PROJECT_ID  = <project id>
QR_KV_REST_TOKEN  = <token>
```

Once set, redeploy and the footer + `/api/metrics` start reporting real numbers.
Until then they gracefully fall back to `Submissions: tracking not configured`.

### Reading metrics yourself

```bash
curl https://<your-domain>/api/metrics
# → { configured, total, today, daily: {...}, ts }
```

Vercel's own dashboard (Observability → Functions) also reports invocation
counts and p50/p95/p99 latency for `api/generate` without any extra setup.

---


##  Build Instructions
### 1. Clone the repository
```bash
git clone https://github.com/7IRE/QR-Generator.git
cd QR-Generator
```
### 2. Configure with CMake
```bash
cmake -B build
```
### 3. Build
```bash
cmake --build build
```
### 4. Run
```bash
./build/qrcode_app
```

---
# QR Code Generator (C++)

##  Usage
When you run the program:

- You’ll be prompted to select an error correction level (0–3).
- Enter the text or URL you want to encode.
- The QR code will be rendered in your terminal.


### Terminal Output

![QR Example](screenshots/terminal.png)

---

##   Configuration

- Extend `render()` to support different rendering styles (ASCII, Unicode blocks, images).
- You can easily integrate this library into any other C++ project by copying the core files and linking them via CMake.
---