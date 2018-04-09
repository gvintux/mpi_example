cmake_minimum_required(VERSION 3.0)
project(mpi_example)
set(MPI_PROCESSES_COUNT 5)
#set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_CXX_COMPILER /usr/bin/mpic++)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#set(LAUNCHER "gnome-terminal --hide-menubar --window-with-profile=dev -x ")
set(LAUNCHER "uxterm -hold -e ")

unset(LAUNCHER)

#message(${CMAKE_CURRENT_BINARY_DIR})
set(CMD "${LAUNCHER} mpirun -np ${MPI_PROCESSES_COUNT} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
#message(${CMD})

add_custom_target(mpirun
        COMMAND $ENV{SHELL} -c "${CMD}"
        DEPENDS ${PROJECT_NAME})
