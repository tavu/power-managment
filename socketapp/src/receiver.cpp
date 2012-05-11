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

int receiver::run()
{
    (void) signal(SIGUSR1,initTime);
 
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

void receiver::initTime(int)
{
    if(!timeS)
    {
        txLog.open(TX_LOG);
        curr_time=time(NULL);
        start_time=curr_time;
        txSum=0;
        timeS=true;        
    }
    else
    {
        time_t t=curr_time;
        time(&curr_time);
        txLog<<(txSum + curr_tx*(curr_time-t)) /(curr_time-start_time) <<endl;
        timeS=false;
        txLog.close();
    }
}


int receiver::setPower(char rssi)
{
//     curr_tx=TX_DEF;

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
        time_t t=curr_time;
        curr_time=time(NULL);
        
        txSum=+(curr_time-t)*curr_tx;
        
        char foo[3];
        string cmd = "iwconfig ";
        cmd+=WLAN;
        cmd+=" txpower ";
        sprintf(foo,"%d",tx_new);
        cmd.append(foo);

        if(system(cmd.c_str()) !=0)
        {
            printf("error on system command\n");
            return -1;
        }
        log<<'\t'<<cmd<<endl; 
        curr_tx=tx_new;
    }            

    return 0;
}

bool receiver::timeS=false;
long int receiver::txSum=0;
std::ofstream receiver::txLog;

time_t receiver::curr_time;
time_t receiver::start_time;
char receiver::curr_tx=TX_DEF;
