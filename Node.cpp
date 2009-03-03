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
  return RGB(double(int(_r) & int(o._r)), double(int(_g) & int(o._g)), double(int(_b) & int(o._b)));
}

RGB RGB::operator|(const RGB& o) {
  return RGB(double(int(_r) | int(o._r)), double(int(_g) | int(o._g)), double(int(_b) | int(o._b)));
}

RGB RGB::operator^(const RGB& o){
  return RGB(double(int(_r) ^ int(o._r)), double(int(_g) ^ int(o._g)), double(int(_b) ^ int(o._b)));
	}

RGB RGB::map(PFunction f) {
  return RGB( f(_r), f(_g), f(_b) );
}

RGB RGB::map2(PFunction2 f , RGB& o) {
  
  
  return RGB( f(_r, o.getr()), f(_g, o.getg()), f(_b, o.getb()) );
}


RGB Sum::eval(Env& e) {
  return op1()->eval(e) + op2()->eval(e);
}

RGB Rest::eval(Env& e) {
  return op1()->eval(e) - op2()->eval(e);
}

RGB Mult::eval(Env& e) {
  return op1()->eval(e) * op2()->eval(e);
}

RGB Div::eval(Env& e) {
  return op1()->eval(e) / op2()->eval(e);
}

RGB Mod::eval(Env& e){
  RGB p = op1() -> eval(e);
  RGB b = op2() -> eval(e);
	return ( p.map2( fmod, b ));
	
	}

RGB Log::eval(Env& e) {
  RGB p = op1() -> eval(e);
  RGB b = op2() -> eval(e);
  return (p.map( log10) / b.map( log10));
}

RGB Round::eval(Env& e) {
  RGB p = op1() -> eval(e);
  RGB b = op2() -> eval(e);
  RGB offs = RGB( 0.5, 0.5, 0.5);
  return (((b/p)+offs).map( floor));
}

RGB And::eval ( Env& e){
	return op1()->eval(e) & op2()->eval(e);	
	
	}
	
RGB Or::eval ( Env& e){
	return op1()->eval(e) | op2()->eval(e);	
	
	}
	
RGB Xor::eval ( Env& e){
	return op1()->eval(e) ^ op2()->eval(e);	
	
	}

RGB Sin::eval ( Env& e){
	RGB p = op1() -> eval(e);
	return p.map(sin);
	}
	
RGB Cos::eval ( Env& e){
	RGB p = op1() -> eval(e);
	return p.map(cos);
	}

RGB Atan::eval(Env& e){
  RGB p = op1() -> eval(e);
  RGB b = op2() -> eval(e);
	return ( p.map2( atan2, b ));
	
	}

RGB X::eval(Env& e) { 
  return RGB(e.getX());
}

RGB Y::eval(Env& e) { 
  return RGB(e.getY());
}

RGB v_fix::eval(Env& e) {
	return RGB( p1, p1, p1);
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
  o << p1;
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
