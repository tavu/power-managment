#include"hello.h"
#include "nodeMap.h"

#define TIME 1//in seconts

int helloMessage::run()
{
    while(1)
    {
        nMap()->lock();
        if(!nMap()->hasHandSh() )
        {
            nMap()->unlock();
            soc->sendHsh(bIp);
            sleep(TIME);
        }
        else
        {
            nMap()->unlock();
            break ;
        }
    }

    while(1)
    {
        soc->sendHellow(bIp);
        sleep(TIME);
    }
    return 0;
}


