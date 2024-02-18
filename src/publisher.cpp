// Copyright 2024 Kazuki Takahashi

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/header.hpp>

class TestPublisher : public rclcpp::Node
{
public:
  TestPublisher()
  : Node("test_publisher")
    , clock_(RCL_ROS_TIME)
  {
    publisher_ = this->create_publisher<std_msgs::msg::Header>("topic", 1);

    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(100),
      std::bind(&TestPublisher::timer_callback, this));
  }

  void timer_callback()
  {
    std_msgs::msg::Header message;
    message.stamp = clock_.now();
    publisher_->publish(message);
  }

private:
  rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Clock clock_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TestPublisher>());
  rclcpp::shutdown();
  return 0;
}
