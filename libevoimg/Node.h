// -*- mode: c++ -*-

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

   bool operator==(const RGB& o) const{
      if (fabs(_r - o._r) < 1e-3 && 
          fabs(_g - o._g) < 1e-3 && 
          fabs(_b - o._b) < 1e-3) { 
         return true; 
      }
      else { return false; }
   }
  
   bool operator>(const RGB& o) const{
      if (_r > o._r && _g > o._g && _b > o._b) { return true; }
      else { return false; }
   }
  
   bool operator<(const RGB& o) const{
      if (_r < o._r && _g < o._g && _b < o._b) { return true; }
      else { return false; }
   }
  
   RGB hsv_to_rgb() const;
};

inline RGB operator+(double x, const RGB& c) { return c+x; }
inline RGB operator-(double x, const RGB& c) { return c-x; }
inline RGB operator*(double x, const RGB& c) { return c*x; }
inline RGB operator/(double x, const RGB& c) { return c/x; }

class Image {
   int x, y;
   float xtl, ytl; // top left map coordinates
   float xbr, ybr; // bottom right map coordinates
   RGB *p;
public:
   Image (int _x = 0 , int _y = 0, 
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

   void resize(int w, int h) {
      delete p;
      p = new RGB[w * h];
      x = w, y = h;
   }

   int  xsize() const { return x; }
   int  ysize() const { return y; }
   RGB  get(int i, int j) const  { return p[j*x + i]; }
   void put(int i, int j, RGB v) { p[j*x + i] = v; }

   void get_tl(float& x, float& y) const { x = xtl, y = ytl; }
   void get_br(float& x, float& y) const { x = xbr, y = ybr; }
   void set_tl(float x, float y) { xtl = x, ytl = y; }
   void set_br(float x, float y) { xbr = x, ybr = y; }
  
   void copyPixels(const Image& I);
   void filtraImatge(const RGB kernel[3][3]);
   void save_pnm(std::string filename) const;
   bool allBallW();
};

class Visitor;

class Node {
protected:
   static const float replace_prob = 0.5;

public:
   virtual ~Node() {}
   virtual void  destroy();
   virtual void  eval(Image& e) = 0;
   virtual void  print(std::ostream& o) const { o << "?"; }
   virtual int   depth() const = 0;
   virtual int   size() const = 0;
   virtual Node *clone() const = 0;
   virtual Node *_mutate(int& idx) { 
      // Default: no mutation
      return this; 
   }

   virtual void  accept(Visitor& v) = 0;

   // Aquest mutate és "extern" i no virtual
   Node*  mutate();

   static Node* randomNode(int lcount);
   static Node* randomUnaryOp(int lcount);
   static Node* randomUnaryHead(Node* p1);
   static Node* randomBinaryOp(int lcount);
   static Node* randomBinaryHead(Node* p1, Node* p2);
   static Node* randomLeaf();
 
};

class Leaf : public Node {
public:
   int depth() const { return 1; }
   int size() const { return 1; }
   Node *_mutate(int& idx);
   virtual Node *_mutate_leaf() = 0;
   virtual std::string name() const = 0;
   void accept(Visitor& v);
};

class X : public Leaf {
public:
   void  eval(Image& e);
   void  print(std::ostream& o) const;
   Node *clone() const { return new X(); }
   Node *_mutate_leaf();
   std::string name() const { return "x"; }
};

class Y : public Leaf {
public:
   void  eval(Image& e);
   void  print(std::ostream& o) const;
   Node *clone() const { return new Y(); }
   Node *_mutate_leaf();
   std::string name() const { return "y"; }
};

class Const : public Leaf {
   float p1, p2, p3;
public:
   Const(float _p1) { p1=_p1; p2=_p1; p3=_p1; }
   Const(float _p1, float _p2, float _p3) { p1=_p1; p2=_p2; p3=_p3; }
  
   void  eval(Image& e);
   void  print(std::ostream& o) const;
   Node *clone() const { return new Const(p1, p2, p3); }
   Node *_mutate(int& idx);
   Node *_mutate_leaf();
   std::string name() const;
};


// Operacions Unàries ////////////////////////////////////////////////

class UnaryOp : public Node {
   Node *p1;

protected:
   void setNULL() { p1 = NULL; }
   Node *_mutate(int& idx);
   Node* bypassUnary();
   Node* nodeAsParam();

public:
   UnaryOp(Node* _p1) { p1 = _p1; }
   Node* op1() const { return p1; }
   virtual std::string head() const { return "?"; }  
   void destroy();
   int  depth() const { return 1 + p1->depth(); }
   int  size() const { return 1 + p1->size(); }
   void print(std::ostream& o) const;
   void accept(Visitor& v);
};

#define DEF_UNARY_OP(Name)                      \
   class Name : public UnaryOp {                \
   public:                                      \
   Name (Node* p1) : UnaryOp(p1) {}             \
   void eval(Image& I);                         \
   std::string head() const;                    \
   Node *clone() const {                        \
      return new Name(op1()->clone());          \
   }                                            \
   }

DEF_UNARY_OP(Abs);
DEF_UNARY_OP(Sin);
DEF_UNARY_OP(Cos);
DEF_UNARY_OP(GaussBlur);
DEF_UNARY_OP(GradDir);
DEF_UNARY_OP(Emboss);
DEF_UNARY_OP(Sharpen);
DEF_UNARY_OP(Blur);
DEF_UNARY_OP(HsvToRgb);

class Noise : public UnaryOp {
   static drand48_data _data;

protected:
   float  random();
   static void set_seed(int s);

public:
   Noise(Node* p1) : UnaryOp(p1) {}
   void eval(Image& e);
   virtual RGB gen_noise() = 0;
};

class BwNoise : public Noise {
public:
   BwNoise(Node *p1) : Noise(p1) {}
   RGB gen_noise();
   std::string head() const;
   Node *clone() const { return new BwNoise(op1()->clone()); }
   std::string name() const { return "bw-noise"; }
};

class ColorNoise : public Noise {
public:
   ColorNoise(Node *p1) : Noise(p1) {}
   RGB gen_noise();
   std::string head() const;
   Node *clone() const { return new ColorNoise(op1()->clone()); }
   std::string name() const { return "color-noise"; }
};


// Operacions Binàries ///////////////////////////////////////////////

class BinaryOp : public Node {
   Node *p1, *p2;

protected:
   Node *_mutate(int& idx);
   Node* bypassBinary();
   Node* nodeAsParam();
public:
   void destroy();
   BinaryOp(Node* _p1, Node* _p2) {
      p1 = _p1;
      p2 = _p2;
   }

