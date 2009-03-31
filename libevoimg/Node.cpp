#include <string>
#include "Node.h"
using namespace std;


void Env::filtraImatge () {
	
	float* kernel, int kernelSizeX, int kernelSizeY)
    int i, j, m, n, mm, nn;
    int kCenterX, kCenterY;
    int kernelSizeX = 3;
    int kernelSizeY = 3;                         
    RGB sum;                                      
    int rowIndex, colIndex;
    int dataSizeX = x; 
    int dataSizeY = y;
	float kernel[2][2];
	kernel[0][0] = -1.0;
	kernel[0][1] = -2.0;
	kernel[0][2] = -1.0;
	kernel[1][0] = 0.0;
	kernel[1][1] = 0.0;
	kernel[1][2] = 0.0;
	kernel[2][0] = -1.0;
	kernel[2][1] = -2.0;
	kernel[2][2] = -1.0;
    

    
    kCenterX = kernelSizeX / 2;
    kCenterY = kernelSizeY / 2;

    for(i=0; i < dataSizeY; ++i)                
    {
        for(j=0; j < dataSizeX; ++j)            
        {
            sum = 0.0;                            
            for(m=0; m < kernelSizeY; ++m)      
            {
                mm = kernelSizeY - 1 - m;       // index fila del kernel girat

                for(n=0; n < kernelSizeX; ++n)  
                {
                    nn = kernelSizeX - 1 - n;   // index columna del kernel girat

                    // index de  l'input per mirar dspres si estem treballant amb valors de fora d la img
                    rowIndex = i + m - kCenterY;
                    colIndex = j + n - kCenterX;

                    // ignorar els pixels que estan fora de la img. (hi ha altres mètodes tb)
                    if(rowIndex >= 0 && rowIndex < dataSizeY && colIndex >= 0 && colIndex < dataSizeX)
                    	
                        sum = sum + ( getPixel (rowIndex , colIndex ) * RGB(kernel[mm][nn]));
                }
            }
            putPixel( i , j , (sum.map( fabs ) + 0.5f));
        }
    }	
	
	
	}

RGB RGB::operator+(const RGB& o) {
  return RGB(_r + o._r, _g + o._g, _b + o._b);
}

RGB RGB::operator-(const RGB& o) {
  return RGB(_r - o._r, _g - o._g, _b - o._b);
}

RGB RGB::operator*(const RGB& o) {
  return RGB(_r * o._r, _g * o._g, _b * o._b);
}

RGB RGB::operator/(const RGB& o) {
  return RGB(_r / o._r, _g / o._g, _b / o._b);
}

RGB RGB::operator&(const RGB& o) {
  return RGB(float(int(_r) & int(o._r)), float(int(_g) & int(o._g)), float(int(_b) & int(o._b)));
}

RGB RGB::operator|(const RGB& o) {
  return RGB(float(int(_r) | int(o._r)), float(int(_g) | int(o._g)), float(int(_b) | int(o._b)));
}

RGB RGB::operator^(const RGB& o){
  return RGB(float(int(_r) ^ int(o._r)), float(int(_g) ^ int(o._g)), float(int(_b) ^ int(o._b)));
	}

RGB RGB::map(PFunction f) {
  return RGB( f(_r), f(_g), f(_b) );
}

RGB RGB::map2(PFunction2 f , RGB o) {
  
  
  return RGB( f(_r, o.getr()), f(_g, o.getg()), f(_b, o.getb()) );
}



void Sum::eval(Env& e) {
  
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(e1.getPixel(i,j) + e2.getPixel(i,j)));
  		  		
  		}
  	}
  
  
}

void Rest::eval(Env& e) {
    int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(e1.getPixel(i,j) - e2.getPixel(i,j)));
  		  		
  		}
  	}
}

void Mult::eval(Env& e) {
    int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(e1.getPixel(i,j) * e2.getPixel(i,j)));
  		  		
  		}
  	}
}

void Div::eval(Env& e) {
    int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(e1.getPixel(i,j) / e2.getPixel(i,j)));
  		  		
  		}
  	}
}

