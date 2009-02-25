#!/bin/sh

./evoimg "(- 22 88)" "test1.pgm" > out1
./evoimg "(+ 0.05 0.5 )" "test2.pgm" > out2
./evoimg "(* 0.5 0.5)" "test3.pgm" > out3
./evoimg "(/ 1 2)" "test4.pgm" > out4
./evoimg "(Mod 1 2)" "test5.pgm" > out5
./evoimg "(Log 3.16 10)" "test6.pgm" > out6
./evoimg "(Round 1 2)" "test7.pgm" > out7
./evoimg "(And 1 2)" "test8.pgm" > out8
./evoimg "(Or 4 3)" "test9.pgm" > out9
./evoimg "(Xor 5 6)" "test10.pgm" > out10
./evoimg "(Sin X)" "test11.pgm" > out11
./evoimg "(Cos X)" "test12.pgm" > out12
./evoimg "(Atan X Y)" "test13.pgm" > out13

#Fins aquí han estat les operacions bàsiques
#Ara comencen operacions complexes
#fallos gramaticals que han de ser superats
#i fallos greus de parametres o wrong syntax 
#que han de ser avisats i parada l'execució.

./evoimg "(- 88 22)" "test14.pgm" > out14 
./evoimg "(- 88 22)" "test15.pgm" > out15
./evoimg "(- 88 22)" "test16.pgm" > out16
./evoimg "(- 88 22)" "test17.pgm" > out17
./evoimg "(- 88 22)" "test18.pgm" > out18
./evoimg "(- 88 22)" "test19.pgm" > out19
./evoimg "(- 88 22)" "test20.pgm" > out20
./evoimg "(- 88 22)" "test21.pgm" > out21