   void eval(Image& I);

   Node* op1() const { return p1; }
   Node* op2() const { return p2; }
   virtual std::string head() const { return "?"; }

   int depth() const {
      return 1 + std::max(p1->depth(), p2->depth());
   }
  
   int size() const {
      return 1 + (p1->size() + p2->size());
   }

   virtual void do_op(Image& res, Image& op1, Image& op2) = 0;
   void print(std::ostream& o) const;
   void accept(Visitor& v);
};

#define DEF_BINARY_OP(Name)                              \
   class Name : public BinaryOp {                           \
   public:                                               \
   Name (Node* p1, Node* p2): BinaryOp(p1, p2) {}           \
   void do_op(Image& res, Image& op1, Image& op2);       \
   std::string head() const;                             \
   Node *clone () const {                                \
      return new Name(op1()->clone(), op2()->clone());	\
   }                                                     \
   }

DEF_BINARY_OP(Sum);
DEF_BINARY_OP(Sub);
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

// Operacions Ternàries /////////////////////////////////////////////////////

class Warp : public Node {
   Node *p1, *p2, *p3;
public:
   Warp(Node *_p1, Node *_p2, Node *_p3) {
      p1 = _p1, p2 = _p2, p3 = _p3;
   }

   Node *op1() const { return p1; }
   Node *op2() const { return p2; }
   Node *op3() const { return p3; }
  
   void eval(Image& I);
   void destroy();
   int  depth() const { 
      return (1 + std::max(p1->depth(), 
                           std::max(p2->depth(), 
                                    p3->depth()))); 
   }
   int  size() const { 
      return (1 + p1->size() + p2->size() + p3->size()); 
   }
   void print(std::ostream& o) const;
   Node *clone() const { 
      return new Warp(p1->clone(), p2->clone(), p3->clone());
   }

   Node *_mutate(int& idx);

   void accept(Visitor& v);
};

class Dissolve : public Node {
   Node *p1, *p2, *p3;
public:
   Dissolve(Node *_p1, Node *_p2, Node *_p3) {
      p1 = _p1, p2 = _p2, p3 = _p3;
   }

   Node *op1() const { return p1; }
   Node *op2() const { return p2; }
   Node *op3() const { return p3; }

   void eval(Image& I);
   void destroy();
   int  depth() const { 
      return (1 + std::max(p1->depth(), 
                           std::max(p2->depth(), 
                                    p3->depth()))); 
   }
   int  size() const {
      return (1 + p1->size() + p2->size() + p3->size()); 
   }
   void print(std::ostream& o) const;

   Node *clone() const { 
      return new Dissolve(p1->clone(), p2->clone(), p3->clone());
   }

   Node *_mutate(int& idx);

   void accept(Visitor& v);
};


// Visitor ///////////////////////////////////////////////////////////

class Visitor {
public:
   virtual void visitLeaf(Leaf *) = 0;
   virtual void visitUnaryOp(UnaryOp *) = 0;
   virtual void visitBinaryOp(BinaryOp *) = 0;
   virtual void visitDissolve(Dissolve *) = 0;
   virtual void visitWarp(Warp *) = 0;
};

inline void Leaf::accept(Visitor& v) { v.visitLeaf(this); }
inline void UnaryOp::accept(Visitor& v) { v.visitUnaryOp(this); }
inline void BinaryOp::accept(Visitor& v) { v.visitBinaryOp(this); }
inline void Dissolve::accept(Visitor& v) { v.visitDissolve(this); }
inline void Warp::accept(Visitor& v) { v.visitWarp(this); }

class GraphvizVisitor : public Visitor {
   std::ostream& _out;
   int _idx;
public:
   GraphvizVisitor(std::ostream& out)
      :_out(out), _idx(0) {
      _out << "digraph G {" << std::endl;
   }

   ~GraphvizVisitor() {
      _out << "}" << std::endl;
   }

   void visitLeaf(Leaf *);
   void visitUnaryOp(UnaryOp *);
   void visitBinaryOp(BinaryOp *);
   void visitDissolve(Dissolve *);
   void visitWarp(Warp *);
};

void show_graph(Node *);

// Reader ////////////////////////////////////////////////////////////

// std::string read_token(std::istream& i);
// float read_number(std::istream& i);
// Node* read_vec(std::istream& i);
// Node* read_list(std::istream& i);
Node* read(std::istream& i);

#endif
