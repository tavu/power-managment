#include"base_receiver.h"
#include"sender.h"
#include"nodeMap.h"
#include"socketC.h"
#include <signal.h>

#include <unistd.h>

sender *Send;
baseReceiver *Rec;
socketC *Soc;

void leave(int sig);

int main()
{
    (void) signal(SIGINT,leave);
    (void) signal(SIGTERM,leave);

    nodeMap::init();

    Soc =new socketC();
    Send =new sender();
    Rec =new baseReceiver();

    Soc->init();

    Send->setSocket(Soc);
    Rec->setSocket(Soc);

    Rec->start();
    Send->start();
    Rec->join();
}

void leave(int sig)
{
    Rec->cancel();
    Send->cancel();

    delete Rec;
    delete Send;
    nodeMap::clear();
    delete Soc;
}