void Mod::eval(Env& e){

	
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,((e1.getPixel(i,j)).map2( fmod ,  (e2.getPixel(i,j)))));
  		  		
  		}
  	}
	
	
	}

void Log::eval(Env& e) {

  
  
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(((e1.getPixel(i,j)).map( log10 )) /  ((e2.getPixel(i,j)).map( log10))));
  		  		
  		}
  	}
  
  
}

void Round::eval(Env& e) {

  RGB offs = RGB( 0.5, 0.5, 0.5);
  
  
  
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,((((e1.getPixel(i,j))/(e1.getPixel(i,j)))+offs).map( floor)));
  		  		
  		}
  	}
  
  
}

void And::eval ( Env& e){
	  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(e1.getPixel(i,j) & e2.getPixel(i,j)));
  		  		
  		}
  	}	
	
	}
	
void Or::eval ( Env& e){
	  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(e1.getPixel(i,j) | e2.getPixel(i,j)));
  		  		
  		}
  	}	
	
	}
	
void Xor::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(e1.getPixel(i,j) ^ e2.getPixel(i,j)));
  		  		
  		}
  	}	
	
	}

void Sin::eval ( Env& e){

	
	
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
  op1()->eval(e1); 
  
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(e1.getPixel(i,j)).map( sin ));
  		  		
  		}
  	}	
	
	
	}
	
void Cos::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
  op1()->eval(e1); 
  
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(e1.getPixel(i,j)).map( cos ));
  		  		
  		}
  	}
	}

void Atan::eval(Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,((e1.getPixel(i,j)).map2( atan2 ,  (e2.getPixel(i,j)))));
  		  		
  		}
  	}
	
	}

void X::eval(Env& e) { 
 
  int x=e.getX();
  int y=e.getY();
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j = 0 ; j < y ; j++){
  		
  		e.putPixel(i,j,RGB(float(i)/float(x)));
  		  		
  		}
  	}
 
}

void Y::eval(Env& e) { 
  
  int x=e.getX();
  int y=e.getY();
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j = 0 ; j < y ; j++){
  		
  		e.putPixel(i,j,RGB(float(j)/float(y)));
  		  		
  		}
  	}
  
}

void v_fix::eval(Env& e) {
	  
  int x=e.getX();
  int y=e.getY();
	  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j = 0 ; j < y ; j++){
  		
  		e.putPixel(i,j,RGB( p1 , p2 , p3 ));
  		  		
  		}
  	}
}



void firGeneric::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
  op1()->eval(e1); 
  
  e1.filtraImatge();
  
  int i,j;
  for (i = 0 ; i < x ; i++){
  	for (j=0 ; j < y ; j++){
  		
  		e.putPixel(i,j,(e1.getPixel(i,j)));
  		  		
  		}
  	}
	}



void BinOp::print(ostream& o) const {
  o << "(" << head() << " ";
  op1()->print(o);
  o << " ";
  op2()->print(o);
  o << ")";
}

void UnaryOp::print(ostream& o) const {
  o << "(" << head() << " ";
  op1()->print(o);
  o << ")";
  }

void v_fix::print(ostream& o) const {
	if( p1 == p2 || p2 == p3) { o << p1; } 
	else{ o << "#(" << p1 << " " << p2 << " " << p3 << ")"; }
}

string Sum::head()  const { return "+"; }
string Rest::head() const { return "-"; }
string Mult::head()  const { return "*"; }
string Div::head()  const { return "/"; }
string Mod::head()  const { return "%"; }
string Log::head()  const { return "Log"; }
string Round::head()  const { return "Round"; }
string And::head()  const { return "&"; }
string Or::head()  const { return "|"; }
string Xor::head()  const { return "^"; }
string Sin::head()  const { return "Sin"; }
string Cos::head()  const { return "Cos"; }
string Atan::head()  const { return "Atan"; }
string firGeneric::head()  const { return "firGeneric"; }

void Y::print(ostream& o) const { o << "y"; }
void X::print(ostream& o) const { o << "x"; }
