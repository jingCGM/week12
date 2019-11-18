/**Copyright (c) 2019 Jing Liang
 * @file       navigation.cpp
 * @date       11/16/2019
 * @brief      The project can roam robot in one scenario. When robot face
 *             obstacles in front, it will rotate until front is clear and
 *             keep moving. This file is used to bring up the class Navigation
 * @license    This project is released under the BSD-3-Clause License.
 */

#include <navigation.hpp>

Navigation::Navigation() {
    velocityRotate.angular.z = 0.5;
    velocityForward.linear.x = 0.3;
}

void Navigation::scanCallback(const sensor_msgs::LaserScanConstPtr& scan) {
    if (minDistance != 4) minDistance = 4;
    for (std::vector<float>::const_iterator i = scan->ranges.begin()+rangeSize;
            i != scan->ranges.end()-rangeSize; ++i) {
        if (*i < minDistance) minDistance = *i;
    }
}

void Navigation::run() {
    while (ros::ok()) {
        if (minDistance < 0.5)
            velocityPublisher.publish(velocityRotate);
        else
            velocityPublisher.publish(velocityForward);
        ros::spinOnce();
    }
}

/**
 * @brief    main function
 * @param    argc int
 * @param    argv char array
 * @return   0
 */
int main(int argc, char **argv) {
    ros::init(argc, argv, "week12");
    Navigation navigate;
    ros::Rate loop_rate(10);

    navigate.run();
}
