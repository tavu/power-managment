#include"node.h"
#include"defs.h"
#include <cmath>
#include<stdlib.h>
#define MAX_PACK 5

using namespace std;

bool node::addRssi(char rssi)
{
    if(rssi<0 )
    {
        return false;
    }
    count++;
    ewma_add(&avg,rssi);

    return true;
}

void node::ackReceived(char rssi)
{
    ackRssi=rssi;
}

bool node::needSend()
{
    if(count<MAX_PACK)
    {
        return false;
    }
    int rssi=rssiAvg();

    //already knows
    if(ackRssi>0 && (abs(ackRssi - rssi) < TX_CONST) )
    {
        return false;
    }

    if( rssi> 0  &&  abs(PERF_RSSI - rssi) > TX_CONST)
    {
        return true;
    }

    return false;
}

node* node::nodeFromIp(string ip)
{
    char mac_add[18];

    string cmd = "arp -n -i ";
    cmd.append(WLAN);
    cmd.append("|grep -i ");
    cmd.append(ip);
    cmd.append("|awk '{print $3}'");

    //   cout<<cmd.c_str()<<endl;

    FILE *fp = popen(cmd.c_str(),"r");
    if(fp==NULL)
    {
        return 0;
    }

//     mac_add=(char*)malloc(16*sizeof(char) );
    if(fgets(mac_add,18,fp)==NULL)
    {
        pclose(fp);
        return 0;
    }

    pclose(fp);

    int i=0;
    while (mac_add[i])
    {
        mac_add[i]=(char) ( toupper(mac_add[i]) );
        i++;
    }

    string mac=string(mac_add);


    return new node(mac,ip);

}

node* node::nodeFromMac(string mac)
{
    char ip_add[18];

    string cmd = "arp -n -i ";
    cmd.append(WLAN);
    cmd.append("|grep -i ");
    cmd.append(mac);
    cmd.append("|awk '{print $1}'");

    //   cout<<cmd.c_str()<<endl;

    FILE *fp = popen(cmd.c_str(),"r");
    if(fp==NULL)
    {
        return 0;
    }

//     mac_add=(char*)malloc(16*sizeof(char) );
    if(fgets(ip_add,18,fp)==NULL)
    {
        pclose(fp);
        return 0;
    }

    pclose(fp);

    string ip=string(ip_add);

    return new node(mac,ip);

}
