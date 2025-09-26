# CMake generated Testfile for 
# Source directory: /Users/admin/Downloads/education/Paint/tests
# Build directory: /Users/admin/Downloads/education/Paint/build/Qt-Debug/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[PaintTests]=] "/Users/admin/Downloads/education/Paint/build/Qt-Debug/tests/test_paint")
set_tests_properties([=[PaintTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/admin/Downloads/education/Paint/tests/CMakeLists.txt;66;add_test;/Users/admin/Downloads/education/Paint/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
