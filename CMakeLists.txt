cmake_minimum_required(VERSION 3.0)

project(midimap
        VERSION 0.1
        LANGUAGES CXX
)

find_package(RtMidi REQUIRED)
# RtMidi exports its include directories as PRIVATE, so we need to get it ourselves.
get_target_property(RtMidi_LOCATION RtMidi::rtmidi LOCATION) # lib path
get_filename_component(RtMidi_LIB_DIR "${RtMidi_LOCATION}" DIRECTORY) # lib dir
get_filename_component(RtMidi_ROOT_DIR "${RtMidi_LIB_DIR}" DIRECTORY) # root dir
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
	get_target_property(DIR midimap-app RUNTIME_OUTPUT_DIRECTORY)
	file(COPY ${RtMidi_LOCATION} DESTINATION ${DIR})
endif()
