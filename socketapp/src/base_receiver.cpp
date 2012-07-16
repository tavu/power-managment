#include"base_receiver.h"
#include"defs.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <list>
#include <string>
#include "nodeMap.h"
/*
#include <arpa/inet.h>
#include <unistd.h>*/

using namespace std;
typedef std::map<std::string,node*>::iterator nodeIter;

void baseReceiver::rssiReceived(string ip,char value)
{
    if(value<0)
    {
        return ;
    }
    lock();

    nMap()->lock();
    node *n=nMap()->nodeFromIp(ip);
    nMap()->unlock();

    if(n==0)
    {
        return ;
    }

    n->setMySignal(value);    

    if(low_nodes.empty() )
    {
        low_rssi=value;
        low_nodes.push_front(ip);
        log<<"\tnew lowest "<<(int)low_rssi<<" "<<ip<<endl;
    }
    else
    {
        if(value < low_rssi)
        {
            low_rssi = value;
            low_nodes.clear();
            low_nodes.push_front(ip);
            log<<"\tnew lowest "<<(int)low_rssi<<" "<<ip<<endl;
        }
        else if(value > low_rssi)
        {
            std::list <std::string>::iterator it;
            for(it = low_nodes.begin(); it != low_nodes.end() ; it++)
            {
                if( ip == *it)
                {
                    low_nodes.erase(it);
                    break;
                }
            }

            if(low_nodes.empty())
            {
                low_rssi=find_lowest();
                log<<"new lowest "<<(int)low_rssi<<endl;
            }
        }
        else if(value == low_rssi)
        {
            std::list <std::string>::iterator it;
            for(it = low_nodes.begin(); it != low_nodes.end() ; it++)
            {
                if ( ip == *it)
                {
                    break;
                }
            }
            if (it == low_nodes.end())
                low_nodes.push_front(ip);
        }
    }

    if(abs(PERF_RSSI - low_rssi) > TX_CONST)
    {
        setPower(low_rssi);
        clear();
    }
    unlock();
}

void baseReceiver::clear()
{
    nMap()->lock();
    nodeMap::nodeIter it=nMap()->ipBegin();

    for(; it != nMap()->ipEnd(); it ++)
    {
        nMap()->nodeFromIt(it)->clear();
    }
    nMap()->unlock();
}

char baseReceiver::find_lowest()
{
    nMap()->lock();
    nodeMap::nodeIter it=nMap()->ipBegin();
    
    if(it==nMap()->ipEnd() )
    {
      return PERF_RSSI;
    }
    
    char lowest = nMap()->nodeFromIt(it)->mySignal();
    it ++;

    for(; it != nMap()->ipEnd(); it ++)
    {
        char signal=nMap()->nodeFromIt(it)->mySignal();
        if( signal< lowest)
            lowest = signal;
    }

    for(it=nMap()->ipBegin(); it != nMap()->ipEnd(); it ++)
    {
        char signal=nMap()->nodeFromIt(it)->mySignal();
        if(signal == lowest)
            low_nodes.push_front(nMap()->nodeFromIt(it)->ip());
    }
    nMap()->unlock();

    return lowest;
}

void baseReceiver::handShR(string ip)
{
/*
    nMap()->lock();
    if(nMap()->nodeFromIp(ip)!=0 )
    {
        nMap()->unlock();;
        return ;
    }
    nMap()->unlock();
*/

    node *n=node::nodeFromIp(ip);
    if(n!=0)
    {
        nMap()->lock();
        nMap()->addNode(n);
        nMap()->unlock();
        cout<<"sendAck"<<endl;
        soc->sendHshAck(ip);
    }
}


void baseReceiver::checkForTimeouts()
{
    lock();
    nMap()->lock();
    nodeIter cnode = nMap()->ipBegin();
    while(cnode!=nMap()->ipEnd() )
    {
            
      if(nMap()->nodeFromIt(cnode) -> getHelloMessages() == 0)
      {
	//sdf
	if(low_rssi== nMap()->nodeFromIt(cnode)->mySignal())
	{
	  low_nodes.remove( nMap()->nodeFromIt(cnode)->ip() );
	}
	nodeIter delI=cnode;
	cnode++;
	nMap()->delete_node(nMap()->nodeFromIt(delI));
      }
      else
      {
	nMap()->nodeFromIt(cnode) -> resetHelloMessages();
	cnode++;
      }
    }
    

    nMap()->unlock();
    
    low_rssi=find_lowest();
    if(abs(PERF_RSSI - low_rssi) > TX_CONST)
    {
        setPower(low_rssi);
        clear();
    }
    unlock();
}