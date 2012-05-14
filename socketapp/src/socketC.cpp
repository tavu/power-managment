#include"socketC.h"
#include<stdlib.h>
#include<cstring>
#include<iostream>
using namespace std;

#include <arpa/inet.h>

#include"defs.h"
#include"message.h"

using namespace std;
void socketC::init()
{
    sockfd = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
}

int socketC::bindSocket()
{
    memset(&bindSa, 0, sizeof bindSa);
    bindSa.sin_family = PF_INET;
    bindSa.sin_port = SPORT;
    bindSa.sin_addr.s_addr = INADDR_ANY;
    socklen_t len = sizeof(peer);

    return bind(sockfd,(struct sockaddr *)&bindSa,sizeof(bindSa) );
}

struct mechMes socketC::received()
{
    while(1)
    {
        std::cout<<"waiting message"<<std::endl;
        memset(buff,0,BUFF_S+1);
        if(recvfrom(sockfd,buff,BUFF_S,0,(struct sockaddr *)&peer,&len) > 0)
        {
            if(buff[0]==MECH )
            {
                break ;
            }
        }
    }

    struct mechMes message;
    message.type=buff[1];
    message.value=buff[2];
    message.ip=std::string(inet_ntoa(peer.sin_addr) );

    cout<<"message received "<<message.type<<endl;

    return message;
}

int socketC::sendHsh(string ip)
{
    char buff[3];
    buff[0]=MECH;
    buff[1]=HNDSH_R;
    buff[2]='\0';

    return sendMessage(ip,buff,3);
}



int socketC::sendAck(string ip, char rssi )
{
    char buff[3];
    buff[0]=MECH;
    buff[1]=ACK;
    buff[2]=rssi;

    return sendMessage(ip,buff,3);
}

int socketC::sendHshAck(string ip)
{
    char buff[3];
    buff[0]=MECH;
    buff[1]=HNDSH_A;
    buff[2]=0;

    return sendMessage(ip,buff,3);
}


int socketC::sendRssiMessage(string ip,char rssi)
{
    char buff[3];
    buff[0]=MECH;
    buff[1]=RSSI_M;
    buff[2]=rssi;

    return sendMessage(ip,buff,3);
}

int socketC::sendHellow(string ip)
{
    char buff[3];
    buff[0]=MECH;
    buff[1]=HELLOW;
    buff[2]='\0';

    return sendMessage(ip,buff,3);
}

int socketC::sendMessage(string ip,char* buff, int size)
{
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof sa);
    sa.sin_family = PF_INET;
    sa.sin_port = SPORT;
    sa.sin_addr.s_addr = inet_addr(ip.c_str() );

    sendto(sockfd,buff,size,0,(struct sockaddr *)&sa,sizeof(sa));

    return 0;
}
