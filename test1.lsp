#!/bin/sh

./evoimg "(- 22 88)" "test1.pgm" > out1
./evoimg "(+ 0.05 0.5 )" "test2.pgm" > out2
./evoimg "(* 0.5 0.5)" "test3.pgm" > out3
./evoimg "(/ 1 2)" "test4.pgm" > out4
./evoimg "(% 1 2)" "test5.pgm" > out5
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

./evoimg "(         -   88  22   )" "test14.pgm" > out14  #espais de més
./evoimg "(- 88 22))" "test15.pgm" > out15 #parentesi de mes al final
./evoimg "((- 88 22)" "test16.pgm" > out16 #parentesi de més al principi
./evoimg "(- 88 22 33)" "test17.pgm" > out17 #més params dels que toquen
./evoimg "(- 88)" "test18.pgm" > out18  #menys params dels que toquen
./evoimg "(- zh th)" "test19.pgm" > out19  #params de tipus inesperat?
./evoimg "(- #(88 22 55) #(33 44 22))" "test20.pgm" > out20  #vector amb parentesis
./evoimg "(Round (Log (+ 0.25  0.19) 55) 20)" "test21.pgm" > out21 #niuament de funcions2
./evoimg "(Round (Log (+ Y  0.19) X) Y)" "test22.pgm" > out22 #niuament de funcions1
./evoimg "(% (Sin (+ #(33 22 11)  0.19) 55))" "test23.pgm" > out23 #niuament de funcions3
./evoimg "(+ #(0.22 0.55 0.81) #(0.0 0.0 0.0))" "test24.pgm" > out24



