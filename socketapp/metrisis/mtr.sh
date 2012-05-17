#!/bin/bash
log="log"
txLog="/root/git/power-managment/socketapp/tx.log"
txAvg="/root/git/power-managment/socketapp/tx.log"
remote_ip=10.0.0.2
count=100

start_time=0;
end_time=0;

echo $1 >>$log

if [ "$2" == "udp" ]; then
    echo "UDP">>$log
    start_time=`date +'%s'`
    mtr -r -n $remote_ip -c $count >>$log
    end_time=`date +'%s'`
else
    echo "ICMP">>$log
    start_time=`date +'%s'`
    mtr -r -n $remote_ip -c $count >>$log
    end_time=`date +'%s'`
fi

echo -n 'start time='>>$log
date --date='@'$start_time >>$log 
echo ' ('$start_time')'

echo -n 'end time='>>$log
date --date='@'$end_time >>$log 
echo ' ('$end_time')' >>$log 

txAvg $start_time $end_time $txLog >>$log 

echo "">>$log
echo "">>$log

cat $log
