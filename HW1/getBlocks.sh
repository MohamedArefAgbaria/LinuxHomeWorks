#!/bin/bash
rm -f blocksdb.txt
URL="https://api.blockcypher.com/v1/btc/main"
URLP=$((((curl -s $URL | grep "previous_url") | sed 's/"previous_url": //') | sed 's/,//') | sed 's/"//g')
for i in {1..10}
do
oneBlock=$((curl -s $URLP | egrep "{|hash|height|total|time|relayed_by|prev_block|}") | sed -e 's/,/,\n/g;s/{/{\n/')
echo $oneBlock >> blocksdb.txt
URLP=$((((curl -s $URLP | grep "prev_block_url") | sed 's/"prev_block_url": //') | sed 's/,//') | sed 's/"//g')
done
sed -i -e 's/,/,\n/g;s/{/{\n/' blocksdb.txt 
sed -i -e '/prev_block_url/d' blocksdb.txt
sed -i 's/"//g;s/,//' blocksdb.txt
sed -i 's/ }/}/' blocksdb.txt
