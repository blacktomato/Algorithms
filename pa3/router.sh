#!/bin/bash
./router ./benchmarks/gr4x4.in ./results/gr4x4.out
./verify/verify_linux ./benchmarks/gr4x4.in ./results/gr4x4.out >> $1
./router ./benchmarks/gr5x5.in ./results/gr5x5.out
./verify/verify_linux ./benchmarks/gr5x5.in ./results/gr5x5.out >> $1
./router ./benchmarks/gr10x10.in ./results/gr10x10.out
./verify/verify_linux ./benchmarks/gr10x10.in ./results/gr10x10.out >> $1
./router ./benchmarks/gr20x20.in ./results/gr20x20.out
./verify/verify_linux ./benchmarks/gr20x20.in ./results/gr20x20.out >> $1
./router ./benchmarks/gr60x60.in ./results/gr60x60.out
./verify/verify_linux ./benchmarks/gr60x60.in ./results/gr60x60.out >> $1


