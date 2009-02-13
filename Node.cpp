#include <string>
#include "Node.h"
using namespace std;

double Sum::eval(Env& e) {
  return op1()->eval(e) + op2()->eval(e);
}

double Mult::eval(Env& e) {
  return op1()->eval(e) * op2()->eval(e);
}

double Log10::eval(Env& e) {
  return log10(op1()->eval(e));
}



double X::eval(Env& e) { 
  return e.getX();
}

double Y::eval(Env& e) { 
  return e.getY();
}


