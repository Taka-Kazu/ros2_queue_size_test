// Copyright 2024 Kazuki Takahashi

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/header.hpp>

class TestSubscriberSpinOnce : public rclcpp::Node
{
public:
  TestSubscriberSpinOnce()
  : Node("test_subscriber_spin")
    , clock_(RCL_ROS_TIME)
  {
    this->declare_parameter("queue_size", 10);
    const int queue_size = this->get_parameter("queue_size").as_int();
    subscription_ = this->create_subscription<std_msgs::msg::Header>(
      "topic",
      rclcpp::QoS(rclcpp::KeepLast(queue_size)),
      std::bind(
        &TestSubscriberSpinOnce::topic_callback,
        this,
        std::placeholders::_1));
  }

  void topic_callback(const std_msgs::msg::Header::SharedPtr msg)
  {
    RCLCPP_INFO(
      this->get_logger(), "Latency: %f[s]",
      clock_.now().nanoseconds() * 1e-9 - (msg->stamp.sec + msg->stamp.nanosec * 1e-9));
  }

private:
  rclcpp::Subscription<std_msgs::msg::Header>::SharedPtr subscription_;
  rclcpp::Clock clock_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TestSubscriberSpinOnce>());
  rclcpp::shutdown();
  return 0;
}
