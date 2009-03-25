
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Node.h>

using namespace std;

int to255(float x) {
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

     
     
  //float maxvalue = 0;
  
  int i,j;
    

      Env e(m,n);
      root->eval(e);      


  {
    ofstream out(argv[2]);
    
    out << "P3" << endl
	<< n << " " << m << endl
	<< "255" << endl;
 
 
   /*  for(i = 0; i < m; i++) {
      for(j = 0; j < n; j++) {
      	
      	if (e.getPixel ( i ,j ).getr() > maxvalue){ maxvalue=e.getPixel ( i ,j ).getr(); }
      	if (e.getPixel ( i ,j ).getg() > maxvalue){ maxvalue=e.getPixel ( i ,j ).getg(); }
      	if (e.getPixel ( i ,j ).getb() > maxvalue){ maxvalue=e.getPixel ( i ,j ).getb(); }
		}
	}*/
 
    
    for(i = 0; i < m; i++) {
      for(j = 0; j < n; j++) {
	out << to255(e.getPixel( i, j ).getr( )) << ' '
	    << to255(e.getPixel( i, j ).getg( )) << ' '
	    << to255(e.getPixel( i, j ).getb( )) << ' ';
	//això comentat no és legal 
	    
	   /*out << int((e.getPixel( i, j ).getr( ))) << ' '
	    << int((e.getPixel( i, j ).getg( ))) << ' '
	    << int((e.getPixel( i, j ).getb( ))) << ' ';*/
	    
	    
	    
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



                

                
                
                
              
	
