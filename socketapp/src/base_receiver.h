#ifndef BASE_RECEIVER_H
#define BASE_RECEIVER_H
#include"receiver.h"
#include<map>
#include <list>

class baseReceiver :public receiver
{
    public:
        baseReceiver():receiver()
        {
            low_rssi=255;//just a very big value
        };
	void checkForTimeouts();
    protected:
        void rssiReceived(std::string ip,char rssi);
        void handShR(std::string ip);
	

    private:
//         std::map <std::string,char> mapped_network;
        std::list <std::string> low_nodes;
//         std::list <std::string>::iterator it;
        char low_rssi;

        char find_lowest();
        void clear();
};
#endif