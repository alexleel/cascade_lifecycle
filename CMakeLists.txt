cmake_minimum_required(VERSION 3.5)
project(rclcpp_cascade_lifecycle)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_lifecycle REQUIRED)
find_package(lifecycle_msgs REQUIRED)
find_package(cascade_lifecycle_msgs REQUIRED)
find_package(ament_cmake_python REQUIRED)

set(executable_name base_lifecycle_manager)

set(dependencies
  rclcpp
  rclcpp_lifecycle
  lifecycle_msgs
  cascade_lifecycle_msgs
)

include_directories(include)

add_library(${PROJECT_NAME} SHARED
  src/rclcpp_cascade_lifecycle/rclcpp_cascade_lifecycle.cpp
  src/rclcpp_cascade_lifecycle/cascade_manager.cpp
  src/rclcpp_cascade_lifecycle/base_lifecycle_manager.cpp
)
ament_target_dependencies(${PROJECT_NAME} ${dependencies})

add_executable(${executable_name}
  src/rclcpp_cascade_lifecycle/base_node.cpp
)

target_link_libraries(${executable_name} ${PROJECT_NAME})

add_executable(simple_node
  src/rclcpp_cascade_lifecycle/simple_node.cpp
)

target_link_libraries(simple_node ${PROJECT_NAME})

ament_target_dependencies(${executable_name}
  ${dependencies}
)

ament_target_dependencies(simple_node
  ${dependencies}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
  add_subdirectory(test)
endif()

install(DIRECTORY include/
  DESTINATION include/
)

install(TARGETS
  ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS ${executable_name}
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS simple_node
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

install(DIRECTORY ros_pycommon
  DESTINATION share/${PROJECT_NAME})

install(DIRECTORY params 
  DESTINATION share/${PROJECT_NAME})

ament_python_install_package(ros_pycommon)

ament_export_include_directories(include)
ament_export_libraries(${PROJECT_NAME})
ament_export_dependencies(${dependencies})

ament_package()
