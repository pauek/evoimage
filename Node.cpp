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

RGB Log10::eval(Env& e) {
  RGB p = op1() -> eval(e);
  return p.map( log10);
}

RGB X::eval(Env& e) { 
  return RGB(e.getX());
}

RGB Y::eval(Env& e) { 
  return RGB(e.getY());
}

RGB v_fix::eval(Env& e) {
	return RGB( p1);
}
