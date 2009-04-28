
#include <cstdlib>
#include <string>
#include <fstream>
#include "Node.h"
using namespace std;

Node* Node::randomNode(int level) {
  Node *_op1, *_op2;
  int selector = rand() % 21;
  cout << selector;
  
  if (selector < 12) { 
    // Operacions binàries
    if (level > 2) {
      _op1 = randomNode(level - 1);
      _op2 = randomNode(level - 1);
    }
    else {
      _op1 = randomLeave();
      _op2 = randomLeave();
    }
    switch (selector) {
    case 0: return new Sum(_op1, _op2);
    case 1: return new Rest(_op1, _op2);
    case 2: return new Mult(_op1, _op2);
    case 3: return new Div(_op1, _op2);
    case 4: return new Mod(_op1, _op2);
    case 5: return new Log(_op1, _op2);
    case 6: return new Round(_op1, _op2);
    case 7: return new And(_op1, _op2);
    case 8: return new Or(_op1, _op2);
    case 9: return new Xor(_op1, _op2);
    case 10: return new Atan(_op1, _op2);
    case 11: 
    default:
      return new Expt(_op1, _op2);
    }
  }
  else {   
    // Operacions unàries
    if (level > 2)
      _op1 = randomNode (level - 1);
    else
      _op1 = randomLeave ();

    switch (selector) {
    case 12: return new Sin(_op1);
    case 13: return new Cos(_op1);
    case 14: return new gradDir(_op1);
    case 15: return new gaussBlur(_op1);
    case 16: return new emboss(_op1);
    case 17: return new sharpen(_op1);
    case 18: return new warp(_op1);
    case 19: return new blur(_op1);
    case 20: 
    default:
      return new Abs(_op1);
    }
  }
}

Node* Node::randomLeave() {
  int selector = rand() % 5;
  switch (selector) {
  case 0: return new X();
  case 1: return new Y();
  case 2: return new v_fix(rand() % 255, rand() % 255, rand() % 255);
  case 3: return new bwNoise();
  case 4: 
  default:
    return new colorNoise();
  }
}

inline int clamp(float x) {
  int v = int(x*255);
  if (v > 255) v = 255;
  if (v < 0)   v = 0;
  return v;
}

void Image::save_pnm(string name) const {
  ofstream out(name.c_str());
  int X = getX(), Y = getY();
  out << "P3" << endl
      << X << " " << Y << endl
      << "255" << endl;
  for (int j = 0; j < Y; j++) {
    for (int i = 0; i < X; i++) {
      out << clamp(getPixel( i, j ).getr()) << ' '
	  << clamp(getPixel( i, j ).getg()) << ' '
	  << clamp(getPixel( i, j ).getb()) << ' ';
    }
    out << endl;
  }
}

void Image::copyPixels(const Image& I) {
  const int _x = (x > I.x ? I.x : x);
  const int _y = (y > I.y ? I.y : y);
  for (int i = 0; i < _x; i++) {
    for (int j = 0; j < _y; j++) {
      putPixel(i, j, I.getPixel(i, j));
    }
  }
}

