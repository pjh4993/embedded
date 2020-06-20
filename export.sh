#!/bin/bash
cd $1
#make clean
cd ..
tar -cvf $1.tar $1
scp $1.tar root@192.168.2.10:/root
