rm -rf CMakeCache.txt CMakeFiles CTestTestfile.cmake Makefile cmake_install.cmake
export ICU_ROOT=/Users/dylan/project/lib/icu/stage/static_ndebug
export BOOSTROOT=/Users/dylan/project/lib/boost
export BOOST_ROOT=/Users/dylan/project/lib/boost
export BOOST_INCLUDEDIR=/Users/dylan/project/lib/boost
export BOOST_LIBRARYDIR=/Users/dylan/project/lib/boost/stage/lib
export Boost_NO_SYSTEM_PATHS=ON
cmake -DCMAKE_BUILD_TYPE=Debug .
