
file(GLOB SRCS *.cpp *.h)

set(BIN_DIR ${asteroids_SOURCE_DIR}/bin)

add_executable(asteroids ${SRCS})

target_link_libraries(asteroids ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})

install(TARGETS asteroids RUNTIME DESTINATION ${BIN_DIR})
