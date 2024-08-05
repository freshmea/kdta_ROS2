#include "interface_example/srv/add_two_int.hpp"
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
        _service = this->create_service<interface_example::srv::AddTwoInt>("add_two_ints", std::bind(&SimpleServiceServer::callback, this, std::placeholders::_1, std::placeholders::_2));
        RCLCPP_INFO(get_logger(), "Service Server Ready to add two ints.");
    }

private:
    int _i;
    rclcpp::Service<interface_example::srv::AddTwoInt>::SharedPtr _service;
    void callback(const interface_example::srv::AddTwoInt::Request::SharedPtr request, interface_example::srv::AddTwoInt::Response::SharedPtr response)
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
