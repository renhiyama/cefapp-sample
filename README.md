# Sample Minimal CEF App

This project aims to create a minimal CEF app working. Since CEF is already hard to setup, this provides a basic working repository to start with.
Feel free to fork it and work on it.

## Setup

Run the following commands to setup the project:

```bash
CEF_VERSION="130.1.16+g5a7e5ed+chromium-130.0.6723.117" ./download_prebuilt_cef.sh
```

Replace the `CEF_VERSION` env value with the version you want to download. You can find the available versions [here](https://cef-builds.spotifycdn.com/index.html).

## Build

To build the project, run the following commands:

```bash
cd src
mkdir build
cd build
cmake ..
make -j
```

## Run

To run the project, run the following commands:

```bash
cd src/build
./Release/cefapp
```

You can also pass the url to open as an argument:

```bash
./Release/cefapp --url=chrome://gpu
```

Replace url with the desired url you want to open. `chrome://gpu` is used to check the GPU status.
