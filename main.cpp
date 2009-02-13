
#include <cstdlib>
#include <iostream>
#include <fstream>


#include "Node.h"

using namespace std;

int main() {
  int m = 1024, n = 768;
    
  X* Xv = new X();
  Y* Yv = new Y();
  Sum* Sumv = new Sum(Xv, Yv);
  Node* root = new Mult(Sumv, Xv);
    
  double imatge[m][n], maxvalue = 0;
  int i,j;
    
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      Env e(i,j);
      imatge[i][j] = root->eval(e);

      //cout << imatge[i][j] << endl; 
      if (imatge[i][j] > maxvalue) {
	maxvalue = imatge[i][j];
      }
    }
  }
  
  ofstream out; 
  out.open("sortida.pgm");

  out << "P2" << endl
      << n << " " << m << endl
      << "65535" << endl;

  for(i = 0; i < m; i++) {
    for(j = 0; j < n; j++) {
      out << int((imatge[i][j]/maxvalue)*65535) << " ";
    }
    out << endl;
  }
    
  out.close();    
    
  delete(Xv);
  delete(Yv);
  delete(Sumv);
  delete(root);
}

// Local variables:
// compile-command: "gcc -o ev main.cpp Node.cpp -lstdc++"
// End:



                

                
                
                
              
