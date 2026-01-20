cmake_minimum_required(VERSION 3.28)
project(Terrarium LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME}
src/main.cpp
src/tileMap.cpp
src/entities/player.cpp
src/logic/collision.cpp
)

target_compile_features(${PROJECT_NAME}
PRIVATE cxx_std_17
)

target_link_libraries(${PROJECT_NAME}
PRIVATE SFML::Graphics
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)