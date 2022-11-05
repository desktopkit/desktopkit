# DesktopKit *(draft)*

Unix Desktop Framework Kit.

Various libraries, services and utilities for (Qt/C++) desktop applications.

**Currently in draft mode**

## Requirements

### Core

* Qt v5+ Core

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
    │       └── core.h
    ├── lib64
    │   ├── libDesktopKit.Core.so -> libDesktopKit.Core.so.1
    │   ├── libDesktopKit.Core.so.1 -> libDesktopKit.Core.so.1.0.0
    │   ├── libDesktopKit.Core.so.1.0.0
    │   └── pkgconfig
    │       └── DesktopKit.Core.pc
    └── share
        └── doc
            └── DesktopKit-1.0.0
                ├── LICENSE
                └── README.md
```

## Kits

### Core

Library that provide core functions.

* `DesktopKit::Core::Common` - provides common functions
* `DesktopKit::Core::BaseDir` - provides paths for standarized directories
* `DesktopKit::Core::Mimes` - provides mime functions

## TODO

* org.DesktopKit.App (https://github.com/desktopkit/desktopkit/issues/3)
* org.DesktopKit.Disks (https://github.com/desktopkit/desktopkit/issues/5)
* org.DesktopKit.Files (https://github.com/desktopkit/desktopkit/issues/9)
* org.DesktopKit.Media (https://github.com/desktopkit/desktopkit/issues/7)
* org.DesktopKit.Network (https://github.com/desktopkit/desktopkit/issues/10)
* org.DesktopKit.Power (https://github.com/desktopkit/desktopkit/issues/8)
* org.DesktopKit.Thumbnails (https://github.com/desktopkit/desktopkit/issues/4)
* org.DesktopKit.Trash (https://github.com/desktopkit/desktopkit/issues/6)
* org.DesktopKit.X11 (https://github.com/desktopkit/desktopkit/issues/11)
