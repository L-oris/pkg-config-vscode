# pkg-config-vscode

This program works in tandem with the C/C++ extension for VSCode.

It uses `pkg-config` to add metainformation about installed libraries into `.vscode/c_cpp_properties.json`, so that Intellisense can work as expected with those.

I've been developing on OSX, so I cannot guarantee it works as expected on your favorite Linux disto.
<br/>
<br/>
![](./screen-record.gif)

## Install from source

#### Prerequisites

- clang (should come already installed with the OS)
- cmake>=2.8 (>=3.16 recommended)
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

First off, make sure you have the C/C++ extension for VSCode installed.

Next up, we're going to build a simple desktop application with gtk.
If you haven't already, install the gtk toolkit with homebrew:

```sh
brew install gtk+3
```

This is a "hello world" gtk application that you can clone:

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

The application is (hopefully) going to start as expected.

VSCode, however, will be complaining with a message along the lines of `#include errors detected. Please update your includePath.`.

That's what `pkg-config-vscode` is going to fix; `cd` in the project root and run:

```sh
pkg-config-vscode gtk+-3.0
```

The program is going to create a new json file at `.vscode/c_cpp_properties.json` with enough settings to make IntelliSense happy. Ready to go!
