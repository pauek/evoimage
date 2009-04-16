
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>

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
  
  RGB map(PFunction f) {
    return RGB( f(_r), f(_g), f(_b) );
  }
  
  RGB map2(PFunction2 f , RGB o) {
    return RGB( f(_r, o.getr()), f(_g, o.getg()), f(_b, o.getb()) );
  }

  RGB operator+(const RGB& o) {
    return RGB(_r + o._r, _g + o._g, _b + o._b);
  }
  
  RGB operator-(const RGB& o) {
    return RGB(_r - o._r, _g - o._g, _b - o._b);
  }
  
  RGB operator*(const RGB& o) {
    return RGB(_r * o._r, _g * o._g, _b * o._b);
  }
  
  RGB operator/(const RGB& o) {
    return RGB(_r / o._r, _g / o._g, _b / o._b);
  }
  
  RGB operator&(const RGB& o) {
    return RGB(float(int(_r) & int(o._r)), 
	       float(int(_g) & int(o._g)),
	       float(int(_b) & int(o._b)));
  }
  
  RGB operator|(const RGB& o) {
    return RGB(float(int(_r) | int(o._r)), 
	       float(int(_g) | int(o._g)), 
	       float(int(_b) | int(o._b)));
  }
  
  RGB operator^(const RGB& o) {
    return RGB(float(int(_r) ^ int(o._r)), 
	       float(int(_g) ^ int(o._g)), 
	       float(int(_b) ^ int(o._b)));
  }
};

class Image {
  int x,y;
  RGB *p;
public:
  Image ( int _x , int _y) {
      x = _x;
      y = _y;
      p = new RGB[x * y];
  }
  ~Image() { delete[] p; }

  int  getX () const { return x; }
  int  getY () const { return y; }
  RGB  getPixel (int i, int j) const  { return p[j*x+i]; }
  void putPixel (int i, int j, RGB v) { p[j*x+i] = v; }

  void filtraImatge(float kernel[3][3]);
  void warpGeneric();
  void save_pnm(std::string filename) const;
};

class Node {
public:
  virtual void eval(Image& e) = 0;
  virtual void print(std::ostream& o) const { o << "?"; }
  static Node* randomNode(int lcount);
  static Node* randomLeave();
};



class X : public Node {
public:
  void eval( Image& e);
  void print(std::ostream& o) const;
};

class Y : public Node {
public:
  void eval( Image& e);
  void print(std::ostream& o) const;
};

class v_fix : public Node {
  float p1, p2, p3;
public:
  v_fix(float _p1) { p1=_p1; p2=_p1; p3=_p1; }
  v_fix(float _p1, float _p2, float _p3) { p1=_p1; p2=_p2; p3=_p3; }
  
  void eval( Image& e);
  void print(std::ostream& o) const;
};

class bwNoise : public Node {
  int seed;
  
public:
  bwNoise( ) { seed=-1;}
  bwNoise(int s) { seed=s; }
  
  int getSeed(){ return seed; }
  void eval( Image& e);
  void print(std::ostream& o) const;
};

class colorNoise : public Node {
  int seed;
  
public:
  colorNoise( int s){	seed=s;	}
  colorNoise( ) { seed=-1;}
  int getSeed(){ return seed; }

  void eval( Image& e);
  void print(std::ostream& o) const;
};


// Operacions Unàries ////////////////////////////////////////////////

class UnaryOp : public Node {
  Node *p1;

protected:
  Node* op1() const { return p1; }
  virtual std::string head() const { return "?"; }  

public:
  UnaryOp(Node* _p1) { p1 = _p1; }

  void print(std::ostream& o) const;
};

#define DEF_UNARY_OP(Name)			\
  class Name : public UnaryOp {			\
  public:					\
    Name (Node* p1) : UnaryOp(p1) {}		\
    void eval(Image& e);			\
    std::string head() const;			\
  }

DEF_UNARY_OP(Abs);
DEF_UNARY_OP(Sin);
DEF_UNARY_OP(Cos);
DEF_UNARY_OP(gaussBlur);
DEF_UNARY_OP(gradDir);
DEF_UNARY_OP(emboss);
DEF_UNARY_OP(sharpen);
DEF_UNARY_OP(blur);
DEF_UNARY_OP(warp);

// Operacions Binàries ///////////////////////////////////////////////

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

  void eval(Image& I);
  virtual void do_op(Image& res, Image& op1, Image& op2) = 0;
  void print(std::ostream& o) const;
};

#define DEF_BINARY_OP(Name) \
  class Name : public BinOp {				\
  public:						\
    Name (Node* p1, Node* p2): BinOp(p1, p2) {}		\
    void do_op(Image& res, Image& op1, Image& op2);	\
    std::string head() const;				\
  }

DEF_BINARY_OP(Sum);
DEF_BINARY_OP(Rest);
DEF_BINARY_OP(Mult);
DEF_BINARY_OP(Div);
DEF_BINARY_OP(Mod);
DEF_BINARY_OP(Log);
DEF_BINARY_OP(Round);
DEF_BINARY_OP(And);
DEF_BINARY_OP(Or);
DEF_BINARY_OP(Xor);
DEF_BINARY_OP(Atan);
DEF_BINARY_OP(Expt);

// Reader ////////////////////////////////////////////////////////////

std::string read_token( std::istream& i);
float read_number (std::istream& i);
Node* read_vec(std::istream& i);
char getnext (std::istream& i);
Node* read_list ( std::istream& i );
Node* read (std::istream& i);


#endif
