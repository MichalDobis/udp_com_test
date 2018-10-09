//
// Created by controller on 10/9/18.
//


#include "udp_com_test/udp_client.h"
#include "udp_com_test/ati_netft.h"
#include <ros/ros.h>

int main(int argc, char** argv) {
    ROS_INFO_STREAM_NAMED("hardware_interface", "Starting hardware interface...");

    ros::init(argc, argv, "udp_test_node");

    UDPClient client("192.168.1.1", 49152);


    AtiNetFT::RDTCommand command;
    command.command_header_ = 0x1234;
    command.command_ = 2;
    command.sample_count_ = 0;

    char buffer_send[AtiNetFT::RDT_COMMAND_SIZE];
    memset(buffer_send, 0, AtiNetFT::RDT_COMMAND_SIZE);
    AtiNetFT::pack(buffer_send, command);


    while(ros::ok()) {

        int bytes = client.send(buffer_send,AtiNetFT::RDT_COMMAND_SIZE );
        ROS_INFO("Send bytes %d", bytes);
        if (bytes < 0) {
            std::cout << "ERROR in sendto" << std::endl;
        }
        char buffer_read[AtiNetFT::RDT_RECORD_SIZE +1 ];
        memset(buffer_read, 0, AtiNetFT::RDT_RECORD_SIZE+1);

        bytes = client.recv(buffer_read, AtiNetFT::RDT_RECORD_SIZE+1);
        ROS_INFO("received bytes %d", bytes);

        AtiNetFT::RDTRecord data = AtiNetFT::unpack(buffer_read);
        ROS_WARN("ft x %d y %d z %d",bytes, data.fx_, data.fy_, data.fz_);

        sleep(1);

    }

    sleep(4);
}