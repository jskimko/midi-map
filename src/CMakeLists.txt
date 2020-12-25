add_library(midimap-lib
    midimap.cc
    Controller.cc
    Layout.cc
    Converter.cc
    Key.cc
    SetupWindow.cc
)

target_include_directories(midimap-lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${RtMidi_INCLUDE_DIRECTORIES}"
        "${FLTK_INCLUDE_DIRS}"
)

target_link_libraries(midimap-lib
    PUBLIC
        RtMidi::rtmidi
        fltk
)

target_link_directories(midimap-lib
    PUBLIC
        "${FLTK_LIBRARY_DIRS}"
)

