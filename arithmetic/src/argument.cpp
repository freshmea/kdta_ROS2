#include "interface_example/msg/arithmetic_argument.hpp"
#include "rclcpp/rclcpp.hpp"
#include <chrono>

using namespace std::chrono_literals;

class Argument : public rclcpp::Node
{
public:
    Argument() : Node("argument")
    {
        auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
        _publisher = create_publisher<interface_example::msg::ArithmeticArgument>("arithmetic_argument", qos_profile);
        _timer = create_wall_timer(1s, std::bind(&Argument::pub_callback, this));
    }

private:
    float _num_a;
    float _num_b;
    rclcpp::Publisher<interface_example::msg::ArithmeticArgument>::SharedPtr _publisher;
    rclcpp::TimerBase::SharedPtr _timer;
    void pub_callback()
    {
        auto msg = interface_example::msg::ArithmeticArgument();
        msg.argument_a = _num_a;
        msg.argument_b = _num_b;
        _publisher->publish(msg);
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Argument>());
    rclcpp::shutdown();
    return 0;
}