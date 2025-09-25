cmake_minimum_required(VERSION 3.19)
project(tests LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gtest_disable_pthreads ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

enable_testing()

add_library(paint_lib
    ../canvas.cpp
    ../createfilewindow.cpp
    ../filesmodel.cpp
    ../filesystem.cpp
    ../homepage.cpp
    ../menubar.cpp
    ../numberline.cpp
    ../paintwindow.cpp
    ../resourcepath.cpp
    ../toolbar.cpp
)

add_executable(test_paint 
    test_main.cpp
    test_canvas.cpp
    #test_createfilewindow.cpp
    #test_filesmodel.cpp
    #test_filesystem.cpp
    #test_homepage.cpp
    #test_menubar.cpp
    #test_numberline.cpp
    #test_paintwindow.cpp
    #test_recourcepath.cpp
    #test_toolbar.cpp
)

target_link_libraries(paint_lib
    PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets
)

target_link_libraries(test_paint PRIVATE
    paint_lib
    GTest::gtest_main
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

add_custom_target(run_tests
    COMMAND ./test_paint
    DEPENDS test_paint
    COMMENT "Running tests..."
)

add_test(NAME PaintTests COMMAND test_paint)