cmake_minimum_required(VERSION 3.0)

project(Silly-Finger)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
include_directories(
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
)

qt5_add_resources(SILLY_FINGER_RESOURCES res/resources.qrc)

qt5_wrap_ui(SILLY_FINGER_UI res/mainwidget.ui)

set(SillyFinger_SOURCES
    ${SILLY_FINGER_RESOURCES} 
    ${SILLY_FINGER_UI}
    src/main.cpp
    src/MainWidget.h
    src/MainWidget.cpp
    src/LifeWidget.h
    src/LifeWidget.cpp
)

add_definitions(-std=c++11)

if(WIN32)
	list(APPEND SillyFinger_SOURCES res/resources.rc)
	add_executable(SillyFinger WIN32 ${SillyFinger_SOURCES})
else()
	add_executable(SillyFinger ${SillyFinger_SOURCES})
endif()

target_link_libraries(SillyFinger Qt5::Widgets Qt5::Core)

install(TARGETS SillyFinger DESTINATION bin)

if(WIN32)
	set(CPACK_GENERATOR "NSIS")
else()
	set(CPACK_GENERATOR "ZIP")
endif()

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Shnaider Pavel") #required
 
include(CPack)