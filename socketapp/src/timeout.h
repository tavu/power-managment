#ifndef TIMEOUT_H
#define TIMEOUT_H

#include "thread.h"
#include "base_receiver.h"
#define TIMEOUT 6


class timeoutChecker : public Thread
{
  public:
    timeoutChecker(baseReceiver *b):Thread(){base = b;};
    int run();
    
  private:
    baseReceiver *base;
 
};


#endif