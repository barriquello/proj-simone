#!/bin/bash
## create feeds

#SERVER=http://emon-gpsnetcms.rhcloud.com
SERVER=http://simon-gpsnetcms.rhcloud.com
APIKEY=a4b245ca16c183c2ad2286efb342d09a
REQUEST=$SERVER/feed/list.json\&apikey=$APIKEY
echo $REQUEST
curl $REQUEST

declare -a feednames=("fTE" "fTO" "fVcn" "fVbn" "fVan" "fVca" "fVbc" "fVab" "fIPc" "fIPb" "fIPa" "fIMc" "fIMb" "fIMa" \
"fIc" "fIa" "fIb" "fPQ" "fPS" "fPP" "fQM" "fSM" "fPM" "fFreq" "fPF" "fQ" "fS" "fP" "fEQ" "fES" "fEP" "fVL" "fNO") 

for f in "${feednames[@]}"
do
   echo "$f"
   REQUEST=\"$SERVER/feed/create.json?name=$f\&datatype=1\&engine=5\&options=\\{\\\"interval\\\":30\\}\&apikey=$APIKEY\"
   echo $REQUEST
   curlCmd="curl $REQUEST"
   eval $curlCmd
done
REQUEST=$SERVER/feed/list.json\&apikey=$APIKEY
echo $REQUEST
curl $REQUEST