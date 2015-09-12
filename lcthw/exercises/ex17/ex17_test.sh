#!/usr/bin/sh
set -e
db="ex17_test.db"
rm -f $db
./ex17 $db c
./ex17 $db s 0  Anna aasw 55592934321
./ex17 $db s 1	Dhruv dcwn 9931943991
./ex17 $db s 2  James jrmw 29229222222
./ex17 $db s 49	Mike mam 151234
./ex17 $db s 99 Kim asl2 1234511231
./ex17 $db l
./ex17 $db g 49
./ex17 $db f jrmw
./ex17 $db f 29229222222
./ex17 $db d 2
./ex17 $db d 49
./ex17 $db d 99
./ex17 $db d 1
./ex17 $db d 0
 
