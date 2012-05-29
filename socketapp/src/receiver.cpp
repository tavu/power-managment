#include <stdio.h>
#include <string.h>
#include<iostream>
#include <stdlib.h>
#include <time.h>

#include"receiver.h"
#include"message.h"
#include"defs.h"
#include "nodeMap.h"

#include <signal.h>
#include <unistd.h>


#define BUFF_S 3

using namespace std;

receiver::receiver() :Thread(),log(LOG_F)
{
    curr_tx=TX_DEF;
}

int receiver::run()
{
    log<<"Starting"<<endl;

    int k=soc->bindSocket();
    if(k!=0)
    {
        log<<"could not bind socket"<<endl;
        log<<"ERR "<<k<<endl;
        return 0;
    }

    while(1)
    {
        struct mechMes m=soc->received();

        log<<"[RECEIVED]"<<m.ip<<endl;

        if(m.type==HELLOW )
        {
            log<<'\t'<<"hello"<<endl;
            continue;
        }
        else if(m.type==RSSI_M)
        {
            log<<'\t'<<"rssi "<<(int)m.value<<endl;
            rssiReceived(m.ip,m.value );
            soc->sendAck(m.ip,m.value);
        }
        else if(m.type==ACK)
        {
            log<<'\t'<<"ack "<<(int)m.value<<endl;

            nMap()->lock();
            node *n=nMap()->nodeFromIp(m.ip);
            if(n!=0)
            {
                n->ackReceived(m.value);
            }
            nMap()->unlock();
        }
        else if(m.type==HNDSH_R)
        {
            log<<'\t'<<"handshake req"<<endl;
            handShR(m.ip);
        }
        else if(m.type==HNDSH_A)//ack to handshake
        {
            log<<'\t'<<"handshake ack "<<endl;
            nMap()->lock();
            nMap()->setHandSh(true);
            nMap()->unlock();
        }
    }
    return 0;
}

int receiver::setPower(char rssi)
{
    if(rssi<0 )
    {
        return -1;
    }

    char path_loss = curr_tx - rssi;
    char tx_new;
    tx_new=PERF_RSSI+path_loss;

    if(tx_new <TX_MIN)
        tx_new=TX_MIN;

    if(tx_new >TX_MAX)
        tx_new=TX_MAX;

    if(tx_new!=curr_tx)
    {
        char foo[3];
        string cmd = "iwconfig ";
        cmd+=WLAN;
        cmd+=" txpower ";
        sprintf(foo,"%d",tx_new);
        cmd.append(foo);

        time_t t=time(NULL);
        if(system(cmd.c_str()) !=0)
        {
            cout<<"error on system command"<<endl;
            return -1;
        }

        txLog.open(TX_LOG,std::ios::out | std::ios::app);
        int txl=curr_tx;
        txLog<<t<<'\t'<<txl;
        txl=tx_new;
        txLog<<'\t'<<txl<<endl;
        curr_tx=tx_new;
        txLog.close();

        log<<'\t'<<cmd<<endl;
    }

    return 0;
}
