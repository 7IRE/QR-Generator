#  QR Code Generator (C++)

##  Overview
This project is a **QR Code Generator** written in **C++17**.  
It allows you to encode text or URLs into QR codes with customizable error correction levels and renders them directly in the terminal using ANSI escape sequences.

---

##  Features
- Generate QR codes from any string input.
- Supports **four error correction levels**:
  - Low (7% recovery)
  - Medium (15% recovery)
  - Quartile (25% recovery)
  - High (30% recovery)
- Terminal rendering using colored blocks (`ANSI escape codes`).
- Modular design with `QR_Generator` class for easy integration.

---

##  Requirements
- **C++17** or later
- **CMake ≥ 3.10**
- A terminal that supports ANSI escape sequences (Linux/macOS, or Windows with proper terminal emulator)

---

##  Project Structure
QR-Generator/  
│─ src/  
│   ├── main.cpp          
│   └── QR_Generator.cpp    
│─ include/     
│   ├── QR_Generator.hpp   
│   └── includes.hpp   
│─ screenshots/  
│   └── terminal.png   
│─ CMakeLists.txt        
│─ README.md            
│─ .gitignore            
└─ LICENSE            


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