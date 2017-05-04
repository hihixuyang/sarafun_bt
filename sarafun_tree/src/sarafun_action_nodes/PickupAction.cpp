#include <sarafun_tree/sarafun_action_nodes/PickupAction.h>

namespace sarafun {
bool PickupAction::fillGoal(sarafun_msgs::PickUpKeyframeGoal &goal) {
  bool prev_result;

  if (idx_list_.size() == 0)
  {
    if(!fillParameter("/sarafun/pick_up/idx", idx_list_))
    {
      goal.idx = 0;
      return false;
    }
  }

  goal.idx = idx_list_[curr_idx_];
  curr_idx_++;

  if (curr_idx_ >= idx_list_.size())
  {
    curr_idx_ = 0;
  }

  return true;
}

double PickupAction::getTimeoutValue() {
  double timeout = 0;
  fillParameter("/sarafun/bt_action_nodes/pickup/timeout", 30.0, timeout);

  return timeout;
}
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "PickupAction");
  std::string bt_client_name, action_server_name;

  if (!ros::param::get("/sarafun/bt_action_nodes/pickup/action_server_name", action_server_name))
  {
    ROS_ERROR("%s missing action server name", ros::this_node::getName().c_str());
    return -1;
  }

  if (!ros::param::get("/sarafun/bt_action_nodes/pickup/bt_client_name", bt_client_name))
  {
    ROS_ERROR("%s missing bt client name", ros::this_node::getName().c_str());
    return -1;
  }

  sarafun::PickupAction pickup_action(
      ros::this_node::getName(),  action_server_name, bt_client_name);
  ros::spin();
  return 1;
}
