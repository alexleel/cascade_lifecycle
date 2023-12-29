#include <exception>
#include <memory>
#include <string>

#include <rclcpp_cascade_lifecycle/base_lifecycle_manager.hpp>
#include <rclcpp_cascade_lifecycle/simple_cascade_lc_node.hpp>
#include <rclcpp_cascade_lifecycle/cascade_manager.hpp>



int main(int argc, char ** argv)
{
    try {
        rclcpp::init(argc, argv);
    } catch (rclcpp::ParameterTypeException &) {
        std::cerr << std::string("Parameter type exception catched.") << std::endl;
    }

	auto lc_node_a = std::make_shared<simple_cascade_lc_node::simple_cascade_lc_node>("Simple_cascade_lc_NodeA");
	auto lc_node_b = std::make_shared<simple_cascade_lc_node::simple_cascade_lc_node>("Simple_cascade_lc_NodeB");

	rclcpp::executors::MultiThreadedExecutor exec_;
	exec_.add_node(lc_node_a->get_node_base_interface());
	exec_.add_node(lc_node_b->get_node_base_interface());

	exec_.spin();
  	rclcpp::shutdown();

    return 0;

}

