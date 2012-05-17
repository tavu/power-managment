#ifndef SOCKETC_H
#define SOCKETC_H

#include<string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFF_S 3
struct mechMes
{
    std::string ip;
    char value;
    char type;
};

class socketC
{
    public:

        socketC(){}
        ~socketC()
        {
            closeFd();
        }

        void init();
        int bindSocket();
        struct mechMes received();

        int sendRssiMessage(std::string ip,char rssi);
        int sendHellow(std::string ip);
        int sendAck(std::string ip,char rssi);
        int sendHsh(std::string ip);
        int sendHshAck(std::string ip);

        void closeFd()
        {
            close(sockfd);
        }


    protected:
        int sendMessage(std::string ip, char*buff, int size);

    private:
        struct sockaddr_in peer, bindSa;
        socklen_t len;
        int sockfd;
        char buff[BUFF_S+1];
};

#endif
