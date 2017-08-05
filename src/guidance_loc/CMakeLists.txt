cmake_minimum_required(VERSION 2.8.3)
project(guidance_loc)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  nav_msgs
  std_msgs
  message_generation
)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# add_message_files(
#   FILES
#   Message1.msg
# )

add_service_files(
  FILES
  GuidanceLocCali.srv
)

generate_messages(
  DEPENDENCIES
  geometry_msgs 
  nav_msgs
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
)

include_directories(
  include
 	${catkin_INCLUDE_DIRS}
)

add_executable(guidance_loc src/guidance_loc_node.cpp
  src/guidance_loc.cpp
)

target_link_libraries(guidance_loc
  ${catkin_LIBRARIES}
)

add_dependencies(guidance_loc guidance_loc_generate_messages_cpp)
