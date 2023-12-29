# `rclcpp-cascade-lifecycle`

Package containing a prototype for rclcpp-cascade-lifecycle implementation and management based on cascade-lifecycle system

## How to run

CLI: ros2 run rclcpp_cascade_lifecycle  base_lifecycle_manager --ros-args -p "base_nodes_l:= ["simple_cascade_lifecycle_node"]" -p "timeout_manager_s:=10"

launch: ros2 launch rclcpp_cascade_lifecycle lc_bringup_launch.py

![image](https://github.com/alexleel/cascade_lifecycle/assets/16509292/ca8ecef5-0dcb-4dae-a8b5-9dd136d96f3e) 


