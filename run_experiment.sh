#!/bin/bash

SPEED=1
DELAY=1
LOSS=0
CORRUPT=100
FILE=$1

make clean
make

killall link 2> /dev/null
killall recv 2> /dev/null
killall send 2> /dev/null

echo "Starting link"
./link_emulator/link speed=$SPEED delay=$DELAY loss=$LOSS corrupt=$CORRUPT &> /dev/null &
sleep 1
echo "Starting recv"
./recv &
sleep 1
echo "Starting send"
./send &

#sleep 2
#echo "Finished transfer, checking files"
#diff tema.txt recv_tema.txt