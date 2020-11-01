To build a release version with cmake:
cmake .
make
ctest .
make install

To build a debug version with cmake:
cmake -DCMAKE_BUILD_TYPE=Debug .
make
ctest .
make install

