# pkg-config-vscode

A tiny and easy to use YouTube downloader.
<br/>
<br/>
![](./screen-record.gif)

## Install from source

#### Prerequisites

- clang (should come already installed with the OS)
- cmake>=2.8, >=3.16 recommended (for json-c)
- meson (https://mesonbuild.com/SimpleStart.html)

#### Build & Install

```sh
# clone the repo and its submodules
git clone --recursive https://github.com/L-oris/pkg-config-vscode

# create a separate build directory to hold all of the compiler output
cd pkg-config-vscode
meson setup build

# compile, run tests, install
cd build
meson compile
meson test
meson install
```

## Usage

```sh
pkg-config-vscode [FLAGS] [LIB]...

# add compiler flags for the MongoDB C Driver (http://mongoc.org/)
pkg-config-vscode libmongoc-1.0
```

## Try it out

```sh
you-dl --output-dir ./Videos \
    https://www.youtube.com/watch?v=MAlSjtxy5ak \
    https://www.youtube.com/watch?v=4jOV0gaNKj0 \
    https://www.youtube.com/watch?v=pVjsCYlc1IY
```
