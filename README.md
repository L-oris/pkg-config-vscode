# pkg-config-vscode

This program works in tandem with the C/C++ extension for VSCode.

It uses `pkg-config` to add metainformation about installed libraries into `.vscode/c_cpp_properties.json`, so that IntelliSense can work with them.

<br/>
<br/>

![](./screen-record.gif)

<br/>
<br/>

## Install from source

#### Prerequisites

- clang
- cmake>=2.8 (>=3.16 recommended)
- meson

#### Clone, compile, and install

```sh
# clone the repo and its submodules
git clone --recursive https://github.com/L-oris/pkg-config-vscode.git

# create a separate build directory to hold all the compiler output
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

# example: adding metainformation for the MongoDB C Driver (http://mongoc.org/)
pkg-config-vscode libmongoc-1.0
```

## Try it out

First off, make sure you have the C/C++ extension for VSCode installed.

Next, we're going to build a desktop application with gtk.
If you haven't already, install the gtk toolkit with homebrew:

```sh
brew install gtk+3
```

This is a "hello world" gtk application that you can clone:

```sh
git clone https://github.com/L-oris/gtk-sample-app.git
cd gtk-sample-app
```

Compile and run:

```sh
meson setup build
cd build
meson compile
./demo
```

The application is (hopefully) going to start as expected.

VSCode, however, will be complaining with a message along the lines of `#include errors detected. Please update your includePath.`.

That's what `pkg-config-vscode` is going to fix; `cd` into the project root and run:

```sh
pkg-config-vscode gtk+-3.0
```

The program is going to create a new configuration file at `.vscode/c_cpp_properties.json` with enough settings to make IntelliSense happy. Ready to go!

## Acknowledgments

Kudos to this [tutorial](https://github.com/rbtylee/tutorial-jsonc), which helped me out a lot with the [json-c](https://github.com/json-c/json-c) library.

## Limitations

I've been developing on macOS, so I cannot guarantee `pkg-config-vscode` works as expected on your favorite Linux distro.
