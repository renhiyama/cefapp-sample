#!/usr/bin/env bash

#download CEF binary from spotify - mention version from environment variable
# example: 130.1.16+g5a7e5ed+chromium-130.0.6723.117
if [ -z "$CEF_VERSION" ]; then
  echo "CEF_VERSION environment variable is not set"
  exit 1
fi
wget -O cef_binary.tar.bz2 https://cef-builds.spotifycdn.com/cef_binary_"$CEF_VERSION"_linux64_minimal.tar.bz2
tar -xvf cef_binary.tar.bz2
mv cef_binary_"$CEF_VERSION"_linux64_minimal cef_binary
rm cef_binary.tar.bz2