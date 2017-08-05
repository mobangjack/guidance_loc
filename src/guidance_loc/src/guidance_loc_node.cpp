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

int main(int argc, char** argv)
{
    ros::init(argc, argv, "guidance_loc_node");

    int spin_rate = 30;

    ros::NodeHandle np("~");
    np.param<int>("spin_rate", spin_rate, 30);

    GuidanceLoc guidance_loc;


    std::cout << "\n---------------------------guidance_loc node started----------------------------" << std::endl;
    std::cout << "                                                                         \n       111                      111                                      \n       111                      111                                      \n       111             1111     111                                      \n       111             1111     111                                      \n       111             1111     111                                      \n       111  1111111  111111111  11111111   1111111  111111111   11111111 \n       111 1111 1111   1111     1111 111  1111 111  11111 111  111 111   \n       111 111   111   1111     111  1111 11    111 1111  111  111  111  \n 111   111 111111111   1111     111   111    111111 111   111  111 1111  \n 111   111 111         1111     111   111 111111111 111   111  1111111   \n 111  1111 111         1111     111   111 111   111 111   111  111111    \n 111  111  1111  111    111     111  1111 111  1111 111   111  111       \n  1111111   11111111    111111  11111111  111111111 111   111  11111111  \n   11111     11111       11111  1111111    11111111 111   111  111  1111 \n                                                              111    111 \n                                                               11111111  " << std::endl;
    
    std::cout << "\n----------------------------Copyright 2017. Jetbang----------------------------" << std::endl;   
    
    ros::Rate rate(spin_rate);
    while (ros::ok())
    {
        ros::spinOnce();

        guidance_loc.publish_odom_calied();

        rate.sleep();
    }
    
    return 0;
}
