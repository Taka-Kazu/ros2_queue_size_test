cmake_minimum_required(VERSION 3.8)
project(ros2_queue_size_test)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(queue_size_test_publisher src/publisher.cpp)
ament_target_dependencies(queue_size_test_publisher rclcpp std_msgs)

add_executable(queue_size_test_subscriber_spin_some src/subscriber_spin_some.cpp)
ament_target_dependencies(queue_size_test_subscriber_spin_some rclcpp std_msgs)

add_executable(queue_size_test_subscriber_spin src/subscriber_spin.cpp)
ament_target_dependencies(queue_size_test_subscriber_spin rclcpp std_msgs)

install (TARGETS
    queue_size_test_publisher
    queue_size_test_subscriber_spin_some
    queue_size_test_subscriber_spin
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
