#ifndef UDP_SERVER_
#define UDP_SERVER_

#include <iostream>
#include <string>
#include <stdexcept>

// Select includes
#include <sys/time.h>

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ros/ros.h>

class UDPClient
{
public:

  UDPClient(std::string host, unsigned short port)
  {

    if ( (sockfd_=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
      ROS_ERROR("Cannot create socket");
    }

    memset(&clientaddr_, 0, sizeof(clientaddr_));
    clientaddr_.sin_family = AF_INET;
    clientaddr_.sin_addr.s_addr = inet_addr(host.c_str());
    clientaddr_.sin_port = htons(port);
    clientlen_ = sizeof(clientaddr_);

    }

  ~UDPClient()
  {
    close(sockfd_);
  }


  int send(char* buffer, int size)
  {
      return sendto(sockfd_, buffer, size , 0, (struct sockaddr *) &clientaddr_, clientlen_);
  }

  int recv(char* buffer, int size){
      memset(buffer, 0, size);
      return recvfrom(sockfd_, buffer, size, 0, (struct sockaddr *) &clientaddr_, &clientlen_);
  }

private:

  int sockfd_;
  socklen_t clientlen_;
  struct sockaddr_in clientaddr_;
};

#endif

