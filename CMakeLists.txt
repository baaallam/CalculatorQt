cmake_minimum_required(VERSION 3.16)
project(CalculatorQt)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(CalculatorQt
    main.cpp
    calculator.cpp
    calculator.h
)

target_link_libraries(CalculatorQt PRIVATE Qt6::Widgets)
