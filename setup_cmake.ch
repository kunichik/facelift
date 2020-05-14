#! /bin/bash

CMAKE_URL=https://github.com/Kitware/CMake/releases/download/v3.17.2/cmake-3.17.2.tar.gz   
mkdir cmake-3.17.2
travis_retry wget --no-check-certificate -O - https://github.com/Kitware/CMake/releases/download/v3.17.2/cmake-3.17.2.tar.gz | tar --strip-components=1 -xz -C cmake-3.17.2
cd cmake-3.17.2
./bootstrap
make && sudo make install && cd .. 
export PATH="$PWD/cmake-3.17.2/bin:$PATH"
