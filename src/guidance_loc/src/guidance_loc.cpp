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
 
#include "guidance_loc.h"

GuidanceLoc::GuidanceLoc() : nh("~")
{
    guidance_odom_sub = nh.subscribe("guidance/odom", 10, &GuidanceLoc::guidance_odom_callback, this);
    guidance_odom_bias_sub = nh.subscribe("guidance/odom_bias", 10, &GuidanceLoc::guidance_odom_bias_callback, this);
    guidance_odom_calied_pub = nh.advertise<nav_msgs::Odometry>("guidance/odom_calied", 10);
    guidance_cali_srv = nh.advertiseService("guidance/cali", &GuidanceLoc::guidance_cali_callback, this);
}

void GuidanceLoc::cali(const nav_msgs::Odometry& g_odom_bias)
{
    odom_bias = g_odom_bias;

    double yaw = tf::getYaw(odom.pose.pose.orientation);
    double yaw_bias = tf::getYaw(g_odom_bias.pose.pose.orientation);
    double yaw_calied = yaw - yaw_bias;
    geometry_msgs::Quaternion quat_calied = tf::createQuaternionMsgFromYaw(yaw_calied);

    odom_calied.header = odom.header;
    odom_calied.child_frame_id = odom.child_frame_id;
    odom_calied.pose.pose.position.x = odom.pose.pose.position.x - g_odom_bias.pose.pose.position.x;
    odom_calied.pose.pose.position.y = odom.pose.pose.position.y - g_odom_bias.pose.pose.position.y;
    odom_calied.pose.pose.position.z = odom.pose.pose.position.z - g_odom_bias.pose.pose.position.z;
    odom_calied.pose.pose.orientation = quat_calied;
    odom_calied.twist = odom.twist;

    calied = true;
}

void GuidanceLoc::guidance_odom_callback(const nav_msgs::OdometryConstPtr& g_odom)
{
    odom = *g_odom;
    std::cout << "callback" << std::endl;
    if (calied == false)
    {
        cali(odom);
    }
}

void GuidanceLoc::guidance_odom_bias_callback(const nav_msgs::OdometryConstPtr& g_odom_bias)
{
    cali(*g_odom_bias);
}

bool GuidanceLoc::guidance_cali_callback(guidance_loc::GuidanceLocCali::Request& request, guidance_loc::GuidanceLocCali::Response& response)
{
    odom_bias.pose.pose = request.pose;
    cali(odom_bias);
    response.pose = odom_calied.pose.pose;
    return true;
}

void GuidanceLoc::publish_odom_calied()
{
    guidance_odom_calied_pub.publish(odom_calied);
}

