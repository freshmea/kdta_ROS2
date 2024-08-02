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
        _timer = create_wall_timer(5s, std::bind(&SimpleServiceClient::send_request, this));
    }

    void send_request()
    {
        while (!_client->wait_for_service(1s)) // 서버연결
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(get_logger(), "Over time!");
            }
            RCLCPP_INFO(get_logger(), "service not available, waiting again...");
        }
        // 보낼 변수 선언
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = _a;
        request->b = _b;

        auto result_future = _client->async_send_request(
            request, std::bind(&SimpleServiceClient::response_callback, this,
                               std::placeholders::_1));
    }
    void response_callback(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future)
    {
        auto status = future.wait_for(1s);
        if (status == std::future_status::ready)
        {
            RCLCPP_INFO(get_logger(), "Result of %d + %d = %ld", _a, _b, future.get()->sum);
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "Service In-Progress...");
        }
    }

private:
    int _a;
    int _b;
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr _client;
    rclcpp::TimerBase::SharedPtr _timer;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleServiceClient>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