void Image::filtraImatge (const RGB kernel[3][3]) {
  RGB res;
  // Core
  Image Tmp(*this);
  for (int i = 1; i < x - 1; i++) {
    for (int j = 1; j < y - 1; j++) {
      res = 
	kernel[2][2] * RGB(Tmp.getPixel(i-1, j-1)) + 
	kernel[1][2] * RGB(Tmp.getPixel(i  , j-1)) + 
	kernel[0][2] * RGB(Tmp.getPixel(i+1, j-1)) + 

	kernel[2][1] * RGB(Tmp.getPixel(i-1, j  )) + 
	kernel[1][1] * RGB(Tmp.getPixel(i  , j  )) + 
	kernel[0][1] * RGB(Tmp.getPixel(i+1, j  )) + 

	kernel[2][0] * RGB(Tmp.getPixel(i-1, j+1)) + 
	kernel[1][0] * RGB(Tmp.getPixel(i  , j+1)) + 
	kernel[0][0] * RGB(Tmp.getPixel(i+1, j+1));
	
      putPixel(i, j, res);
    }
  }

  // Top
  for (int i = 1; i < x - 1; i++) {
    res = 
      kernel[2][2] * RGB(Tmp.getPixel(i-1, 0)) + 
      kernel[1][2] * RGB(Tmp.getPixel(i  , 0)) + 
      kernel[0][2] * RGB(Tmp.getPixel(i+1, 0)) + 
      
      kernel[2][1] * RGB(Tmp.getPixel(i-1, 0)) + 
      kernel[1][1] * RGB(Tmp.getPixel(i  , 0)) + 
      kernel[0][1] * RGB(Tmp.getPixel(i+1, 0)) + 
      
      kernel[2][0] * RGB(Tmp.getPixel(i-1, 1)) + 
      kernel[1][0] * RGB(Tmp.getPixel(i  , 1)) + 
      kernel[0][0] * RGB(Tmp.getPixel(i+1, 1));
	
    putPixel(i, 0, res);
  }

  // Bottom
  for (int i = 1; i < x - 1; i++) {
    res = 
      kernel[2][2] * RGB(Tmp.getPixel(i-1, y-2)) + 
      kernel[1][2] * RGB(Tmp.getPixel(i  , y-2)) + 
      kernel[0][2] * RGB(Tmp.getPixel(i+1, y-2)) + 
      
      kernel[2][1] * RGB(Tmp.getPixel(i-1, y-1)) + 
      kernel[1][1] * RGB(Tmp.getPixel(i  , y-1)) + 
      kernel[0][1] * RGB(Tmp.getPixel(i+1, y-1)) + 
      
      kernel[2][0] * RGB(Tmp.getPixel(i-1, y-1)) + 
      kernel[1][0] * RGB(Tmp.getPixel(i  , y-1)) + 
      kernel[0][0] * RGB(Tmp.getPixel(i+1, y-1));
	
    putPixel(i, y-1, res);
  }

  // Left
  for (int j = 1; j < y - 1; j++) {
    res = 
      kernel[2][2] * RGB(Tmp.getPixel(0, j-1)) + 
      kernel[1][2] * RGB(Tmp.getPixel(0, j-1)) + 
      kernel[0][2] * RGB(Tmp.getPixel(1, j-1)) + 
      
      kernel[2][1] * RGB(Tmp.getPixel(0, j  )) + 
      kernel[1][1] * RGB(Tmp.getPixel(0, j  )) + 
      kernel[0][1] * RGB(Tmp.getPixel(1, j  )) + 
      
      kernel[2][0] * RGB(Tmp.getPixel(0, j+1)) + 
      kernel[1][0] * RGB(Tmp.getPixel(0, j+1)) + 
      kernel[0][0] * RGB(Tmp.getPixel(1, j+1));
    
    putPixel(0, j, res);
  }
  
  // Right
  for (int j = 1; j < y - 1; j++) {
    res = 
      kernel[2][2] * RGB(Tmp.getPixel(x-2, j-1)) + 
      kernel[1][2] * RGB(Tmp.getPixel(x-1, j-1)) + 
      kernel[0][2] * RGB(Tmp.getPixel(x-1, j-1)) + 
      
      kernel[2][1] * RGB(Tmp.getPixel(x-2, j  )) + 
      kernel[1][1] * RGB(Tmp.getPixel(x-1, j  )) + 
      kernel[0][1] * RGB(Tmp.getPixel(x-1, j  )) + 
      
      kernel[2][0] * RGB(Tmp.getPixel(x-2, j+1)) + 
      kernel[1][0] * RGB(Tmp.getPixel(x-1, j+1)) + 
      kernel[0][0] * RGB(Tmp.getPixel(x-1, j+1));
    
    putPixel(x-1, j, res);
  }

  // TopLeft
  res = 
    kernel[2][2] * RGB(Tmp.getPixel(0, 0)) + 
    kernel[1][2] * RGB(Tmp.getPixel(0, 0)) + 
    kernel[0][2] * RGB(Tmp.getPixel(1, 0)) + 
    
    kernel[2][1] * RGB(Tmp.getPixel(0, 0)) + 
    kernel[1][1] * RGB(Tmp.getPixel(0, 0)) + 
    kernel[0][1] * RGB(Tmp.getPixel(1, 0)) + 
    
    kernel[2][0] * RGB(Tmp.getPixel(0, 1)) + 
    kernel[1][0] * RGB(Tmp.getPixel(0, 1)) + 
    kernel[0][0] * RGB(Tmp.getPixel(1, 1));

  putPixel(0, 0, res);
  
  // BottomLeft
  res = 
    kernel[2][2] * RGB(Tmp.getPixel(0, y-2)) + 
    kernel[1][2] * RGB(Tmp.getPixel(0, y-2)) + 
    kernel[0][2] * RGB(Tmp.getPixel(1, y-2)) + 
    
    kernel[2][1] * RGB(Tmp.getPixel(0, y-1)) + 
    kernel[1][1] * RGB(Tmp.getPixel(0, y-1)) + 
    kernel[0][1] * RGB(Tmp.getPixel(1, y-1)) + 
    
    kernel[2][0] * RGB(Tmp.getPixel(0, y-1)) + 
    kernel[1][0] * RGB(Tmp.getPixel(0, y-1)) + 
    kernel[0][0] * RGB(Tmp.getPixel(1, y-1));
  
  putPixel(0, y-1, res);


  // TopRight
  res = 
    kernel[2][2] * RGB(Tmp.getPixel(x-2, 0)) + 
    kernel[1][2] * RGB(Tmp.getPixel(x-1, 0)) + 
    kernel[0][2] * RGB(Tmp.getPixel(x-1, 0)) + 
    
    kernel[2][1] * RGB(Tmp.getPixel(x-2, 0)) + 
    kernel[1][1] * RGB(Tmp.getPixel(x-1, 0)) + 
    kernel[0][1] * RGB(Tmp.getPixel(x-1, 0)) + 
    
    kernel[2][0] * RGB(Tmp.getPixel(x-2, 1)) + 
    kernel[1][0] * RGB(Tmp.getPixel(x-1, 1)) + 
    kernel[0][0] * RGB(Tmp.getPixel(x-1, 1));
  
  putPixel(x-1, 0, res);

  // TopRight
  res = 
    kernel[2][2] * RGB(Tmp.getPixel(x-2, y-2)) + 
    kernel[1][2] * RGB(Tmp.getPixel(x-1, y-2)) + 
    kernel[0][2] * RGB(Tmp.getPixel(x-1, y-2)) + 
    
    kernel[2][1] * RGB(Tmp.getPixel(x-2, y-1)) + 
    kernel[1][1] * RGB(Tmp.getPixel(x-1, y-1)) + 
    kernel[0][1] * RGB(Tmp.getPixel(x-1, y-1)) + 
    					    
    kernel[2][0] * RGB(Tmp.getPixel(x-2, y-1)) + 
    kernel[1][0] * RGB(Tmp.getPixel(x-1, y-1)) + 
    kernel[0][0] * RGB(Tmp.getPixel(x-1, y-1));
  
  putPixel(x-1, y-1, res);
}

