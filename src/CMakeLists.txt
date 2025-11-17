cmake_minimum_required(VERSION  3.12)
project(trumpf_zadanie_rekrutacyjne)

set(SOURCE_FILES main.c static_double_deque.c static_double_deque.h file_analyzer.c file_analyzer.h)

add_executable(trumpf_zadanie_rekrutacyjne ${SOURCE_FILES})
install(TARGETS trumpf_zadanie_rekrutacyjne DESTINATION ${TRUMPF_ZADANIE_REKRUTACYJNE_BIN_DIR})
