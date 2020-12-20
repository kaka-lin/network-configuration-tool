# Network Configuration Tool

## Require

- Qt5.10+
- CMake & Ninja

## build (qmake)

```bash
$ chmod +x build.sh

$ ./build.sh
```

## clean

```bash
$ chmod +x clean.sh

$ ./clean.sh
```

## build (cmake)

### Method 1

```bash
$ mkdir -p build && cd build
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ..
$ cmake --build .
```

### Method 2

```bash
$ chmod +x cmake-build.sh

$ ./cmake-build.sh
```

## clean

```bash
$ chmod +x cmake-clean.sh

$ ./cmake-clean.sh
```

## Trobuleshooting

### Qt is not found

Opening ```CMakeLists.txt``` and modify Qt location in ```list(APPEND CMAKE_PREFIX_PATH ${Your Qt path})```

### FullScreen

```bash
QT_WAYLAND_SHELL_INTEGRATION=wl-shell ./network-config-tool.pro
```
