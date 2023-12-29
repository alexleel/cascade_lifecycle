#include <exception>
#include <memory>
#include <string>

#include <rclcpp_cascade_lifecycle/base_lifecycle_manager.hpp>
#include <rclcpp_cascade_lifecycle/cascade_manager.hpp>

int main(int argc, char ** argv)
{
    try {
        rclcpp::init(argc, argv);
    } catch (rclcpp::ParameterTypeException &) {
        std::cerr << std::string("Parameter type exception catched.") << std::endl;
    }

	auto base_node = std::make_shared<rclcpp_cascade_lifecycle::base_lifecycle_manager>();

	bool started = false;
	while(!started) {
		started =  base_node->auto_check(rclcpp_cascade_lifecycle::CHECK_TO_START);
	}

	rclcpp::executors::MultiThreadedExecutor exec_;
	exec_.add_node(base_node->get_node_base_interface());
	exec_.spin();
  	rclcpp::shutdown();

    return 0;

}

