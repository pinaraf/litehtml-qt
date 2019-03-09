cmake_minimum_required(VERSION 3.2)

project(litehtml-qt5 CXX)

add_executable(litehtml-qt5 main.cpp container_qt5.cpp)
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

target_link_libraries(litehtml-qt5 Qt5::Core Qt5::Gui Qt5::Widgets litehtml)

