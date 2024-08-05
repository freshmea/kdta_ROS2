#include "example_interfaces/srv/add_two_ints.hpp"
#include "rcl_interfaces/msg/parameter_event.hpp"
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
        : Node("addTwoInt_client"), _a(30), _b(24)
    {
        _client = create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        _timer = create_wall_timer(5s, std::bind(&SimpleServiceClient::send_request, this));
        declare_parameter("a", 40);
        declare_parameter("b", 74);
        get_parameter("a", _a);
        get_parameter("b", _b);
        set_parameter(rclcpp::Parameter("a", 50));
        set_parameter(rclcpp::Parameter("b", 100));
        rclcpp::QoS qos(rclcpp::KeepLast(100), rmw_qos_profile_sensor_data);
        _parameter_event_sub = create_subscription<rcl_interfaces::msg::ParameterEvent>(
            "/parameter_events",
            qos,
            std::bind(&SimpleServiceClient::param_event_callback,
                      this,
                      std::placeholders::_1));
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
    void param_event_callback(const rcl_interfaces::msg::ParameterEvent::SharedPtr event)
    {
        for (auto &changed_parameter : event->changed_parameters)
        {
            if (changed_parameter.name == "a")
            {
                auto value = rclcpp::Parameter::from_parameter_msg(changed_parameter).as_int();
                _a = value;
            }
            else if (changed_parameter.name == "b")
            {
                auto value = rclcpp::Parameter::from_parameter_msg(changed_parameter).as_int();
                _b = value;
            }
        }
    }

private:
    int _a;
    int _b;
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr _client;
    rclcpp::TimerBase::SharedPtr _timer;
    rclcpp::Subscription<rcl_interfaces::msg::ParameterEvent>::SharedPtr _parameter_event_sub;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleServiceClient>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
