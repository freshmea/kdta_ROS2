#include "example_interfaces/srv/add_two_ints.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono_literals;

class SimpleServiceClient : public rclcpp::Node
{
public:
    SimpleServiceClient()
        : Node("addTwoInt_client"), _a(40), _b(74)
    {
        _client = create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        _timer = this->create_wall_timer(5s, std::bind(&SimpleServiceClient::send_request, this));
        RCLCPP_INFO(get_logger(), "Service Server Ready to add two ints.");
    }

private:
    int _a;
    int _b;
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr _client;
    rclcpp::TimerBase::SharedPtr _timer;
    void send_request()
    {
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = _a;
        request->b = _b;
        while (!_client->wait_for_service(1s)) // 서버연결
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(get_logger(), "Over time!");
            }
            RCLCPP_INFO(get_logger(), "service not available, waiting again...");
        }
        auto result = _client->async_send_request(request); // 비동기 요청
        if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) == rclcpp::FutureReturnCode::SUCCESS)
        {
            RCLCPP_INFO(get_logger(), "Result of %d + %d = %ld", _a, _b, result.get()->sum);
        }
        else
        {
            RCLCPP_INFO(get_logger(), "Service call failed!");
        }
    };
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleServiceClient>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
