cmake_minimum_required(VERSION 3.16)
project(Calculator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt
find_package(Qt6 COMPONENTS Widgets QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()

# Calculator library (for testing)
add_library(calculator_lib
    src/calculator.cpp
    src/calculator.h
)
target_include_directories(calculator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Main executable
add_executable(calculator
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
)

target_link_libraries(calculator PRIVATE
    calculator_lib
    Qt${QT_VERSION_MAJOR}::Widgets
)

# Enable testing
enable_testing()
add_subdirectory(tests)
