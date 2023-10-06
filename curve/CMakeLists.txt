cmake_minimum_required(VERSION 3.10)

# Добавляем все cpp файлы в библиотеку curve
add_library(curve
    curve_lib.h
    curve_lib.cpp
)

# Укажите публичные хедеры для библиотеки curve
target_include_directories(curve PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

