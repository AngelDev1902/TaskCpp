cmake_minimum_required(VERSION 3.26)
project(TodoList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(TodoList main.cpp
        Window.cpp
        Window.h
        alltasks.h
        alltasks.cpp
        myday.cpp
        myday.h
        taskday.cpp
        taskday.h
        newtask.cpp
        newtask.h
)
target_link_libraries(TodoList
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

