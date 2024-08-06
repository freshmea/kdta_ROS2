#include "arithmetic/operator.hpp"

Operator::Operator(const rclcpp::NodeOptions &options)
    : Node("operator", options), _arithmetic_operator(1)
{

    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _service = create_client<ArithmeticOperator>("arithmetic_operator");
    _timer = create_wall_timer(1s, std::bind(&Operator::timer_callback, this));

    declare_parameter("random", true);
    _random_state = get_parameter("random").get_value<bool>();
    _parameter_event_sub = create_subscription<rcl_interfaces::msg::ParameterEvent>(
        "/parameter_events",
        qos_profile,
        std::bind(&Operator::param_event_callback,
                  this,
                  std::placeholders::_1));
}
void Operator::param_event_callback(const rcl_interfaces::msg::ParameterEvent::SharedPtr event)
{
    for (auto &changed_parameter : event->changed_parameters)
    {
        if (changed_parameter.name == "random")
        {
            auto value = rclcpp::Parameter::from_parameter_msg(changed_parameter).get_value<bool>();
            _random_state = value;
        }
    }
}
void Operator::timer_callback()
{
    while (!_service->wait_for_service(1s)) // 서버연결
    {
        if (!rclcpp::ok())
        {
            RCLCPP_ERROR(get_logger(), "Over time!");
        }
        RCLCPP_INFO(get_logger(), "service not available, waiting again...");
    }
    // 보낼 변수 선언
    auto request = std::make_shared<ArithmeticOperator::Request>();
    if (_random_state)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, 4);
        request->arithmetic_operator = (int8_t)dis(gen);
        _arithmetic_operator = request->arithmetic_operator;
    }
    else
    {
        request->arithmetic_operator = _arithmetic_operator;
    }
    auto result_future = _service->async_send_request(
        request, std::bind(&Operator::response_callback, this,
                           std::placeholders::_1));
}

void Operator::response_callback(rclcpp::Client<ArithmeticOperator>::SharedFuture future)
{
    auto status = future.wait_for(1s);
    if (status == std::future_status::ready)
    {
        RCLCPP_INFO(get_logger(), "Result :%f", future.get()->arithmetic_result);
    }
    else
    {
        RCLCPP_INFO(this->get_logger(), "Service In-Progress...");
    }
}

void print_help()
{
    std::cout << "For argument node:" << std::endl;
    std::cout << "node_name [-h]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -h  : Print this help function" << std::endl;
}

int main(int argc, char *argv[])
{
    if (rcutils_cli_option_exist(argv, argv + argc, "-h"))
    {
        print_help();
        return 0;
    }
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Operator>());
    rclcpp::shutdown();
    return 0;
}