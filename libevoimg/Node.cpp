#include <string>
#include "Node.h"
using namespace std;

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

void Y::print(ostream& o) const { o << "y"; }
void X::print(ostream& o) const { o << "x"; }
