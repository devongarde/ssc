# CMake generated Testfile for 
# Source directory: /Users/dylan/Depot/applications/ssc/recipe/tea
# Build directory: /Users/dylan/Depot/applications/ssc/recipe/tea
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(toasty_toast "/Users/dylan/Depot/applications/ssc/recipe/tea/ssc-test" "-d" "-i" "/Users/dylan/Depot/applications/ssc/recipe/tea/../toast/ssc-test/output.txt" "/Users/dylan/Depot/applications/ssc/recipe/tea/../toast/ssc-test/input.spec")
set_tests_properties(toasty_toast PROPERTIES  _BACKTRACE_TRIPLES "/Users/dylan/Depot/applications/ssc/recipe/tea/CMakeLists.txt;230;add_test;/Users/dylan/Depot/applications/ssc/recipe/tea/CMakeLists.txt;0;")
add_test(toast "/Users/dylan/Depot/applications/ssc/recipe/tea/ssc-test" "-v" "-f" "/Users/dylan/Depot/applications/ssc/recipe/tea/../toast/ssc-test/ssc.lst")
set_tests_properties(toast PROPERTIES  _BACKTRACE_TRIPLES "/Users/dylan/Depot/applications/ssc/recipe/tea/CMakeLists.txt;231;add_test;/Users/dylan/Depot/applications/ssc/recipe/tea/CMakeLists.txt;0;")
