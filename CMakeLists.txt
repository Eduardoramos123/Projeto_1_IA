cmake_minimum_required(VERSION 3.17)
project(projeto_1_IA)

set(CMAKE_CXX_STANDARD 14)
set(PYTHON_LIBRARY "C:/Users/andre/AppData/Local/Programs/Python/Python311/libs/python311.lib")

find_package(PythonLibs REQUIRED)

# Add the Boost include path
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(projeto_1_IA main.cpp Node.cpp Node.h Position.cpp Position.h Piece.cpp Piece.h Heuristics.cpp Heuristics.h Heuristics.cpp Game.cpp Game.h)

# Link your executable with the Boost libraries
target_include_directories(projeto_1_IA PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(projeto_1_IA ${PYTHON_LIBRARY})
