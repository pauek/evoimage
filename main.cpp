
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Node.h"

using namespace std;

int to255(double x) {
  int v = int(x*255);
  if (v > 255) v = 255;
  if (v < 0)   v = 0;
  return v;
}

int main() {
  int m = 128, n = 128;
    
  X* Xv = new X();
  Y* Yv = new Y();
  v_fix* trenta = new v_fix(30.0);
  v_fix* migMD = new v_fix ( 128.0);
  Mult* Mult_1 = new Mult (Xv , migMD);
  Rest* Rest_1 = new Rest ( Yv , trenta);
  v_fix* quaranta = new v_fix (40.0);
  Sum* Sum_1 = new Sum(Rest_1, quaranta);
  Div* Div_1 = new Div ( Mult_1 , Sum_1);
  
  Node* root = new Log10(Div_1);
     
  RGB imatge[m][n], maxvalue = 0;
  int i,j;
    
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      Env e(i/double(m),j/double(n));
      imatge[i][j] = root->eval(e);
    }
  }

  {
    ofstream out("sortida.pgm");
    
    out << "P3" << endl
	<< n << " " << m << endl
	<< "255" << endl;
    
    for(i = 0; i < m; i++) {
      for(j = 0; j < n; j++) {
	out << to255(imatge[i][j].getr()) << ' '
	    << to255(imatge[i][j].getg()) << ' '
	    << to255(imatge[i][j].getb()) << ' ';
      }
      out << endl;
    }
  }
    
  delete(Xv);
  delete(Yv);
  delete(trenta);
  delete(quaranta);
  delete(migMD);
  delete(Mult_1);
  delete(Rest_1);
  delete(Div_1);
  delete(Sum_1);
  delete(root);
}

// Local variables:
// compile-command: "gcc -Wall -g3 -o ev main.cpp Node.cpp -lstdc++"
// End:



                

                
                
                
              
