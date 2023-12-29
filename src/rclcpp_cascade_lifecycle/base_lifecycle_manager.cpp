#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "rclcpp_cascade_lifecycle/base_lifecycle_manager.hpp"


namespace rclcpp_cascade_lifecycle
{
base_lifecycle_manager::base_lifecycle_manager()
: rclcpp_cascade_lifecycle::CascadeManager("base_lifecycle_manager", "base_nodes_l")
{}
base_lifecycle_manager::~base_lifecycle_manager()
{
	if (get_current_state().id() ==
		lifecycle_msgs::msg::State::PRIMARY_STATE_ACTIVE) {
		on_deactivate(get_current_state());
		on_cleanup(get_current_state());
	}
	message_info(this->get_name() + std::string(" lifecycle destroyed."));
}


CallbackReturn_T base_lifecycle_manager::on_configure(const rclcpp_lifecycle::State &)
{
	message_info(this->get_name() + std::string(" onconfiguring"));
	if (manager_configure()) {
    	message_info(std::string("Manager internal configured."));
	}
	message_info(get_name() + std::string(" configured."));
  	return CallbackReturn_T::SUCCESS;
}


CallbackReturn_T base_lifecycle_manager::on_activate(const rclcpp_lifecycle::State &)
{
	message_info(get_name() + std::string(" onactivating"));

	if (manager_activate()) {
    	message_info(std::string("Manager internal activated."));
	}

	message_info(get_name() + std::string(" activated."));
  	return CallbackReturn_T::SUCCESS;
}


CallbackReturn_T base_lifecycle_manager::on_deactivate(const rclcpp_lifecycle::State &)
{
	message_info(get_name() + std::string(" deactivating..."));

	if (manager_deactivate()) {
		message_info(std::string("Manager internal deactivated."));
  	}

	message_info(get_name() + std::string(" deactivated."));
  	return CallbackReturn_T::SUCCESS;
}

CallbackReturn_T base_lifecycle_manager::on_cleanup(const rclcpp_lifecycle::State &)
{
  message_info(get_name() + std::string(" cleaning up..."));

  if (manager_cleanup()) {
    message_info(std::string("Manager internal cleaned up."));
  }

  message_info(get_name() + std::string(" completely cleaned up."));
  return CallbackReturn_T::SUCCESS;
}


CallbackReturn_T base_lifecycle_manager::on_shutdown(const rclcpp_lifecycle::State &)
{
  message_info(get_name() + std::string(" error raising..."));

  if (manager_cleanup()) {
    message_info(std::string("Manager internal cleaned up."));
  }

  message_info(get_name() + std::string(" completely cleaned up."));
  
  return CallbackReturn_T::SUCCESS;
}


} // namespace rclcpp_cascade_lifecycle

