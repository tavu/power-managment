#include"sender.h"

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include"defs.h"
#include"message.h"

#define RSSI_FILE "/proc/rssi"
#define LOG_F "sender.log"
using namespace std;

sender::sender()
    :log(LOG_F)

{}

int sender::run()
{
    input.open(RSSI_FILE,std::ios::in);

    while(1)
    {
        struct packet_info packet =readRssi();

        if(packet.rssi<0)
        {
            log<<"SENDER: negative rssi"<<endl;
            continue ;
        }

        log<<"RSSI_READ: "<<packet.mac_addr<<" "<<packet.rssi<<endl;

        string mac=string(packet.mac_addr);
        int rssiAvg=-1;

        nMap()->lock();
        node *n=nMap()->nodeFromMac(mac);
        nMap()->unlock();

        if(n==0)
        {
            log<<"\tUNKOWN MAC "<<packet.mac_addr<<endl;
            continue;
        }

        n->addRssi(packet.rssi);
        rssiAvg=n->rssiAvg();

        nMap()->lock();
        if(n->needSend() )
        {
            nMap()->unlock();
            log<<"\tsend message"<<packet.mac_addr<<" "<<packet.rssi<<endl;
            soc->sendRssiMessage(n->ip(),rssiAvg);
        }
        else
        {
            nMap()->unlock();
        }
    }
    return 0;
}



struct packet_info sender::readRssi()
{
    struct packet_info packet;
    char info[35];
    char rssiC[4];

    memset(packet.mac_addr,'\0',18);
    memset(rssiC,'\0',4);
    input.getline(info,35);

    char *p=info+5;

    int i=0;
    while(*p!=' ')
    {
        rssiC[i]=*p;
        p++;
        i++;
        if(i==3)
        {
            packet.rssi = -1;
            return packet;
        }
    }

    packet.rssi = atoi(rssiC);

    if(packet.rssi<0)
    {
        cout<<"ERR:negative rssi\n"<<endl;
    }

    p+=5;

    strncpy(packet.mac_addr,p,18);

    return packet;
}