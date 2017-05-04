#include <sarafun_tree/sarafun_action_nodes/RetractAction.h>

namespace sarafun {
bool RetractAction::fillGoal(sarafun_msgs::RetractKeyframeGoal &goal) {
  bool prev_result;

  if (idx_list_.size() == 0)
  {
    if(!fillParameter("/sarafun/retract/idx", idx_list_))
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

double RetractAction::getTimeoutValue() {
  double timeout = 0;
  fillParameter("/sarafun/bt_action_nodes/retract/timeout", 30.0, timeout);

  return timeout;
}
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "RetractAction");
  std::string bt_client_name, action_server_name;

  if (!ros::param::get("/sarafun/bt_action_nodes/retract/action_server_name", action_server_name))
  {
    ROS_ERROR("%s missing action server name", ros::this_node::getName().c_str());
    return -1;
  }

  if (!ros::param::get("/sarafun/bt_action_nodes/retract/bt_client_name", bt_client_name))
  {
    ROS_ERROR("%s missing bt client name", ros::this_node::getName().c_str());
    return -1;
  }

  sarafun::RetractAction retract_action(
      ros::this_node::getName(),  action_server_name, bt_client_name);
  ros::spin();
  return 1;
}
