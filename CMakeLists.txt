cmake_minimum_required(VERSION 3.31)
project(adventurePicker)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-4.0)

add_executable(adventurePicker main.cpp)
target_link_libraries(adventurePicker PkgConfig::GTKMM)
