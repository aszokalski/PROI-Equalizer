# PROI-Equalizer-Project

A simple equalizer plugin written in JUCE

## Supported targets

| Target             | Support |
|--------------------|---------|
| VST3               | ✅       |
| AU                 | ✅       |
| Standalone (MacOS) | ✅       |
| Standalone (Windows) | ✅       |
| Standalone (Linux) | ✅       |

## Setup
- Install [CMake](https://cmake.org/download/) 3.15 or newer 
- Install git submodules
```
git submodule update --init --recursive
```

## Build
### Using CLion
- Reload CMake project
- Build one of the targets 
- The build artifacts will be located in `cmake-build-[debug/release]/ProiEqualizer_artefacts/[Debug/Release]` directory

### Using CMake
- Create a build directory
```
mkdir build
cd build
```
- Generate build files
```
cmake ..
```
- Build one of the targets
```
cmake --build . --target ProiEqualizer_Standalone
```