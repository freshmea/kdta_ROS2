#include "example_interfaces/srv/add_two_ints.hpp"
#include "rcl_interfaces/msg/set_parameters_result.hpp"
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
        declare_parameter("a", 40);
        declare_parameter("b", 74);
        get_parameter("a", _a);
        get_parameter("b", _b);
        auto result = add_on_set_parameters_callback(std::bind(&SimpleServiceClient::param_callback, this, std::placeholders::_1));
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
    rcl_interfaces::msg::SetParametersResult param_callback(const std::vector<rclcpp::Parameter> &parameters)
    {
        for (const auto &param : parameters)
        {
            if (param.get_name() == "a")
            {
                _a = param.as_int();
            }
            else if (param.get_name() == "b")
            {
                _b = param.as_int();
            }
        }
        auto result = rcl_interfaces::msg::SetParametersResult();
        result.successful = true;
        return result;
    }

private:
    int _a;
    int _b;

    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr _client;
    rclcpp::TimerBase::SharedPtr _timer;
    rclcpp::AsyncParametersClient::SharedPtr _param_client;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleServiceClient>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
