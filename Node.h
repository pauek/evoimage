#include <math.h>

#ifndef Node_h
#define Node_h

typedef double (*PFunction)(double);

class RGB {
  double _r, _g, _b;
 public:
  
 RGB(double x=0.0) : _r(x), _g(x), _b(x) {}
 
 RGB(double r, double g, double b)
   : _r(r), _g(g), _b(b) {}

  double getr() const { return _r; }
  double getg() const { return _g; }
  double getb() const { return _b; }

  RGB map(PFunction f);

  RGB operator+(const RGB& o);
  RGB operator-(const RGB& o);  
  RGB operator*(const RGB& o);
  RGB operator/(const RGB& o);
};

class Env {
  double x,y;
 public:
  double getX () { return x; }
  double getY () { return y; }
  Env ( double _x , double _y) {
      x = _x;
      y = _y;
  }
};

class Node {
public:
  virtual RGB eval(Env& e) = 0;
};

class BinOp : public Node {
  Node *p1, *p2;

protected:
  Node* op1() { return p1; }
  Node* op2() { return p2; }
  
public:
  BinOp(Node* _p1, Node* _p2) {
    p1 = _p1;
    p2 = _p2;
  }
};


class UnaryOp : public Node {
  Node *p1;

protected:
  Node* op1() { return p1; }
    
public:
  UnaryOp(Node* _p1) {
    p1 = _p1;
  }
};

class Sum : public BinOp {
public:
  Sum(Node* p1, Node* p2): BinOp(p1, p2) {}
  RGB eval( Env& e);
};

class Rest : public BinOp {
public:
  Rest(Node* p1, Node* p2): BinOp(p1, p2) {}
  RGB eval( Env& e);
};

class Mult : public BinOp {
 public:
 Mult(Node* p1, Node* p2): BinOp(p1, p2) {}

  RGB eval(Env& e);
};

class Div : public BinOp {
 public:
 Div(Node* p1, Node* p2): BinOp(p1, p2) {}

  RGB eval(Env& e);
};

class Log : public BinOp {
 public:
 Log(Node* p1 , Node* p2): BinOp( p1, p2) {}

  RGB eval(Env& e);
};


class X : public Node {
public:
  RGB eval( Env& e);
};

class Y : public Node {
public:
  RGB eval( Env& e);
};

class v_fix : public Node {
	double p1;
	
public:
	RGB eval( Env& e);
	v_fix( double _p1){
		p1=_p1;
		}
};
	

#endif
