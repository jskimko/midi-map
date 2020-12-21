add_executable(midimap-app
    main.cc
)

target_link_libraries(midimap-app
    PRIVATE
        midimap-lib
)
