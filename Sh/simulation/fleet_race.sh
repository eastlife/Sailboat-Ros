#!/usr/bin/env bash
nohup roslaunch sailboat_launch start_tf_tree_onboat.launch &
sleep 5s
nohup roslaunch sailboat_simulation fleet_race_simulation.launch &
sleep 5s
nohup rosrun rviz rviz -d rviz/sim.rviz &
sleep 3s
nohup rosrun rqt_gui rqt_gui --perspective-file rqt/sim.perspective &
sleep 3s
echo "start fleet_race simulation"
rosnode list