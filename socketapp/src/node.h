#ifndef NODE_H
#define NODE_H

#include"average.h"

#include"iostream"
#include<string>

class node
{
    public:
        node(std::string mac,std::string ip) :_mac(mac),_ip(ip)
        {
            count=0;
//             _lastRssi=-1;
            ackRssi=-1;
            _mySignal=20;
            ewma_init(&avg,2,2);
        }
        node()
        {}

        bool addRssi(char rssi);

        void clear()
        {
            count=0;
            ewma_init(&avg,2,2);
        }

        char rssiAvg()
        {
            return (char)ewma_read(&avg);
        }

        std::string mac()
        {
            return _mac;
        }

        std::string ip()
        {
            return _ip;
        }

//         char lastAvgRssi()
//         {
//             return _lastRssi;
//         }

        char mySignal()
        {
            return _mySignal;
        }

        void setMySignal(char s)
        {
            _mySignal=s;
        }

        bool needSend();

        void ackReceived(char rssi);

        static node* nodeFromMac(std::string mac);
        static node* nodeFromIp(std::string ip);


    private:
        struct ewma avg;
        std::string _mac;
        std::string _ip;
//         char _lastRssi;
        char ackRssi;
        char _mySignal;

//         bool hasInformed;
        short count;
};




#endif