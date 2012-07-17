#ifndef RECEIVER_H
#define RECEIVER_H

#include <pthread.h>
#include "socketC.h"
#include <fstream>
#include "thread.h"
#define LOG_F "receiver.log"
#define TX_LOG "tx.log"

class receiver :public Thread
{
    public:
        receiver();

        virtual ~receiver()
        {
            log.close();
        };

        int setPower(char rssi);

        void setSocket(socketC *s)
        {
            soc=s;
        }

        int run();

    protected:

        virtual void rssiReceived(std::string ip,char rssi)=0;
        void sendRssiAck(std::string ip,char rssi);
        virtual void handShR(std::string ip)=0;
        int setAbsPower(char tx_new);
        
        std::ofstream log;
        socketC *soc;
        
    private:

        std::ofstream txLog;
        char curr_tx;
};

#endif