add_library(midimap-lib
    midimap.cc
    Controller.cc
    Layout.cc
    Converter.cc
    Key.cc
    SetupWindow.cc
    Keyboard.cc
    NoteKeyMap.cc
)

target_compile_features(midimap-lib
	PUBLIC
        cxx_std_17 # if constexpr
)

target_include_directories(midimap-lib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        "${RtMidi_INCLUDE_DIRS}"
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

if(NOT WIN32)
	target_compile_definitions(midimap-lib PUBLIC XLIB)
    if(X11_XTest_FOUND)
        target_compile_definitions(midimap-lib PUBLIC XTEST)
	endif()

    target_include_directories(midimap-lib
        PUBLIC
            "${X11_INCLUDE_DIR}"
            "${X11_XTest_INCLUDE_PATH}"
    )

    target_link_libraries(midimap-lib
        PRIVATE
            "${X11_LIBRARIES}"
            "${X11_XTest_LIB}"
    )
endif()
