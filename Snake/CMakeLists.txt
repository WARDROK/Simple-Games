set(SNAKE_SOURCES
    Snake.cpp
)

# if(WIN32)
#     set(SNAKE_RESOURCES resources.rc)
# endif()

add_executable(Snake ${SNAKE_SOURCES} ${SNAKE_RESOURCES})
target_link_libraries(Snake PUBLIC sfml-graphics)