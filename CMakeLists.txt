cmake_minimum_required(VERSION 3.19)
project(paint LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

add_custom_target(format COMMAND clang-format -i --style=file ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

qt_add_executable(paint
    WIN32 MACOSX_BUNDLE
    canvas.cpp
    createfilewindow.cpp
    filesmodel.cpp
    filesystem.cpp
    homepage.cpp
    main.cpp
    menubar.cpp
    numberline.cpp
    paintwindow.cpp
    toolbar.cpp
    canvas.h
    createfilewindow.h
    filesmodel.h
    filesystem.h
    homepage.h
    menubar.h
    numberline.h
    paintwindow.h
    toolbar.h
)

target_link_libraries(paint
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

include(GNUInstallDirs)

install(TARGETS paint
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET paint
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
