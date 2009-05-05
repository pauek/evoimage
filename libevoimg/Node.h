
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>

#ifndef Node_h
#define Node_h

typedef float (*PFunction)(float);
typedef float (*PFunction2)(float,float);

union long_float {
  long l;
  float f;
};

inline float _clamp(float x) {
  if (x > 1.0) x = 1.0;
  if (x < 0.0) x = 0.0;
  return x;
}

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
  
  RGB map2(PFunction2 f, RGB o) {
    return RGB( f(_r, o.getr()), f(_g, o.getg()), f(_b, o.getb()) );
  }

  RGB operator+(const RGB& o) const {
    return RGB(_r + o._r, _g + o._g, _b + o._b);
  }
  
  RGB operator-(const RGB& o) const {
    return RGB(_r - o._r, _g - o._g, _b - o._b);
  }
  
  RGB operator*(const RGB& o) const {
    return RGB(_r * o._r, _g * o._g, _b * o._b);
  }

  RGB operator*(double x) const {
    return RGB(_r * x, _g * x, _b * x);
  }
  
  RGB operator/(const RGB& o) const {
    return RGB(_r / o._r, _g / o._g, _b / o._b);
  }

  RGB clamp() const {
    return RGB(_clamp(_r), _clamp(_g), _clamp(_b));
  }

  RGB invert() const {
    return RGB(1.0 - _r, 1.0 - _g, 1.0 - _b);
  }
  
  RGB operator&(const RGB& o) const {
    long_float r1, r2, g1, g2, b1, b2;
    r1.f = _r; r2.f = o._r; r1.l &= r2.l;
    g1.f = _g; g2.f = o._g; g1.l &= g2.l;
    b1.f = _b; b2.f = o._b; b1.l &= b2.l;
    return RGB(r1.f, g1.f, b1.f);
  }
  
  RGB operator|(const RGB& o) const {
    long_float r1, r2, g1, g2, b1, b2;
    r1.f = _r; r2.f = o._r; r1.l |= r2.l;
    g1.f = _g; g2.f = o._g; g1.l |= g2.l;
    b1.f = _b; b2.f = o._b; b1.l |= b2.l;
    return RGB(r1.f, g1.f, b1.f);
  }
  
  RGB operator^(const RGB& o) const {
    long_float r1, r2, g1, g2, b1, b2;
    r1.f = _r; r2.f = o._r; r1.l ^= r2.l;
    g1.f = _g; g2.f = o._g; g1.l ^= g2.l;
    b1.f = _b; b2.f = o._b; b1.l ^= b2.l;
    return RGB(r1.f, g1.f, b1.f);
  }

  RGB hsv_to_rgb() const;
};

class Image {
  int x, y;
  float xtl, ytl; // top left map coordinates
  float xbr, ybr; // bottom right map coordinates
  RGB *p;
public:
  Image (int _x , int _y, 
         float _xtl = -1.0, float _ytl =  1.0,
         float _xbr =  1.0, float _ybr = -1.0) {
      x = _x;
      y = _y;
      xtl = _xtl, ytl = _ytl;
      xbr = _xbr, ybr = _ybr;
      p = new RGB[x * y];
  }

  Image(const Image& I) {
    x = I.x, y = I.y;
    xtl = I.xtl, ytl = I.ytl, xbr = I.xbr, ybr = I.ybr;
    p = new RGB[x * y];
    copyPixels(I);
  }
  ~Image() { delete[] p; }

  int  getX () const { return x; }
  int  getY () const { return y; }
  RGB  getPixel (int i, int j) const  { return p[j*x+i]; }
  void putPixel (int i, int j, RGB v) { p[j*x+i] = v; }

  void get_tl(float& x, float& y) const { x = xtl, y = ytl; }
  void get_br(float& x, float& y) const { x = xbr, y = ybr; }
  void set_tl(float x, float y) { xtl = x, ytl = y; }
  void set_br(float x, float y) { xbr = x, ybr = y; }

  void copyPixels(const Image& I);
  void filtraImatge(const RGB kernel[3][3]);
  void save_pnm(std::string filename) const;
};

class Node {
protected:
  static const float mutation_prob = 0.1;

public:
  virtual void  destroy();
  virtual void  eval(Image& e) = 0;
  virtual void  print(std::ostream& o) const { o << "?"; }
  virtual int   depth() const = 0;
  virtual Node *clone() const = 0;
  virtual Node *_mutate() { 
    // Default: no mutation
    return this; 
  }

  // Aquest mutate és "extern" i no virtual
  Node*  mutate();

  static Node* randomNode(int lcount);
  static Node* randomUnaryOp(int lcount);
  static Node* randomBinaryOp(int lcount);
  static Node* randomLeave();
};

class Leaf : public Node {
public:
  int depth() const { return 1; }
};

class X : public Leaf {
public:
  void  eval(Image& e);
  void  print(std::ostream& o) const;
  Node* _mutate();
  Node *clone() const { return new X(); }
};

