cmake_minimum_required(VERSION 3.12)
project(trumpf_zadanie_rekrutacyjne)

include_directories(${SOURCE_DIR})
set(SOURCE_FILES main_test.c ${SOURCE_DIR}/static_double_deque.c ${SOURCE_DIR}/static_double_deque.h ${SOURCE_DIR}/file_analyzer.c ${SOURCE_DIR}/file_analyzer.h)

add_executable(trumpf_zadanie_rekrutacyjne_test ${SOURCE_FILES})
install(TARGETS trumpf_zadanie_rekrutacyjne_test DESTINATION ${TRUMPF_ZADANIE_REKRUTACYJNE_BIN_DIR})