#!/bin/bash
## create feeds

#SERVER=http://emon-gpsnetcms.rhcloud.com
SERVER=http://simon-gpsnetcms.rhcloud.com
APIKEY=a4b245ca16c183c2ad2286efb342d09a
REQUEST=$SERVER/feed/list.json\&apikey=$APIKEY
echo $REQUEST
curl $REQUEST

f=1

while [ $f -le 33 ]
do
   echo "$f"
   REQUEST=$SERVER/feed/delete.json?id=$f\&apikey=$APIKEY
   echo $REQUEST
   curl $REQUEST
   f=`expr $f + 1`
done

REQUEST=$SERVER/feed/list.json\&apikey=$APIKEY
echo $REQUEST
curl $REQUEST