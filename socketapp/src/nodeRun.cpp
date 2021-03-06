#include"node_receiver.h"
#include"sender.h"
#include"nodeMap.h"
#include"socketC.h"
#include"hello.h"
#include<pthread.h>
#include"nodeMap.h"
#include <signal.h>

helloMessage *hl;
sender *Send;
nodeReceiver *Rec;
socketC *SocR;
socketC *SocS;
socketC *SocH;

void leave(int sig);

int main()
{
    (void) signal(SIGINT,leave);
    (void) signal(SIGTERM,leave);

    nodeMap::init();
    std::string ip("10.0.0.2");
    node *n=node::nodeFromIp(ip);
    if(n==0)
    {
        std::cout<<"error initialising the node"<<std::endl;
        return 1;
    }

    std::cout<<n->mac()<<" "<<n->ip()<<std::endl;

    nMap()->addNode(n);

    SocR =new socketC();
    SocS =new socketC();
    SocH =new socketC();

    Send =new sender();
    Rec =new nodeReceiver(ip);
    hl=new helloMessage(ip);

    SocR->init();
    SocH->init();
    SocS->init();

    Send->setSocket(SocS);
    Rec->setSocket(SocR);
    hl->setSocket(SocH);

    Rec->start();
    hl->start();
    Send->start();
    hl->join();

    return 0;
}

void leave(int sig)
{
    Rec->cancel();
    Send->cancel();
    hl->cancel();

    delete hl;
    delete Rec;
    delete Send;
    nodeMap::clear();
    delete SocR;
    delete SocH;
    delete SocS;
}
