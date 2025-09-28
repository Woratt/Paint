cmake_minimum_required(VERSION 3.19)
project(paint LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

add_custom_target(format COMMAND clang-format -i --style=file ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_custom_target(tidy
    COMMAND clang-tidy -fix -p ${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR}/*.cpp
    COMMENT "Running clang-tidy on canvas.cpp..."
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping -O0 -g)
    add_link_options(-fprofile-instr-generate -fcoverage-mapping)
endif()

enable_testing()

add_subdirectory(tests)

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
    resourcepath.cpp
    canvas.h
    createfilewindow.h
    filesmodel.h
    filesystem.h
    homepage.h
    menubar.h
    numberline.h
    paintwindow.h
    toolbar.h
    resourcepath.h
)


target_link_libraries(paint
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/icons/icon.icns")
    message(WARNING "Icon file not found: ${CMAKE_SOURCE_DIR}/icons/icon.icns")
endif()

include(GNUInstallDirs)

install(TARGETS paint
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
if(APPLE OR WIN32)
    qt_generate_deploy_app_script(
        TARGET paint
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${deploy_script})
endif()

file(GLOB_RECURSE ICONS
${CMAKE_SOURCE_DIR}/icons/*)

set(RESOURCE_FILES ${ICONS})

set_source_files_properties(${ICONS} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/icons")

target_sources(paint PRIVATE ${RESOURCE_FILES})
