cmake_minimum_required(VERSION 3.9)

project(chrodify VERSION 1.0.1 DESCRIPTION "Lv2 plugin to make chrods in scale based on played midi note")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build/chordify.lv2)

add_library(chrodify SHARED
    src/lv2.cpp
    src/uris.h
    src/musictypes.h
    src/musictypes.cpp
)

if (WIN32)
    set(LIB_EXT ".dll")
endif (WIN32)
if (UNIX)
    set(LIB_EXT ".so")
    add_custom_command(
        TARGET chrodify POST_BUILD COMMAND ./scripts/install-build.sh
    )
endif (UNIX)


configure_file(manifest/libchrodify.ttl build/chordify.lv2/libchrodify.ttl COPYONLY)
configure_file(manifest/manifest.ttl.in build/chordify.lv2/manifest.ttl)

set_target_properties(chrodify PROPERTIES ADDITIONAL_CLEAN_FILES
        "build/chordify.lv2/libchrodify.ttl;build/chordify.lv2/manifest.ttl;")
