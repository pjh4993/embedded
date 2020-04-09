#!/bin/bash
cd $1
make clean
cd ..
tar -cvzf $1.tar.gz $1
