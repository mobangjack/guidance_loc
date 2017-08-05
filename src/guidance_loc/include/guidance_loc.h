/**
 * Copyright (c) 2017, Jack Mo (mobangjack@foxmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include <ros/ros.h>
#include <stdio.h>

#include<tf/transform_broadcaster.h>

#include <nav_msgs/Odometry.h>

#include <std_msgs/Empty.h>
#include <geometry_msgs/TransformStamped.h> //IMU
#include <geometry_msgs/Vector3Stamped.h> //velocity
#include <sensor_msgs/LaserScan.h> //obstacle distance && ultrasonic

#include "guidance_loc/GuidanceLocCali.h"

class GuidanceLoc
{
public:
    GuidanceLoc();
    
protected:
    ros::NodeHandle nh;
    ros::Subscriber guidance_odom_sub;
    ros::Subscriber guidance_odom_bias_sub;
    ros::Publisher guidance_odom_calied_pub;
    ros::ServiceServer guidance_cali_srv;

    bool calied;

public:
    nav_msgs::Odometry odom;
    nav_msgs::Odometry odom_bias;
    nav_msgs::Odometry odom_calied;

    void cali(const nav_msgs::Odometry& odom_bias);
    void publish_odom_calied();

protected:
    void guidance_odom_callback(const nav_msgs::OdometryConstPtr& odom);
    void guidance_odom_bias_callback(const nav_msgs::OdometryConstPtr& g_odom_bias);
    bool guidance_cali_callback(guidance_loc::GuidanceLocCali::Request& request, guidance_loc::GuidanceLocCali::Response& response);

};
