//
// Created by hywel on 17-4-23.
//

#include "autopilot_lib/CAutopilotVer1.h"



//ros::NodeHandle ap_node;
//ros::Publisher mach_pub;
//ros::Subscriber sensor_sub;

CAutopilotVer1::CAutopilotVer1() {

    Kp = 0.5;
    Ki = 0;
    Kd = 0;
    T = 0.1;
    OutMax = 0.52;
    OutMin = -0.52;
    yawFdb = 0;
    yawRef = 0;

    PCCtrl = 0;
    rudder = 0;
    sail = 0;

    Init();

}

CAutopilotVer1::CAutopilotVer1(double kp, double ki, double kd) {
    Kp = kp;
    Ki = ki;
    Kd = kd;
    T = 0.1;
    OutMax = 0.52;
    OutMin = -0.52;
    yawFdb = 0;
    yawRef = 0;

    PCCtrl = 0;
    rudder = 0;
    sail = 0;

    Init();
}

CAutopilotVer1::CAutopilotVer1(double kp, double ki, double kd, double t, double outMax, double outMin) {
    Kp = kp;
    Ki = ki;
    Kd = kd;
    T = t;
    OutMax = outMax;
    OutMin = outMin;
    yawFdb = 0;
    yawRef = 0;

    PCCtrl = 0;
    rudder = 0;
    sail = 0;

    Init();
}

CAutopilotVer1::~CAutopilotVer1() {
    delete pidp;

}

double CAutopilotVer1::Get_Rudder() {
    return rudder;
}

double CAutopilotVer1::Get_Sail() {
    return sail;
}
int CAutopilotVer1::Get_PCCtrl(){
    return PCCtrl;
}
void CAutopilotVer1::Init() {

    pidp=new CPID(Kp,Ki, Kd, T, OutMax,OutMin);

    mach_pub = ap_node.advertise<mach_onboat::Mach_msg>("mach", 5);

    sensor_sub = ap_node.subscribe("sensor", 2, &CAutopilotVer1::SensorCallback,this);
    //sensor_simulation_sub = ap_node.subscribe("sensor", 2, &CHeadingControl::SensorSimulationCallback,this);
    //sailboat_simulation_sub = ap_node.subscribe("sailboat", 2, &CHeadingControl::SailboatSimulationCallback,this);
    ctrl_sub = ap_node.subscribe("targetangle", 2, &CAutopilotVer1::CtrlCallback,this);

}

void CAutopilotVer1::SensorCallback(const sailboat_message::Sensor_msg::ConstPtr &msg) {
    ROS_INFO("I get AWA: [%f]", msg->AWA);
    yawFdb = msg->Yaw;
    AWA = msg->AWA;
    AWS = msg->AWS;
}


//void CHeadingControl::SensorSimulationCallback(const sailboat_message::Sensor_Simulation_msg::ConstPtr& msg){

//}

//void CHeadingControl::SailboatSimulationCallback(const sailboat_message::Sailboat_Simulation_msg::ConstPtr& msg) {
//    ROS_INFO("sailboat_msg sub: [%f]", msg->yaw);
//    yawFdb = msg->yaw;
//}


void CAutopilotVer1::CtrlCallback(const sailboat_message::Target_msg::ConstPtr &msg) {
    ROS_INFO("Tatget_msg sub: [%f]",msg->TargetAngle);
    yawRef = msg->TargetAngle;
}

void CAutopilotVer1::PIDCallback(autopilot_lib::pid_adjustment_Config &config, uint32_t level) {
    ROS_INFO("PID_ad config: [%f] [%f] [%f]",config.Kp,config.Ki,config.Kd);
    Kp = config.Kp /10;
    Ki = config.Ki /10;
    Kd = config.Kd /10;
    pidp->Set_Kp(Kp);
    pidp->Set_Ki(Ki);
    pidp->Set_Kd(Kd);

    if (config.PC_Ctrl == true)
        PCCtrl = 1;
    else
        PCCtrl = 0;

    double p,i,d = pidp->Get_Kpid();
    ROS_INFO("CPID: [%f] [%f] [%f]",p,i,d);
}

void CAutopilotVer1::AP_Calc() {
    pidp->Set_Ref(yawRef);
    pidp->Set_Fdb(yawFdb);
    ROS_INFO("YAWRef and YAWFdb: [%f] [%f]",yawRef,yawFdb);
    //rudder = pidp->PID_Calc();

    rudder = (yawRef-yawFdb)*Kp;
    sail = sailCtrl.GetBestSailAngle2(AWA);
    if (sail> pi/2)
        sail = pi/2;
    else if (sail < -pi/2)
        sail = -pi/2;

    ROS_INFO("sail: [%f]",sail);

}
