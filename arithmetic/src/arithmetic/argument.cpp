#include "arithmetic/argument.hpp"

Argument::Argument() : Node("argument"), _min_random_num(0.0), _max_random_num(0.0)
{
    declare_parameter("min_random_num", 0.0);
    declare_parameter("max_random_num", 9.0);
    _min_random_num = get_parameter("min_random_num").get_value<float>();
    _max_random_num = get_parameter("max_random_num").get_value<float>();

    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    _publisher = create_publisher<interface_example::msg::ArithmeticArgument>("arithmetic_argument", qos_profile);
    _parameter_event_sub = create_subscription<rcl_interfaces::msg::ParameterEvent>(
        "/parameter_events",
        qos_profile,
        std::bind(&Argument::param_event_callback,
                  this,
                  std::placeholders::_1));
    _timer = create_wall_timer(1s, std::bind(&Argument::pub_callback, this));
}

void Argument::pub_callback()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(_min_random_num, _max_random_num);

    auto msg = interface_example::msg::ArithmeticArgument();
    msg.argument_a = dis(gen);
    msg.argument_b = dis(gen);

    _publisher->publish(msg);
    RCLCPP_INFO(get_logger(), "Published: {a: %f, b: %f}", msg.argument_a, msg.argument_b);
}

void Argument::param_event_callback(const rcl_interfaces::msg::ParameterEvent::SharedPtr event)
{
    for (auto &changed_parameter : event->changed_parameters)
    {
        if (changed_parameter.name == "min_random_num")
        {
            auto value = rclcpp::Parameter::from_parameter_msg(changed_parameter).get_value<float>();
            _min_random_num = value;
        }
        else if (changed_parameter.name == "max_random_num")
        {
            auto value = rclcpp::Parameter::from_parameter_msg(changed_parameter).get_value<float>();
            _max_random_num = value;
        }
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
    rclcpp::spin(std::make_shared<Argument>());
    rclcpp::shutdown();
    return 0;
}