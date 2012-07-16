#include<iostream>
#include <stdlib.h>
#include<iostream>
#include <fstream>
using namespace std;

int main( int argc, const char* argv[] )
{
    if(argc!=4)
    {
        cerr<<"invalid number of arguments"<<endl;
        exit(1);
    }
    
    for(int i=0;i<argc;i++)
    {
      printf("%s\n",argv[i]);
    }
    
    ifstream txLog;
    
    long int start_time = atol(argv[1] );
    long int end_time = atol(argv[2] );
    const char* file=argv[3];
    
    txLog.open(file);
    
    int start_tx=20;
    int end_tx;    
    long int pre_time=start_time;
    
    double sum=0;
            long int time;
        int tx_old;
        int tx_new;

     printf("start time %ld\nend time %ld\n",start_time,end_time);
    while(txLog.good() )
    {


        txLog>>time;
        txLog>>tx_old;
        txLog>>tx_new;

        if(time<=start_time )
        {
            start_tx=tx_old;
            continue ;
        }
        else if(time>=end_time)
        {
            tx_new=tx_old;
            break ;
        }
        else
        {
            sum+=(time-pre_time)*tx_old;
            pre_time=time;
        }
    }
    
    txLog.close();
    sum+=(end_time-pre_time)*tx_new;
    
    double avg=sum/(end_time-start_time);
    printf("average power %f\n",avg);
}
