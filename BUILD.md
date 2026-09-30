# Building FamilyTreeBuilder

## Requirements

- C++17 compatible compiler (GCC, Clang, or MSVC)
- CMake 3.10+

## Build Instructions

### Linux/Mac

```bash
mkdir build
cd build
cmake ..
make
./family
```

### Windows

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
./Release/family.exe
```

## Features

- Add family members
- Define relationships
- Query family connections
- Multi-language support (English, Finnish)
