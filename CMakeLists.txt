cmake_minimum_required(VERSION 3.14)
project(cowchess)
set(CMAKE_CXX_STANDARD 17)

# Source directory
aux_source_directory(source/ SOURCES)

# Executable for the run configuration
add_executable(cowchess ${SOURCES})

# Link to SDL2 libraries
target_link_libraries(${PROJECT_NAME} -lSDL2 -lSDL2_image)

# target directory to the configuration
target_include_directories(${PROJECT_NAME} PRIVATE headers/ img/)
