#include <navigation.hpp>

Navigation::Navigation() {
    velocityRotate.angular.z = 0.5;
    velocityForward.linear.x = 0.3;
}

void Navigation::scanCallback(const sensor_msgs::LaserScanConstPtr& scan) {
    if (maxDistance != 4) maxDistance = 4;
    for (std::vector<float>::const_iterator i = scan->ranges.begin()+rangeSize;
            i != scan->ranges.end()-rangeSize;
            i++) {
        if (*i < maxDistance) maxDistance = *i;
    }
}

void Navigation::run() {
    while (ros::ok()) {
        std::cout<<maxDistance<<std::endl;
        if (maxDistance < 0.5) velocityPublisher.publish(velocityRotate);
        else velocityPublisher.publish(velocityForward);
        ros::spinOnce();
    }
}

int main(int argc, char **argv){
    ros::init(argc, argv, "week12");
    Navigation navigate;
    ros::Rate loop_rate(10);

    navigate.run();
}
