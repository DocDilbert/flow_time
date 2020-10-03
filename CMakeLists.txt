cmake_minimum_required(VERSION 3.10)

# set the project name
project(flow_time)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
find_package(Boost 1.74.0)

SET(SOURCE
  main.cc
  mainwindow.cpp
  mainwindow.ui
  resources.qrc
)

SET(HEADERS
  mainwindow.h
)

# add the executable
add_executable(flow_time WIN32 ${SOURCE} ${HEADERS})

# Link getopt  ... attention dll is needed
target_link_libraries(flow_time PUBLIC Qt5::Widgets)

target_include_directories(flow_time PUBLIC ${Boost_INCLUDE_DIRS})

# Add include directory
target_include_directories(flow_time PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          ) 
						  
# Copy qt widgets dll to build folder
add_custom_command(
    TARGET flow_time POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE_DIR:flow_time>
)

# Copy qt core dll to build folder
add_custom_command(
    TARGET flow_time POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE_DIR:flow_time>
)

# Copy qt gui dll to build folder
add_custom_command(
    TARGET flow_time POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE_DIR:flow_time>
)

# create platforms folder needed by qt
add_custom_command(
    TARGET flow_time POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:flow_time>/platforms"
)

# copy windows integration plugin to platforms folder
add_custom_command(
    TARGET flow_time POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin>
        "$<TARGET_FILE_DIR:flow_time>/platforms"
)

# ------------------------------
# For debugging purposes
# ------------------------------
#
# add_custom_command(
#    TARGET flow_time POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#       COMMAND ${CMAKE_COMMAND} -E make_directory 
#       $<TARGET_FILE_DIR:flow_time>\test
#)