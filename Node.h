
#include <iostream>
#include <math.h>

#ifndef Node_h
#define Node_h

typedef double (*PFunction)(double);
typedef double (*PFunction2)(double,double);

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
  RGB map2(PFunction2 f, RGB& o);

  RGB operator+(const RGB& o);
  RGB operator-(const RGB& o);  
  RGB operator*(const RGB& o);
  RGB operator/(const RGB& o);
  RGB operator&(const RGB& o);
  RGB operator|(const RGB& o);
  RGB operator^(const RGB& o);
  
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
  virtual void print(std::ostream& o) const { o << "?"; }
};

class BinOp : public Node {
  Node *p1, *p2;

protected:
  Node* op1() const { return p1; }
  Node* op2() const { return p2; }
  virtual std::string head() const { return "?"; }
  
public:
  BinOp(Node* _p1, Node* _p2) {
    p1 = _p1;
    p2 = _p2;
  }

  void print(std::ostream& o) const;
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
  std::string head() const;
};

class Rest : public BinOp {
public:
  Rest(Node* p1, Node* p2): BinOp(p1, p2) {}
  RGB eval( Env& e);
  std::string head() const;
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

class Mod : public BinOp {
	public:
	Mod( Node* p1, Node* p2) : BinOp( p1, p2) {}
	
	RGB eval ( Env& e);
};

class Log : public BinOp {
 public:
 Log(Node* p1 , Node* p2): BinOp( p1, p2) {}

  RGB eval(Env& e);
};

class Round : public BinOp {
 public:
 Round(Node* p1 , Node* p2): BinOp( p1, p2) {}

  RGB eval(Env& e);	
	
	};

class And : public BinOp {
	public:
	And ( Node* p1, Node* p2) : BinOp ( p1, p2) {}
	RGB eval ( Env& e);
	
	};
	
class Or : public BinOp {
	public:
	Or ( Node* p1, Node* p2) : BinOp ( p1, p2) {}
	RGB eval ( Env& e);
	
	};
	
class Xor : public BinOp {
	public:
	Xor ( Node* p1, Node* p2) : BinOp ( p1, p2) {}
	RGB eval ( Env& e);
	
	};

class Sin : public UnaryOp {
	public:
	Sin ( Node* p1) : UnaryOp( p1) {}
	RGB eval ( Env& e);
	
	};
	
class Cos : public UnaryOp {
	public:
	Cos ( Node* p1) : UnaryOp( p1) {}
	RGB eval ( Env& e);
	
	};

class Atan : public BinOp {
	public:
	Atan ( Node* p1, Node* p2) : BinOp( p1, p2) {}
	RGB eval ( Env& e);
	
	};

class X : public Node {
public:
  RGB eval( Env& e);
};

class Y : public Node {
public:
  RGB eval( Env& e);
  void print(std::ostream& o) const;
};

class v_fix : public Node {
	double p1, p2, p3;
	
public:
	RGB eval( Env& e);

	v_fix( double _p1){	p1=_p1; p2=_p1; p3=_p1;	}
	v_fix( double _p1, double _p2, double _p3) { p1=_p1; p2=_p2; p3=_p3; }


	void print(std::ostream& o) const;

};
	

#endif