void Image::warpGeneric () {
  //De moment faré el warp amb aliasing i sense massa miraments, i només per l'eix x (que em sembla q de fet és l'y)
	
  int i,j;
  int A = x/4;
  int B = 3*x/4;
  RGB *p2;
  p2 = new RGB[x * y];
	
  for ( i = 0; i < x; i++){
    for ( j = 0; j < y; j++){
      p2[j*x+i] = getPixel( i , j );
    }
  }
	
  for ( i = 0; i < x; i++){
    for ( j = 0; j < y; j++){
      putPixel( i , j , p2[j*(A + (i/(B - A)))+i]);
    }
  }
}

// Leaf Operations ///////////////////////////////////////////////////

void Node::destroy(){
  delete this;	
}

void X::eval(Image& e) {
  float xtl, ytl, xbr, ybr;
  e.get_tl(xtl, ytl);
  e.get_br(xbr, ybr);
  const int x = e.getX(), y = e.getY();
  for (int i = 0 ; i < x ; i++)
    for (int j = 0 ; j < y ; j++)
      e.putPixel(i, j, RGB( (xbr - xtl)*float(i)/float(x-1) + xtl ));
}

void Y::eval(Image& e) { 
  float xtl, ytl, xbr, ybr;
  e.get_tl(xtl, ytl);
  e.get_br(xbr, ybr);
  const int x = e.getX(), y = e.getY();
  for (int i = 0 ; i < x ; i++)
    for (int j = 0 ; j < y ; j++)
      e.putPixel(i, j, RGB( (ybr - ytl)*float(j)/float(y-1) + ytl ));
}

void v_fix::eval(Image& e) {
  const int x = e.getX(), y = e.getY();
  for (int i = 0 ; i < x ; i++)
    for (int j = 0 ; j < y ; j++)
      e.putPixel(i, j, RGB( p1 , p2 , p3 ));
}

inline float frand() {
  return float(rand()) / float(RAND_MAX); 
}

const double noise_size = 0.05;

