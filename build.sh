#!/bin/bash
rm -rf build
mkdir build
cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
./ImGuiDemo 