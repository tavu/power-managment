#ifndef HELLO_H
#define HELLO_H
#include "thread.h"
#include <string.h>

#include "socketC.h"

class helloMessage :public Thread
{
    public:
        helloMessage(std::string ip) :Thread(),bIp(ip){};
        void setSocket(socketC *s)
        {
            soc=s;
        }

        int run();

    private:
        std::string bIp;
        socketC *soc;
};

#endif