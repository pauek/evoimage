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

RGB X::eval(Env& e) { 
  return RGB(e.getX());
}

RGB Y::eval(Env& e) { 
  return RGB(e.getY());
}

RGB v_fix::eval(Env& e) {
	return RGB( p1, p1, p1);
}
