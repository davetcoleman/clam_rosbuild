cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
rosbuild_genmsg()
#uncomment if you have defined services
rosbuild_gensrv()

#common commands for building c++ executables and libraries
rosbuild_add_library(${PROJECT_NAME} src/dynamixel_io.cpp src/serial_proxy.cpp)
target_link_libraries(${PROJECT_NAME} flexiport)

rosbuild_add_boost_directories()
rosbuild_link_boost(${PROJECT_NAME} thread)

rosbuild_add_executable(controller_manager src/controller_manager.cpp)
target_link_libraries(controller_manager ${PROJECT_NAME})

rosbuild_add_library(dynamixel_controllers src/joint_position_controller.cpp
                                           src/joint_torque_controller.cpp
                                           src/joint_trajectory_action_controller.cpp)
target_link_libraries(dynamixel_controllers ${PROJECT_NAME})

rosbuild_add_executable(dynamixel_io test/main.cpp)
target_link_libraries(dynamixel_io ${PROJECT_NAME})

option (DYNAMIXEL_BUILD_BINDINGS "Build the Python bindings for Dynamixel Driver" ON)
if (DYNAMIXEL_BUILD_BINDINGS)
    add_subdirectory (python)
endif (DYNAMIXEL_BUILD_BINDINGS)
