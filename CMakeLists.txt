cmake_minimum_required(VERSION 3.22)
project(WidgetInQML)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#find_package(Qt5 COMPONENTS Core Widgets Quick Gui REQUIRED)
find_package(Qt6 COMPONENTS Core Widgets Quick Gui REQUIRED)

add_executable(WidgetInQML
    main.cpp
    Container.cpp
    Container.hpp
    Form.ui
    qml.qrc)

target_link_libraries(WidgetInQML PRIVATE Qt::Core Qt::Quick Qt::Widgets)
