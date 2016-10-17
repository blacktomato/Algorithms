#!/bin/bash

echo -ne '\n' | ./sort case1.dat -insert c1_i.dat
echo -ne '\n' | ./sort case2.dat -insert c2_i.dat
echo -ne '\n' | ./sort case3.dat -insert c3_i.dat
echo -ne '-n' | ./sort case4.dat -insert c4_i.dat
echo -ne '\n' | ./sort case1.dat -merge c1_m.dat
echo -ne '\n' | ./sort case2.dat -merge c2_m.dat
echo -ne '\n' | ./sort case3.dat -merge c3_m.dat
echo -ne '\n' | ./sort case4.dat -merge c4_m.dat
echo -ne '\n' | ./sort case1.dat -heap c1_h.dat
echo -ne '\n' | ./sort case2.dat -heap c2_h.dat
echo -ne '\n' | ./sort case3.dat -heap c3_h.dat
echo -ne '\n' | ./sort case4.dat -heap c4_h.dat
echo -ne '\n' | ./sort case1.dat -quick c1_q.dat
echo -ne '\n' | ./sort case2.dat -quick c2_q.dat
echo -ne '\n' | ./sort case3.dat -quick c3_q.dat
echo -ne '\n' | ./sort case4.dat -quick c4_q.dat