inline RGB linear(const RGB& a, const RGB& b, double t) {
  return a * (1 - t) + b * t;
}

inline RGB bilinear(const RGB& aa, const RGB& ab,
		    const RGB& ba, const RGB& bb,
		    double u, double v) {
  return linear( linear(aa, ab, u),
		 linear(ba, bb, u), v );
}

void Noise::eval(Image& e) {
  const int x = e.getX(), y = e.getY();
  if (seed != -1) {
    srand(seed);
  }
  
  float xtl, ytl, xbr, ybr;
  e.get_tl(xtl, ytl);
  e.get_br(xbr, ybr);
  const double width = xbr - xtl, height = ytl - ybr;
  int xsz = int(floor(width  / noise_size)) + 1;
  int ysz = int(floor(height / noise_size)) + 1;
  if (xsz > x) xsz = x;
  if (ysz > y) ysz = y;
  
  Image I(xsz, ysz);
  for (int i = 0 ; i < xsz ; i++)
    for (int j = 0 ; j < ysz ; j++)
      I.putPixel(i, j, gen_noise()); // alternativa: (frand() < .5 ? 0.0 : 1.0)

  // Bilinear interpolation
  for (int i = 0 ; i < x ; i++) {
    for (int j = 0 ; j < y ; j++) {
      double u = width  * float(i) / float(x-1);
      double v = height * float(j) / float(y-1);
      u /= noise_size;
      v /= noise_size;
      int _x = floor(u), _y = floor(v);
      double u_r = u - _x, v_r = v - _y;
      e.putPixel(i, j, 
		 bilinear( I.getPixel(_x, _y),   I.getPixel(_x+1, _y),
			   I.getPixel(_x, _y+1), I.getPixel(_x+1, _y+1),
			   u_r, v_r ));
    }
  }
}

RGB bwNoise::gen_noise() const {
  return RGB(frand());
}

RGB colorNoise::gen_noise() const {
  return RGB(frand(), frand(), frand());
}

void Warp::eval(Image& I) {
  // (warp <expr> <scale x> <scale y>)
  Image scalex(1, 1);
  p2->eval(scalex);
  float scx = scalex.getPixel(0, 0).getr();

  Image scaley(1, 1);
  p3->eval(scaley);
  float scy = scaley.getPixel(0, 0).getr();
  
  float xtl, ytl, xbr, ybr;
  I.get_tl(xtl, ytl);
  I.get_br(xbr, ybr);
  float xcen = (xtl + xbr) / 2.0;
  float ycen = (ytl + ybr) / 2.0;
  float xv = xtl - xcen, yv = ytl - ycen;
  xv *= scx, yv *= scy;
  
  Image result(I.getX(), I.getY(),
  	           xcen + xv, ycen + yv,
  	           xcen - xv, ycen - yv);
  p1->eval(result);
  I.copyPixels(result);
}

void Warp::destroy() {
  p1->destroy();
  p2->destroy();
  p3->destroy();
  delete this;
}

// Unary Operations //////////////////////////////////////////////////

void UnaryOp::destroy(){
op1()->destroy();
delete this;	
}

void Abs::eval(Image& I) {
  op1()->eval(I);
  const int x = I.getX(), y = I.getY();
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      I.putPixel(i, j, I.getPixel(i,j).map( fabs ));
}

void Sin::eval(Image& I) {
  op1()->eval(I);
  const int x = I.getX(), y = I.getY();
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      I.putPixel(i, j, I.getPixel(i,j).map( sin ));
}

void Cos::eval(Image& I) {
  op1()->eval(I);
  const int x = I.getX(), y = I.getY();
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      I.putPixel(i, j, I.getPixel(i,j).map( cos ));
}

void gaussBlur::eval(Image& I) {
  static const RGB kernel[3][3] = {
    {  1.,  2.,  1. },
    {  2.,  4.,  2. },
    {  1.,  2.,  1. }
  };
  op1()->eval(I); 
  I.filtraImatge(kernel);
}

void gradDir::eval(Image& I){
  static const RGB kernel[3][3] = {
    {  1., -2.,  1. },
    { -2.,  5., -2. },
    {  1., -2.,  1. }
  };
  op1()->eval(I); 
  I.filtraImatge(kernel);
}

void sharpen::eval(Image& I){
  static const RGB kernel[3][3] = {
    { -1., -1., -1. },
    { -1.,  9., -1. },
    { -1., -1., -1. }
  };
  op1()->eval(I); 
  I.filtraImatge(kernel);
}

