cmake_minimum_required(VERSION 3.19)
option(ENABLE_COVERAGE "Enable code coverage reporting" OFF)
project(paint_tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()
# 1. Основна бібліотека - КОМПІЛЮЄМО З COVERAGE
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
    ../infobar.cpp
    ../gradientpalette.cpp
    ../menupalette.cpp
)

# ✅ Coverage флаги для ВАШОЇ бібліотеки

target_link_libraries(paint_lib PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
# 2. Тестовий виконуваний файл - БЕЗ coverage флагів
add_executable(test_paint 
test_main.cpp
test_canvas.cpp
test_createfilewindow.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
    
    target_compile_options(paint_lib PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(paint_lib PRIVATE -fprofile-instr-generate -fcoverage-mapping)

    target_compile_options(test_paint PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    target_link_options(test_paint PRIVATE -fprofile-instr-generate -fcoverage-mapping)

    add_custom_target(coverage
        COMMAND rm -f default.profraw default.profdata
        COMMAND echo "Running tests..."
        COMMAND LLVM_PROFILE_FILE=default.profraw $<TARGET_FILE:test_paint>
        COMMAND echo "Merging profile data..."
        COMMAND llvm-profdata merge -sparse default.profraw -o default.profdata
        COMMAND echo "Generating text report..."
        COMMAND llvm-cov report $<TARGET_FILE:test_paint> -instr-profile=default.profdata -ignore-filename-regex=".*googletest.*|.*test_.*|.*moc_.*|.*qrc_.*|.*CMakeFiles.*"
        COMMAND echo "Generating HTML report..."
        COMMAND llvm-cov show $<TARGET_FILE:test_paint> -instr-profile=default.profdata -ignore-filename-regex=".*googletest.*|.*test_.*|.*moc_.*|.*qrc_.*|.*CMakeFiles.*" --format=html -output-dir=coverage_report
        COMMAND echo "✅ Coverage report: file://${CMAKE_BINARY_DIR}/coverage_report/index.html"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS test_paint
    )
endif()
# ❌ НЕ додаємо coverage флаги для тестівtarget_link_libraries(test_paint PRIVATE
target_link_libraries(test_paint
    PRIVATE paint_lib       # твоя бібліотека
    PRIVATE GTest::gtest_main  # GTest
    PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets
)

# 3. Ціль для coverage
add_test(NAME PaintTests COMMAND test_paint)