class Y : public Leaf {
public:
  void  eval(Image& e);
  void  print(std::ostream& o) const;
  Node* _mutate();
  Node *clone() const { return new Y(); }
};

class v_fix : public Leaf {
  float p1, p2, p3;
public:
  v_fix(float _p1) { p1=_p1; p2=_p1; p3=_p1; }
  v_fix(float _p1, float _p2, float _p3) { p1=_p1; p2=_p2; p3=_p3; }
  
  void  eval(Image& e);
  void  print(std::ostream& o) const;
  Node *_mutate();
  Node *clone() const { return new v_fix(p1, p2, p3); }
};

class Noise : public Leaf {
  int seed;
  
public:
  Noise() { seed=-1;}
  Noise(int s) { seed=s; }
  
  int getSeed(){ return seed; }
  void eval(Image& e);
  virtual RGB gen_noise() const = 0;
};

class bwNoise : public Noise {
public:
  bwNoise() : Noise() {}
  bwNoise(int s) : Noise(s) {}
  RGB gen_noise() const;
  Node *_mutate();
  void print(std::ostream& o) const;
  Node *clone() const { return new bwNoise(); }
};

class colorNoise : public Noise {
public:
  colorNoise() : Noise() {}
  colorNoise(int s) : Noise(s) {}
  RGB gen_noise() const;
  Node *_mutate();
  void print(std::ostream& o) const;
  Node *clone() const { return new colorNoise(); }
};

class Warp : public Node {
  Node *p1, *p2, *p3;
public:
  Warp(Node *_p1, Node *_p2, Node *_p3) {
    p1 = _p1, p2 = _p2, p3 = _p3;
  }
  
  void eval(Image& I);
  void destroy();
  int  depth() const { 
    return 1 + std::max(p1->depth(), 
			std::max(p2->depth(), 
				 p3->depth())); 
  }
  void print(std::ostream& o) const;
  Node *clone() const { 
    return new Warp(p1->clone(), p2->clone(), p3->clone());
  }
  //Node *_mutate();
};

class Dissolve : public Node {
  Node *p1, *p2, *p3;
public:
  Dissolve(Node *_p1, Node *_p2, Node *_p3) {
    p1 = _p1, p2 = _p2, p3 = _p3;
  }

  void eval(Image& I);
  void destroy();
  int  depth() const {
    return 1 + std::max(p1->depth(), 
			std::max(p2->depth(), 
				 p3->depth())); 
  }
  void print(std::ostream& o) const;

  Node *clone() const { 
    return new Dissolve(p1->clone(), p2->clone(), p3->clone());
  }
};

// Operacions Unàries ////////////////////////////////////////////////

class UnaryOp : public Node {
  Node *p1;

protected:
  Node* op1() const { return p1; }
  virtual std::string head() const { return "?"; }  
  Node *_mutate();

public:
  UnaryOp(Node* _p1) { p1 = _p1; }
  void destroy();
  int  depth() const { return 1 + p1->depth(); }
  void print(std::ostream& o) const;
};

#define DEF_UNARY_OP(Name)			\
  class Name : public UnaryOp {			\
  public:					\
    Name (Node* p1) : UnaryOp(p1) {}		\
    void eval(Image& I);			\
    std::string head() const;			\
    Node *clone() const {			\
      return new Name(op1()->clone());		\
    }						\
  }

DEF_UNARY_OP(Abs);
DEF_UNARY_OP(Sin);
DEF_UNARY_OP(Cos);
DEF_UNARY_OP(gaussBlur);
DEF_UNARY_OP(gradDir);
DEF_UNARY_OP(emboss);
DEF_UNARY_OP(sharpen);
DEF_UNARY_OP(blur);
DEF_UNARY_OP(hsv_to_rgb);

// Operacions Binàries ///////////////////////////////////////////////

class BinOp : public Node {
  Node *p1, *p2;

protected:
  Node* op1() const { return p1; }
  Node* op2() const { return p2; }
  virtual std::string head() const { return "?"; }
  Node *_mutate();
  
public:
  void destroy();
  BinOp(Node* _p1, Node* _p2) {
    p1 = _p1;
    p2 = _p2;
  }

  void eval(Image& I);

  int depth() const {
    return 1 + std::max(p1->depth(), p2->depth());
  }

  virtual void do_op(Image& res, Image& op1, Image& op2) = 0;
  void print(std::ostream& o) const;
};

#define DEF_BINARY_OP(Name) \
  class Name : public BinOp {				\
  public:						\
    Name (Node* p1, Node* p2): BinOp(p1, p2) {}		\
    void do_op(Image& res, Image& op1, Image& op2);	\
    std::string head() const;				\
    Node *clone () const {				\
      return new Name(op1()->clone(), op2()->clone());	\
    }							\
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
DEF_BINARY_OP(Min);
DEF_BINARY_OP(Max);

// Reader ////////////////////////////////////////////////////////////
std::string read_token(std::istream& i);
float read_number(std::istream& i);
Node* read_vec(std::istream& i);
char  getnext(std::istream& i);
Node* read_list(std::istream& i);
Node* read(std::istream& i);

#endif
