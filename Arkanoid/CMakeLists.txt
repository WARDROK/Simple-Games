set(ARKANOID_SOURCES
    Arkanoid.cpp
    Game.cpp
    Block.cpp
    Ball.cpp
    MainMenu.cpp
)

if(WIN32)
    set(ARKANOID_RESOURCES resources.rc)
endif()

add_executable(Arkanoid ${ARKANOID_SOURCES} ${ARKANOID_RESOURCES})
target_link_libraries(Arkanoid PUBLIC sfml-graphics sfml-audio)

if(WIN32)
    add_custom_command(
        TARGET Arkanoid
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Arkanoid>
        VERBATIM)
endif()