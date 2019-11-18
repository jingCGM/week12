#ifndef INCLUDE_NAVIGATION_HPP_
#define INCLUDE_NAVIGATION_HPP_

/**Copyright (c) 2019 Jing Liang
 * @file       navigation.hpp
 * @date       11/16/2019
 * @brief      The project can roam robot in one scenario. When robot face
 *             obstacles in front, it will rotate until front is clear and
 *             keep moving.
 * @license    This project is released under the BSD-3-Clause License.
 */

#include <ros/ros.h>
#include <math.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

/**
 * @brief Class Navigation is used to subscribe sensor data, detect if there would be
 *        collision in front, and also publish velocities to drive robot rotate or forward
 */
class Navigation {
 private:
    ros::NodeHandle nh;

    // created subscriber and publisher to receive sensor data and publish velocities
    ros::Subscriber scanSubscribe = nh.subscribe<sensor_msgs::LaserScan>("/turtlebot/scan_filtered", 10, &Navigation::scanCallback, this);
    ros::Publisher velocityPublisher = nh.advertise<geometry_msgs::Twist>("/turtlebot/cmd_vel_mux/input/navi", 10);

    geometry_msgs::Twist velocityForward, velocityRotate;

    int rangeSize = round(512/3);  // used for choosing part of sensor range
    float minDistance = 4.0;  // used to record


 public:
    /**
     * @brief constructor of Navigation defining velocities of forward and rotate
     */
    Navigation();

    /**
     * @brief scanCallback function is callback function when receiving
     *        scan data.
     * @param scan data, which is LaserScan.
     */
    void scanCallback(const sensor_msgs::LaserScanConstPtr& scan);

    /**
     * @brief run function drive robot forward when front is clear, and
     *        rotate when front is not clear.
     */
    void run();
};


#endif  // INCLUDE_NAVIGATION_HPP_
