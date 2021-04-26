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

## Try it out (for Mac)

We're going to build a simple desktop application with gtk.
First off, let's install the gtk toolkit with homebrew:

```sh
brew install gtk+3
```

Here's the "hello world" code (simply clone the repo if you want to get it quicker):

```sh
git clone https://github.com/L-oris/gtk-sample-app
cd gtk-sample-app
```

Compile and run the app:

```sh
meson setup build
cd build
meson compile
./demo
```

All working fine so far.
VSCode, however, won't be able to provide any type definition yet, and will be complaining with a message similar to `#include errors detected. Please update your includePath.`.
To overcome the issue, `cd` into the project main directory and run:

```sh
pkg-config-vscode gtk+-3.0
```

It's going to create a new json file at `.vscode/c_cpp_properties.json` with all the new things you need.
