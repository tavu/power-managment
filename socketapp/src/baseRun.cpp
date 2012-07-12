#include"base_receiver.h"
#include"sender.h"
#include"nodeMap.h"
#include"socketC.h"
#include"timeout.h"
#include <signal.h>
#include <unistd.h>

sender *Send;
baseReceiver *Rec;
socketC *Soc;
timeoutChecker *Chk;

void leave(int sig);

int main()
{
    (void) signal(SIGINT,leave);
    (void) signal(SIGTERM,leave);

    nodeMap::init();

    Soc =new socketC();
    Send =new sender();
    Rec =new baseReceiver();
    Chk = new timeoutChecker(Rec);

    Soc->init();

    Send->setSocket(Soc);
    Rec->setSocket(Soc);

    Rec->start();
    Chk->start();
    Send->start();
    Rec->join();
    Chk->join();
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