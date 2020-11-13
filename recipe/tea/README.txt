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

Because ssc is very alpha, the make install does not install in a standard location,
but in the ssc parent directory.
