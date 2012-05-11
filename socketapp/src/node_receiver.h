#ifndef NODE_RECEIVER_H
#define NODE_RECEIVER_H

#include"receiver.h"
#include"defs.h"
#include <cmath>
#include<string>

class nodeReceiver :public receiver
{
    public:
        nodeReceiver(std::string s):receiver(),bIp(s){}


    protected:

        std::string bIp;

        virtual void rssiReceived(std::string ip,char rssi)
        {
            if(ip==bIp && std::abs(PERF_RSSI - rssi) > TX_CONST)
            {
                setPower(rssi);
            }
        }

        virtual void handShR(std::string ip)
        {
            return ;
        }

};

#endif


