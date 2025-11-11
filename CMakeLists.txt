cmake_minimum_required(VERSION 3.2)

project(trumpf_zadanie_rekrutacyjne)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(TRUMPF_ZADANIE_REKRUTACYJNE_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(test)


