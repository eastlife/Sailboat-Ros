cmake_minimum_required(VERSION 2.8.3)
project(spare_function)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
        dynamic_reconfigure
        roscpp
        rospy
        sailboat_message
        std_msgs
        message_generation
        )


add_message_files(
        FILES
        spare_function_out.msg
        spare_function_para.msg
)

generate_dynamic_reconfigure_options(
        cfg/spare_function.cfg
)

generate_messages(
        DEPENDENCIES
        std_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
        INCLUDE_DIRS include
        LIBRARIES spare_function
        CATKIN_DEPENDS dynamic_reconfigure roscpp rospy sailboat_message std_msgs message_runtime
        #DEPENDS system_lib
)


include_directories(
        include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}
        ${catkin_INCLUDE_DIRS})

set( spare_function_SRC
        src/spare_function_main.cpp
        src/sailboat_ap_ok.cpp
        )


add_executable( ${PROJECT_NAME} ${spare_function_SRC} )
add_dependencies( ${PROJECT_NAME} ${catkin_EXPORTED_TARGETS} spare_function_gencfg)
target_link_libraries( ${PROJECT_NAME} ${catkin_LIBRARIES} )
