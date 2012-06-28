import sys
 
#start_time=1338562222
#end_time=1338564224
#filet ="tx.log.base"

start_time=int(sys.argv[1] )
end_time=int(sys.argv[2] )
filet=sys.argv[3]

f=open(filet,'r')

start_tx=20
end_tx=20
pre_time=start_time

sum=0
for line in f:
     time=int(line.split()[0] )
     tx_old=int( line.split()[1] )
     tx_new=int( line.split()[2] )
     
     #print time,  tx_old ,tx_new
     
     if time<=start_time :        
	  start_tx=tx_old;
     elif time>=end_time :
          tx_new=tx_old;
          break ;
     else :
	  sum+=(time-pre_time)*tx_old;
	  pre_time=time;
     
f.close();
sum+=(end_time-pre_time)*tx_new;
    
avg=sum/(end_time-start_time);
print "average power " ,avg
#print avg
     
     
     
     
     
     
     
     