Built with:
- Visual Studio under Windows
- CMake under various unii with gcc or clang

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
but in ~/bin.

To change the default nit templates, namely the output format (see nitout.cpp),
you'll need a copy of vi (in all unix flavours & Windows 10 in the standard Linux guest),
or some other disreputable editor whose name I forget.
