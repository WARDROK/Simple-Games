set(SNAKE_SOURCES
    Snake.cpp
)

# if(WIN32)
#     set(SNAKE_RESOURCES resources.rc)
# endif()

add_executable(Snake ${SNAKE_SOURCES} ${SNAKE_RESOURCES})
target_link_libraries(Snake PUBLIC sfml-graphics)

if(WIN32)
    add_custom_command(
        TARGET Snake
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Snake>
        VERBATIM)
endif()