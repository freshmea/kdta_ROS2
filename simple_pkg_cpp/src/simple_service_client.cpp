#include "interface_example/srv/add_two_int.hpp"
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
        _client = create_client<interface_example::srv::AddTwoInt>("add_two_ints");
        while (!_client->wait_for_service(1s)) // 서버연결
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(get_logger(), "Over time!");
            }
            RCLCPP_INFO(get_logger(), "service not available, waiting again...");
        }
        RCLCPP_INFO(get_logger(), "Service is ready!");
    }
    void send_request()
    {
        RCLCPP_INFO(get_logger(), "Sending request...");
        auto request = std::make_shared<interface_example::srv::AddTwoInt::Request>();
        request->a = _a;
        request->b = _b;
        auto result = _client->async_send_request(request); // 비동기 요청
        RCLCPP_INFO(get_logger(), "After async...");
        if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) == rclcpp::FutureReturnCode::SUCCESS)
        {
            RCLCPP_INFO(get_logger(), "Result of %d + %d = %ld", _a, _b, result.get()->sum);
        }
        else
        {
            RCLCPP_INFO(get_logger(), "Service call failed!");
        }
    };

private:
    int _a;
    int _b;
    rclcpp::Client<interface_example::srv::AddTwoInt>::SharedPtr _client;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleServiceClient>();
    node->send_request();
    rclcpp::shutdown();
    return 0;
}
