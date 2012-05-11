#include"base_receiver.h"
#include"sender.h"
#include"nodeMap.h"
#include"socketC.h"
int main()
{
    nodeMap m;
    sender send;
    socketC s;

    baseReceiver receiver;

    send.setMap(&m);
    receiver.setMap(&m);
    send.setSocket(&s);
    receiver.setSocket(&s);

    receiver.start();
    send.start();
    return 0;
} 
