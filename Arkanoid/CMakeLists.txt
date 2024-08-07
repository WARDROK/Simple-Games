set(ARKANOID_SOURCES
    Arkanoid.cpp
)

# if(WIN32)
#     set(ARKANOID_RESOURCES resources.rc)
# endif()

add_executable(Arkanoid ${ARKANOID_SOURCES} ${ARKANOID_RESOURCES})
target_link_libraries(Arkanoid PUBLIC sfml-graphics)