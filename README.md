# SDLGL_Base
Base OpenGL/SDL2.0 project

## Build

### Dependencies
* SDL2
* GLM

### Get the code

```
git clone --recursive https://github.com/TomMinor/SDLGL_Base
```

*Note: Make sure to add --recursive so all the submodules are synced too*

### Configuring CMake

***Note: On Windows it is currently necessary to force a 64-bit build with CMAKE_GENERATOR_PLATFORM***
#### Windows
```batch
mkdir build
cd build
cmake .. -DCMAKE_GENERATOR_PLATFORM=x64 -DSDL2_DIR="D:/dev/SDL2"
```

*Use the toolset argument *(-T)* to force the 2013 compilers in a newer version of Visual Studio (such as [community](https://www.visualstudio.com/vs/community/))*
```batch
cmake .. -DCMAKE_GENERATOR_PLATFORM=x64 -T v120 -DCMAKE_GENERATOR_PLATFORM=x64 -DSDL2_DIR="D:/dev/SDL2"
```

#### Linux
```bash
mkdir build
cd build
cmake ..
```
