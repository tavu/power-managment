#ifndef SENDER_H
#define SENDER_H

#include"node.h"
#include <iostream>
#include <fstream>
#include"nodeMap.h"
#include"socketC.h"
#include "thread.h"

struct packet_info
{
  int rssi;
  char mac_addr[18];
};

class sender :public Thread
{
    public:
        sender();
        ~sender()
        {
            soc->closeFd();
            input.close();
        }
        int run();

        void setSocket(socketC *s)
        {
            soc=s;
        }

    private:
        std::ifstream input;
        std::ofstream log;
        struct packet_info readRssi();
        socketC *soc;
};

#endif