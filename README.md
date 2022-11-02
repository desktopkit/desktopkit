# org.DesktopKit *(draft)*

Unix Desktop Framework Kit.

Various libraries, services and utilities for (Qt) desktop applications.

**Currently in draft mode**

## Requirements

### Core

* GCC v4.8.5+ or Clang v3.3+
* CMake v3.5+
* Qt v5.9+ Core

## Build

```
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release ..
make
make DESTDIR=<package> install
```

## Kits

* *org.DesktopKit.*[BaseDir](kits/basedir/README.md)
