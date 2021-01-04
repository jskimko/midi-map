cmake_minimum_required(VERSION 3.0)

project(midimap
        VERSION 0.1
        LANGUAGES CXX
)

# RtMidi-4.0.0 exports its include directories as PRIVATE.
# rtmidi/{bin,lib,include,share}/rtmidi.{dll,lib}
find_package(RtMidi REQUIRED)
get_target_property(RtMidi_FILE RtMidi::rtmidi LOCATION) # library file path
get_filename_component(RtMidi_FILE_DIR "${RtMidi_FILE}" DIRECTORY) # parent dir
get_filename_component(RtMidi_ROOT_DIR "${RtMidi_FILE_DIR}" DIRECTORY) # root dir
set(RtMidi_INCLUDE_DIR "${RtMidi_ROOT_DIR}/include") # include dir

# FLTK-1.3.5 has a Config file, but does not define library directories.
find_package(FLTK CONFIG REQUIRED)
get_filename_component(FLTK_ROOT_DIR "${FLTK_INCLUDE_DIRS}" DIRECTORY) # root dir
set(FLTK_LIBRARY_DIR "${FLTK_ROOT_DIR}/lib")

# X11
if(NOT WIN32)
    find_package(X11 REQUIRED)
endif()

add_subdirectory(app)
add_subdirectory(src)

set_target_properties(midimap-app midimap-lib
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# move RtMidi.dll to RUNTIME_OUTPUT_DIRECTORY for Windows
if(WIN32)
    get_filename_component(EXTENSION ${RtMidi_FILE} EXT)
    if ("${EXTENSION}" STREQUAL ".dll")
        get_target_property(DIR midimap-app RUNTIME_OUTPUT_DIRECTORY)
        file(COPY ${RtMidi_FILE} DESTINATION ${DIR})
    endif()
endif()
