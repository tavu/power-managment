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
    
    ifstream txLog;
    
    long int start_time = atol(argv[1] );
    long int end_time = atol(argv[2] );
    const char* file=argv[3];
    
    txLog.open(file);
    
    int start_tx;
    int end_tx;    
    long int pre_time=start_time;
    
    long int sum=0;
    while(txLog.good() )
    {
        long int time;
        int tx_old;
        int tx_new;
        
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
            sum+=(end_time-pre_time)*tx_old;
            break ;
        }
        else
        {
            sum+=(time-pre_time)*tx_old;
            pre_time=time;
        }
    }
    txLog.close();
    
    double avg=(double)sum/(start_time-end_time);
    
    cout<<avg;
    
}