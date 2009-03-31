
#include <iostream>
#include <cmath>

#ifndef Node_h
#define Node_h

typedef float (*PFunction)(float);
typedef float (*PFunction2)(float,float);



class RGB {
  float _r, _g, _b;
 public:
  
 RGB(float x=0.0) : _r(x), _g(x), _b(x) {}
 
 RGB(float r, float g, float b)
   : _r(r), _g(g), _b(b) {}

  float getr() const { return _r; }
  float getg() const { return _g; }
  float getb() const { return _b; }

  RGB map(PFunction f);
  RGB map2(PFunction2 f, RGB o);

  RGB operator+(const RGB& o);
  RGB operator-(const RGB& o);  
  RGB operator*(const RGB& o);
  RGB operator/(const RGB& o);
  RGB operator&(const RGB& o);
  RGB operator|(const RGB& o);
  RGB operator^(const RGB& o);
  
  
};

class Env {
  int x,y;
  RGB *p;
 public:
  int getX () { return x; }
  int getY () { return y; }
  RGB getPixel (int i, int j) { return p[j*x+i]; }
  void putPixel ( int i , int j , RGB v) { p[j*x+i] = v; }
  Env ( int _x , int _y) {
      x = _x;
      y = _y;
      p = new RGB[x * y];
  }
  void filtraImatge ();
  ~Env() { delete[] p; }
};

class Node {
public:
  virtual void eval(Env& e) = 0;
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
  Node* op1() const { return p1; }
  virtual std::string head() const { return "?"; }  
public:
  UnaryOp(Node* _p1) {
    p1 = _p1;
  }

  void print(std::ostream& o) const;

};

class Sum : public BinOp {
public:
  Sum(Node* p1, Node* p2): BinOp(p1, p2) {}
  void eval( Env& e);
  std::string head() const;
};

class Rest : public BinOp {
public:
  Rest(Node* p1, Node* p2): BinOp(p1, p2) {}
  void eval( Env& e);
  std::string head() const;
};

class Mult : public BinOp {
 public:
 Mult(Node* p1, Node* p2): BinOp(p1, p2) {}

  void eval(Env& e);
  std::string head() const;
};

class Div : public BinOp {
 public:
 Div(Node* p1, Node* p2): BinOp(p1, p2) {}

  void eval(Env& e);
  std::string head() const;
};

class Mod : public BinOp {
	public:
	Mod( Node* p1, Node* p2) : BinOp( p1, p2) {}
	
	void eval ( Env& e);
	std::string head() const;
};

class Log : public BinOp {
 public:
 Log(Node* p1 , Node* p2): BinOp( p1, p2) {}

  void eval(Env& e);
  std::string head() const;
};

class Round : public BinOp {
 public:
 Round(Node* p1 , Node* p2): BinOp( p1, p2) {}

  void eval(Env& e);	
  std::string head() const;
	
	};

class And : public BinOp {
	public:
	And ( Node* p1, Node* p2) : BinOp ( p1, p2) {}
	void eval ( Env& e);
	std::string head() const;
	
	};
	
class Or : public BinOp {
	public:
	Or ( Node* p1, Node* p2) : BinOp ( p1, p2) {}
	void eval ( Env& e);
	std::string head() const;
	
	};
	
class Xor : public BinOp {
	public:
	Xor ( Node* p1, Node* p2) : BinOp ( p1, p2) {}
	void eval ( Env& e);
	std::string head() const;
	
	};

class Sin : public UnaryOp {
	public:
	Sin ( Node* p1) : UnaryOp( p1) {}
	void eval ( Env& e);
	std::string head() const;
	};
	
class Cos : public UnaryOp {
	public:
	Cos ( Node* p1) : UnaryOp( p1) {}
	void eval ( Env& e);
	std::string head() const;
	};

class Atan : public BinOp {
	public:
	Atan ( Node* p1, Node* p2) : BinOp( p1, p2) {}
	void eval ( Env& e);
	std::string head() const;
	
	};

class X : public Node {
public:
  void eval( Env& e);
  void print(std::ostream& o) const;
};

class Y : public Node {
public:
  void eval( Env& e);
  void print(std::ostream& o) const;
};

class v_fix : public Node {
	float p1, p2, p3;
	
public:
	void eval( Env& e);

	v_fix( float _p1){	p1=_p1; p2=_p1; p3=_p1;	}
	v_fix( float _p1, float _p2, float _p3) { p1=_p1; p2=_p2; p3=_p3; }


	void print(std::ostream& o) const;

};
	


class firGeneric : public UnaryOp{
	public:
	firGeneric ( Node* p1) : UnaryOp( p1) {}
	void eval ( Env& e);
	std::string head() const;
	
	
	
    };


std::string read_token( std::istream& i);
float read_number (std::istream& i);
Node* read_vec(std::istream& i);
char getnext (std::istream& i);
Node* read_list ( std::istream& i );
Node* read (std::istream& i);


#endif