void emboss::eval(Image& I){
  static const RGB kernel[3][3] = {
    {  2.,  0.,  0. },
    {  0., -1.,  0. },
    {  0.,  0., -1. }
  };
  op1()->eval(I); 
  I.filtraImatge(kernel);
}

void warp::eval(Image& I) {
  op1()->eval(I); 
  I.warpGeneric();
}

void blur::eval (Image& I){
  static const RGB kernel[3][3] = {
    { 1./9., 1./9., 1./9. },
    { 1./9., 1./9., 1./9. },
    { 1./9., 1./9., 1./9. }
  };
  op1()->eval(I); 
  I.filtraImatge(kernel);
}

// BinaryOperations //////////////////////////////////////////////////

void BinOp::destroy(){
  op1()->destroy();
  op2()->destroy();
  delete this;
}

void BinOp::eval(Image& I) {
  const int x = I.getX(), y = I.getY();
  Image i1(x, y), i2(x, y);
  op1()->eval(i1); 
  op2()->eval(i2);
  do_op(I, i1, i2);
}

#define DO_OP(Class, expr)					     \
  void Class::do_op(Image& res, Image& op1, Image& op2) {	     \
    const int x = res.getX(), y = res.getY();			     \
    for (int i = 0; i < x; i++)					     \
      for (int j = 0; j < y; j++)				     \
	res.putPixel(i, j, (expr));				     \
  }

inline float _fmod(float x, float y) {
  return (x > 0.0 ? fmod(x, y) : y - fmod(-x, y));
}

inline RGB _max(const RGB& c1, const RGB& c2) {
  return (c1.getr() > c2.getr() ? c1 : c2);
}

inline RGB _min(const RGB& c1, const RGB& c2) {
  return (c1.getr() < c2.getr() ? c1 : c2);
}

const RGB offs(0.5, 0.5, 0.5);

DO_OP(Sum,   op1.getPixel(i,j) + op2.getPixel(i,j))
DO_OP(Rest,  op1.getPixel(i,j) - op2.getPixel(i,j))
DO_OP(Mult,  op1.getPixel(i,j) * op2.getPixel(i,j))
DO_OP(Div,   op1.getPixel(i,j) / op2.getPixel(i,j))
DO_OP(And,   op1.getPixel(i,j) & op2.getPixel(i,j))
DO_OP(Or,    op1.getPixel(i,j) | op2.getPixel(i,j))
DO_OP(Xor,   op1.getPixel(i,j) ^ op2.getPixel(i,j))
DO_OP(Log,   op1.getPixel(i,j).map( log10 ) / op2.getPixel(i,j).map( log10 ))
DO_OP(Mod,   op1.getPixel(i,j).map2(_fmod, op2.getPixel(i,j)))
DO_OP(Atan,  op1.getPixel(i,j).map2( atan2, op2.getPixel(i,j) ))
DO_OP(Expt,  op1.getPixel(i,j).map2( pow, op2.getPixel(i,j) ))
DO_OP(Round, (op1.getPixel(i,j) / op1.getPixel(i,j) + offs).map( floor ))
DO_OP(Min,   _min(op1.getPixel(i, j), op2.getPixel(i, j)))
DO_OP(Max,   _max(op1.getPixel(i, j), op2.getPixel(i, j)))

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
  if( p1 == p2 || p2 == p3) { o << p1; } 
  else{ o << "#(" << p1 << " " << p2 << " " << p3 << ")"; }
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
string gaussBlur::head()  const { return "gaussBlur"; }
string gradDir::head()  const { return "gradDir"; }
string emboss::head()  const { return "emboss"; }
string sharpen::head()  const { return "sharpen"; }
string warp::head() const { return "warp";}
string blur::head() const { return "blur";}
string Abs::head()  const { return "Abs"; }
string Expt::head()  const { return "Expt"; }
string Max::head()  const { return "Max"; }
string Min::head()  const { return "Min"; }

void Y::print(ostream& o) const { o << "y"; }
void X::print(ostream& o) const { o << "x"; }
void bwNoise::print(ostream& o) const { o << "bwNoise"; }
void colorNoise::print(ostream& o) const { o << "colorNoise"; }

void Warp::print(ostream& o) const {
  o << "(warp ";  
  p1->print(o);
  o << " ";
  p2->print(o);
  o << " ";
  p3->print(o);
  o << ")";
}
