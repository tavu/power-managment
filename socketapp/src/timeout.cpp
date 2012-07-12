#include "timeout.h"
#include "nodeMap.h"
#include "base_receiver.h"



int timeoutChecker :: run()
{ 
  while(1)
  {
    sleep(TIMEOUT);
    base->checkForTimeouts();
  } 
  
  return 0;
}