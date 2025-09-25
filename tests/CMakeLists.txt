cmake_minimum_required(VERSION 3.19)
project(tests LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 🔥 Додайте визначення для бібліотеки
add_compile_definitions(PAINT_LIBRARY=1)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

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

# 🔥 Створіть SHARED бібліотеку для правильного експорту
add_library(paint_lib SHARED  # ← ЗМІНІТЬ на SHARED
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

# ✅ Тільки тестові файли
add_executable(test_paint 
    test_main.cpp
    test_canvas.cpp
)

# 🔥 Додайте інклюди для тестів
target_include_directories(test_paint PRIVATE ..)
target_include_directories(paint_lib PRIVATE ..)

# ✅ Підключіть бібліотеку до тестів
target_link_libraries(test_paint PRIVATE
    GTest::gtest_main
    paint_lib
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

target_link_libraries(paint_lib PRIVATE
    Qt6::Core
    Qt6::Gui  
    Qt6::Widgets
)

# 🔥 Для Windows - специфічні налаштування
if(WIN32)
    target_compile_definitions(paint_lib PRIVATE PAINT_LIBRARY=1)
    target_compile_definitions(test_paint PRIVATE PAINT_STATIC=1)
endif()

add_custom_target(run_tests
    COMMAND ./test_paint
    DEPENDS test_paint
    COMMENT "Running tests..."
)

add_test(NAME PaintTests COMMAND test_paint)