# Physical Activities Management System

A C system to manage clients, physical activities, and training plans. Compatible with **macOS ARM64/x86_64** and **Windows**.

## 📋 Features

1. **Search activity** - Count participants who performed a specific activity in a period
2. **List participants** - List clients who practiced activities in a period, ordered by activity count
3. **Show activity plan** - Display plans for a specific activity for a client in a period
4. **Calculate activity time** - Calculate total and average time of activities for a client

## 🚀 How to Run

### On macOS (ARM64/x86_64)

#### Option 1: Automated Script (Recommended)
```bash
./build.sh
```

#### Option 2: Makefile
```bash
# Install dependencies (if needed)
make install-deps

# Compile and run
make run

# Or compile and run separately
make
./activities
```

#### Option 3: Manual Compilation
```bash
gcc -Wall -Wextra -std=c99 -O2 -o activities imperative-c/Source.c
./activities
```

### On Windows

#### Visual Studio
1. Open `imperative-c.sln` in Visual Studio
2. Compile and run the project (F5)

#### Visual Studio Code
1. Open the `imperative-c` directory
2. Use the C/C++ extension to compile
3. Run the generated `.exe` file

#### Manual Compilation (Windows)
```cmd
cd imperative-c
cl Source.c /Fe:activities.exe
activities.exe
```

## 📁 Project Structure

```
imperative-c/
├── Makefile                    # Build for macOS/Linux
├── build.sh                   # Automated script
├── README.md                  # This documentation
├── imperative-c.sln           # Visual Studio Solution
└── imperative-c/
    ├── Source.c               # Main source code
    ├── customer.txt           # Customer data
    ├── activity.txt           # Activity data
    ├── plan.txt              # Plan data
    ├── imperative-c.vcxproj   # Visual Studio Project
    └── imperative-c.vcxproj.filters # Project filters
```

## 🔧 Makefile Commands

```bash
make           # Compile the program
make run       # Compile and run
make clean     # Remove compiled files
make debug     # Compile debug version
make release   # Compile optimized version
make help      # Show all commands
```

## 🛠️ Dependencies

### macOS
- **Xcode Command Line Tools**: `xcode-select --install`
- **GCC/Clang**: Included in command line tools

### Windows
- **Visual Studio Community** (recommended)
- **Visual Studio Code** with C/C++ extension
- **MinGW** or **MSVC** for manual compilation

## 🖥️ Compatibility

### ✅ Tested Systems
- **macOS Monterey+ (ARM64/M1/M2)**
- **macOS Big Sur+ (x86_64/Intel)**
- **Windows 10/11**

### 🔄 Cross-Platform Features
- Automatic operating system detection
- OS-specific terminal commands
- Compatible input functions (`scanf` vs `scanf_s`)
- Adaptive screen clearing (`clear` vs `cls`)




