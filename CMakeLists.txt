cmake_minimum_required(VERSION 2.8.3)
project(week12)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Declare ROS messages and services
add_message_files(
  FILES
)

add_service_files(
  FILES
)

## Generate added messages and services
generate_messages(
  DEPENDENCIES
  std_msgs
)

## Declare a catkin package
catkin_package(
	CATKIN_DEPENDS message_runtime
)


## Build talker and listener
include_directories(
  ${catkin_INCLUDE_DIRS}
)

# add_executable(talker src/talker.cpp)
# target_link_libraries(talker ${catkin_LIBRARIES})
# add_dependencies(talker week12_generate_messages_cpp)


if(CATKIN_ENABLE_TESTING)
  
  find_package(rostest REQUIRED)

  add_rostest_gtest(
  rosTest
#   test/test.launch
#   test/main.cpp
#   test/test.cpp
  )

  target_link_libraries(
  rosTest
  ${catkin_LIBRARIES}
  )

  add_dependencies(
#   talker
  rosTest
  ${catkin_EXPORTED_TARGETS}
  )
  
endif()