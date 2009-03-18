
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Node.h>

using namespace std;

int to255(double x) {
  int v = int(x*255);
  if (v > 255) v = 255;
  if (v < 0)   v = 0;
  return v;
}

int main(int argc, char **argv) {
  int m = 400, n = 400;
  string arg1 , arg2;
  
  if (argc > 0) {
  	arg1 = string(argv[1]);
  	arg2 = string(argv[2]);
  }
    

    stringstream sin(arg1);
     
Node* root =  read ( sin);

     
     
  RGB imatge[m][n], maxvalue = 0;
  int i,j;
    
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      Env e(double(i)/double(m),double(j)/double(n));
      imatge[i][j] = root->eval(e);      
    }    
  }

  {
    ofstream out(argv[2]);
    
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

  cout << "Print " << arg2 << ": ";
  root->print(cout); 
  cout << endl;
  
}
// Local variables:
// compile-command: "gcc -Wall -g3 -o ev main.cpp Node.cpp -lstdc++"
// End:



                

                
                
                
              
	
