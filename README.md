# org.DesktopKit *(draft)*

Unix Desktop Framework Kit.

Various libraries, services and utilities for (Qt) desktop applications.

**Currently in draft mode**

## Requirements

### Core

* CMake v3.5+
* Qt v5.9+ Core

## Build

```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_LIBDIR=lib64 -DCMAKE_BUILD_TYPE=Release ..
make
make DESTDIR=<package> install
```
```
└── usr
    ├── include
    │   └── DesktopKit
    │       └── basedir.h
    ├── lib64
    │   ├── libDesktopKit.BaseDir.so -> libDesktopKit.BaseDir.so.1
    │   ├── libDesktopKit.BaseDir.so.1 -> libDesktopKit.BaseDir.so.1.0.0
    │   ├── libDesktopKit.BaseDir.so.1.0.0
    │   └── pkgconfig
    │       └── DesktopKit.BaseDir.pc
    └── share
        └── doc
            └── DesktopKit-1.0.0
                ├── LICENSE
                └── README.md
```

## Kits

* org.DesktopKit.App (#3)
* org.DesktopKit.[BaseDir](kits/basedir/README.md) (#2)
* org.DesktopKit.Disks (#5)
* org.DesktopKit.Files (#9)
* org.DesktopKit.Media (#7)
* org.DesktopKit.Network (#10)
* org.DesktopKit.Power (#8)
* org.DesktopKit.Thumbnails (#4)
* org.DesktopKit.Trash (#6)
* org.DesktopKit.X11 (#11)
