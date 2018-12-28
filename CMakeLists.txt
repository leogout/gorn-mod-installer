cmake_minimum_required(VERSION 3.10)
project(gorn_mod_installer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

SET(GUI_TYPE WIN32)

set(RESOURCE_FOLDER res)
set(RESOURCE_FILES ${RESOURCE_FOLDER}/resources.qrc)

set(SOURCE_FILES src/main.cpp src/view/PlatformSelection.cpp src/view/PlatformSelection.h src/MemeLoaderInstaller.cpp src/MemeLoaderInstaller.h src/Registry.cpp src/Registry.h)

if(CMAKE_BUILD_TYPE STREQUAL Release)
    add_executable(${PROJECT_NAME} ${GUI_TYPE} ${SOURCE_FILES} ${RESOURCE_FILES})
else()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${RESOURCE_FILES})
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Network)
