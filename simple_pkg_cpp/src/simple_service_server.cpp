#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono_literals;

class SimpleServiceServer : public rclcpp::Node
{
public:
    SimpleServiceServer()
        : Node("addTwoInt_server"), _i(0)
    {
        _service = this->create_service<example_interfaces::srv::AddTwoInts>("add_two_ints", std::bind(&SimpleServiceServer::callback, this, std::placeholders::_1, std::placeholders::_2));
        RCLCPP_INFO(get_logger(), "Service Server Ready to add two ints.");
    }

private:
    int _i;
    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr _service;
    void callback(const example_interfaces::srv::AddTwoInts::Request::SharedPtr request, example_interfaces::srv::AddTwoInts::Response::SharedPtr response)
    {
        RCLCPP_INFO(get_logger(), "Incomming Message: %ld, %ld", request->a, request->b);
        response->sum = request->a + request->b;
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleServiceServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
