cmake_minimum_required(VERSION 3.9)

project(chrodify VERSION 1.0.1 DESCRIPTION "Lv2 plugin to make chrods in scale based on played midi note")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build/chordify.lv2)
if (WIN32)
    set(LIB_EXT ".dll")
endif (WIN32)
if (UNIX)
    set(LIB_EXT ".so")
endif (UNIX)

add_library(chrodify SHARED
    src/fifths.c
    src/uris.h
)

configure_file(manifest/fifths.ttl build/chordify.lv2/fifths.ttl COPYONLY)
configure_file(manifest/manifest.ttl.in build/chordify.lv2/manifest.ttl)

set_target_properties(chrodify PROPERTIES ADDITIONAL_CLEAN_FILES
        "build/chordify.lv2/fifths.ttl;build/chordify.lv2/manifest.ttl;")
