#!/bin/bash
## create feeds

#SERVER=http://emon-gpsnetcms.rhcloud.com
SERVER=http://simon-gpsnetcms.rhcloud.com
#SERVER=http://localhost
APIKEY=a4b245ca16c183c2ad2286efb342d09a
#APIKEY=b52faf2939e7957e722fb38a13dd74e3
REQUEST=$SERVER/feed/list.json\&apikey=$APIKEY
#echo $REQUEST
#curl $REQUEST

#declare -a feednames=("fTE" "fTO" "fVcn" "fVbn" "fVan" "fVca" "fVbc" "fVab" "fIPc" "fIPb" "fIPa" "fIMc" "fIMb" "fIMa" \
#"fIc" "fIa" "fIb" "fPQ" "fPS" "fPP" "fQM" "fSM" "fPM" "fFreq" "fPF" "fQ" "fS" "fP" "fEQ" "fES" "fEP" "fVL" "fNO") 



vartime=1456600001

v=0
while [ $v -lt 10 ]
do
let v=v+1 
m=0
while [ $m -lt 60 ]
do       
   let vartime=vartime+30 
   REQUEST=$SERVER/monitor/set.json?monitorid=0\&time=$vartime\&data=0,0,0,0,0,38,0,0,0,0,$m,0,0,0,242,231,0,0,0,0,1,0\&apikey=$APIKEY
   curl $REQUEST
   REQUEST=$SERVER/monitor/set.json?monitorid=0\&time=$vartime\&data=0,0,0,0,0,38,0,0,0,0,$m,0,0,0,242,231,0,0,0,0,1,0\&apikey=$APIKEY
   curl $REQUEST   
   let m=m+1
   echo $m
done
done

