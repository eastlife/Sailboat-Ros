cmake_minimum_required(VERSION 2.8.3)
project(sensor_process)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
        roscpp
        rospy
        sailboat_message
        std_msgs
        message_filters
        )

catkin_package(
        INCLUDE_DIRS include
        LIBRARIES sensor_process
        CATKIN_DEPENDS roscpp rospy sailboat_message std_msgs message_filters
        #DEPENDS system_lib
)


include_directories(
        include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}
        ${catkin_INCLUDE_DIRS})

set(sensor_process_SRC
        src/CSensorProcess.cpp
        src/Sensor_Process.cpp)

set(sensor_filters_SRC
        src/Sensor_filters.cpp)


add_executable(sensor_process ${sensor_process_SRC})
target_link_libraries(sensor_process ${catkin_LIBRARIES})
add_dependencies(sensor_process ${catkin_EXPORTED_TARGETS})

add_executable(sensor_filters ${sensor_filters_SRC})
target_link_libraries(sensor_filters ${catkin_LIBRARIES})
add_dependencies(sensor_filters ${catkin_EXPORTED_TARGETS})
