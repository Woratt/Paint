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

# 🔥 ПРОСТИЙ СПОСІБ: всі файли в одному executable
add_executable(test_paint 
    test_main.cpp
    test_canvas.cpp
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

target_link_libraries(test_paint PRIVATE
    GTest::gtest_main
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

target_include_directories(test_paint PRIVATE ..)

add_custom_target(run_tests
    COMMAND ./test_paint
    DEPENDS test_paint
    COMMENT "Running tests..."
)

add_test(NAME PaintTests COMMAND test_paint)