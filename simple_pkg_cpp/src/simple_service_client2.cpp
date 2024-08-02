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
        : Node("addTwoInt_client"), _a(30), _b(24)
    {
        _client = create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        _timer = create_wall_timer(5s, std::bind(&SimpleServiceClient::send_request, this));
        declare_parameter("a", 40);
        declare_parameter("b", 74);
        get_parameter("a", _a);
        get_parameter("b", _b);
        auto ha = add_on_set_parameters_callback(
            std::bind(&SimpleServiceClient::param_callback, this, std::placeholders::_1));
        set_parameter(rclcpp::Parameter("a", 50));
        set_parameter(rclcpp::Parameter("b", 100));
        _param_client = std::make_shared<rclcpp::AsyncParametersClient>(this);
        auto param_event_callback =
            [this](const rcl_interfaces::msg::ParameterEvent::SharedPtr event) -> void
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
        };
        auto sub = _param_client->on_parameter_event(param_event_callback);
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
        _a++;
        _b++;
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
        RCLCPP_INFO(this->get_logger(), "Parameters set.");
        for (const auto &param : parameters)
        {
            RCLCPP_INFO(this->get_logger(), "Parameter name: %s", param.get_name());
            RCLCPP_INFO(this->get_logger(), "Parameter value: %ld", param.get_parameter_value().get<int>());
            if (param.get_name() == string("a"))
            {
                RCLCPP_INFO(this->get_logger(), "Parameter a is set to %ld", param.get_parameter_value().get<int>());
                _a = param.get_parameter_value().get<int>();
            }
            else if (param.get_name() == string("b"))
            {
                RCLCPP_INFO(this->get_logger(), "Parameter b is set to %ld", param.get_parameter_value().get<int>());
                _b = param.get_parameter_value().get<int>();
            }
        }
        auto result = rcl_interfaces::msg::SetParametersResult();
        result.successful = true;
        return result;
    }
    // void param_callback2(const rcl_interfaces::msg::SetParametersResult &result)
    // {
    //     if (!result.successful)
    //     {
    //         RCLCPP_INFO(this->get_logger(), "Not all parameters were set.");
    //     }
    // }

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
