/**Copyright (c) 2019 Jing Liang
 * @file       navigation.cpp
 * @date       11/16/2019
 * @brief      The project can roam robot in one scenario. When robot face
 *             obstacles in front, it will rotate until front is clear and
 *             keep moving. This file is used to bring up the class Navigation
 * @license    This project is released under the BSD-3-Clause License.
 *             Redistribution and use in source and binary forms, with or without
 *             modification, are permitted provided that the following conditions are met:
 *
 *             1. Redistributions of source code must retain the above copyright notice, this
 *                list of conditions and the following disclaimer.
 *
 *             2. Redistributions in binary form must reproduce the above copyright notice,
 *                this list of conditions and the following disclaimer in the documentation
 *                and/or other materials provided with the distribution.
 *
 *             3. Neither the name of the copyright holder nor the names of its
 *                contributors may be used to endorse or promote products derived from
 *                this software without specific prior written permission.
 *
 *             THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *             AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *             IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *             DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *             FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *             DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *             SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *             CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *             OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *             OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <navigation.hpp>

Navigation::Navigation() {
    velocityRotate.angular.z = 0.5;  // set angular velocity
    velocityForward.linear.x = 0.3;  // set linear velocity
}

void Navigation::scanCallback(const sensor_msgs::LaserScanConstPtr& scan) {
    if (minDistance != 4) minDistance = 4;

    // judge is there is obstacle at front
    for (std::vector<float>::const_iterator i = scan->ranges.begin()+rangeSize;
            i != scan->ranges.end()-rangeSize; ++i) {
        if (*i < minDistance) minDistance = *i;
    }
}

void Navigation::run() {
    while (ros::ok()) {
        if (minDistance < 0.5)
            // publish rotate command
            velocityPublisher.publish(velocityRotate);
        else
            // publish forward command
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
