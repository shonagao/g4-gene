#!/bin/sh

i=`expr $1 + 10000`
./build/main macro/gun.mac $i param/input.in

