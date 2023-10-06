cmake_minimum_required(VERSION 3.10)
project(Curve)

set(CMAKE_CXX_STANDARD 17)

# Указываем имя исполняемого файла
set(EXECUTABLE_NAME main)

# Добавляем исполняемый файл с указанным именем
add_executable(${EXECUTABLE_NAME} main.cpp)

# Устанавливаем папку вывода для исполняемого файла
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/out"
    OUTPUT_NAME ${EXECUTABLE_NAME}
)

# Добавляем папку с исходными файлами curve
add_subdirectory(curve)

# Линкуем исполняемый файл с библиотекой curve
target_link_libraries(${EXECUTABLE_NAME} curve)
