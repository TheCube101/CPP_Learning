cmake_minimum_required(VERSION 3.28)
project(main)

set(CMAKE_CXX_STANDARD 17)

# Point the SFML_DIR to your local copy of the framework
set(SFML_DIR "C:/CPP-Libraries/Clion/SFML-3.0.2")
include_directories(${SFML_DIR}/include)
link_directories(${SFML_DIR}/lib)
add_definitions(-DSFML_STATIC)

#add_executable(main ui_test.cpp)
add_executable(main snake_game.cpp)
#add_executable(main structs.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-system sfml-window)