cmake_minimum_required(VERSION 3.0)

project(midimap
        VERSION 0.1
        LANGUAGES CXX
)

# RtMidi exports its include directories as PRIVATE, so we need to get it ourselves.
# rtmidi/{bin,lib,include,share}/rtmidi.{dll,lib}
find_package(RtMidi REQUIRED)
get_target_property(RtMidi_FILE RtMidi::rtmidi LOCATION) # library file path
get_filename_component(RtMidi_FILE_DIR "${RtMidi_FILE}" DIRECTORY) # parent dir
get_filename_component(RtMidi_ROOT_DIR "${RtMidi_FILE_DIR}" DIRECTORY) # root dir
set(RtMidi_INCLUDE_DIRECTORIES "${RtMidi_ROOT_DIR}/include") # include dir

add_subdirectory(app)
add_subdirectory(src)

set_target_properties(midimap-app midimap-lib
    PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# move RtMidi.dll to bin for Windows
if(WIN32)
    get_filename_component(EXTENSION ${RtMidi_FILE} EXT)
    if ("${EXTENSION}" STREQUAL ".dll")
		get_target_property(DIR midimap-app RUNTIME_OUTPUT_DIRECTORY)
		file(COPY ${RtMidi_FILE} DESTINATION ${DIR})
	endif()
endif()
