#include "arithmetic/operator.hpp"

Operator::Operator(const rclcpp::NodeOptions &options)
    : Node("operator", options)
{
    _service = create_client<ArithmeticOperator>("arithmetic_operator");
    _timer = create_wall_timer(1s, std::bind(&Operator::timer_callback, this));
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
    // TODO: random operator or parameter
    request->arithmetic_operator = request->PLUS;

    auto result_future = _service->async_send_request(
        request, std::bind(&Operator::response_callback, this,
                           std::placeholders::_1));
}

void Operator::response_callback(rclcpp::Client<ArithmeticOperator>::SharedFuture future)
{
    auto status = future.wait_for(1s);
    if (status == std::future_status::ready)
    {
        // TODO: operator 내부 변수 저장후 로깅.
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