
#include <cstdlib>
#include <cassert>
#include <string>
#include <fstream>
#include "Node.h"
using namespace std;

// Retorna un número entre 0.0 i 1.0
inline float frand() {
  return float(rand()) / float(RAND_MAX); 
}

RGB RGB::hsv_to_rgb() const {
  double xh = fmod( _r*360., 360 ) / 60.0;
  double i = floor(xh);
  double f = xh - i;
  double p1 = _b * (1 - _g);
  double p2 = _b * (1 - (_g * f));
  double p3 = _b * (1 - (_g * (1 - f)));

  double r = 0.0, g = 0.0, b = 0.0;
  switch ( (int)i ) {
  case 0: r = _b; g = p3; b = p1; break;
  case 1: r = p2; g = _b; b = p1; break;
  case 2: r = p1; g = _b; b = p3; break;
  case 3: r = p1; g = p2; b = _b; break;
  case 4: r = p3; g = p1; b = _b; break;
  case 5: r = _b; g = p1; b = p2; break;
  }
  return RGB(r, g, b);
}

Node *Node::randomUnaryOp(int level) {
  
  // Operacions unàries
  Node *_op1;
  if (level > 2)
    _op1 = randomNode (level - 1);
  else
    _op1 = randomLeaf();
  
  return randomUnaryHead(_op1);
  
}

Node* Node::randomUnaryHead(Node* p1){
	
  int selector = rand() % 9;
  switch (selector) {
  case 0: return new Sin(p1);
  case 1: return new Cos(p1);
  case 2: return new gradDir(p1);
  case 3: return new gaussBlur(p1);
  case 4: return new emboss(p1);
  case 5: return new sharpen(p1);
  case 6: return new blur(p1);
  case 7: return new hsv_to_rgb(p1);
  case 8: 
  default:
    return new Abs(p1);
	}
}

Node *Node::randomBinaryOp(int level) {
  
  // Operacions binàries
  Node *_op1, *_op2;
  if (level > 2) {
    _op1 = randomNode(level - 1);
    _op2 = randomNode(level - 1);
  }
  else {
    _op1 = randomLeaf();
    _op2 = randomLeaf();
  }
  return randomBinaryHead(_op1, _op2);
}

Node* Node::randomBinaryHead(Node* p1, Node* p2){
  int selector = rand() % 14;	
  switch (selector) {
  case 0: return new Sum(p1, p2);
  case 1: return new Rest(p1, p2);
  case 2: return new Mult(p1, p2);
  case 3: return new Div(p1, p2);
  case 4: return new Mod(p1, p2);
  case 5: return new Log(p1, p2);
  case 6: return new Round(p1, p2);
  case 7: return new And(p1, p2);
  case 8: return new Or(p1, p2);
  case 9: return new Xor(p1, p2);
  case 10: return new Atan(p1, p2);
  case 11: return new Min(p1, p2);
  case 12: return new Max(p1, p2);
  case 13: 
  default:
    return new Expt(p1, p2);
  }	
	
	
}

Node* Node::randomNode(int level) {
  Node *_op1, *_op2, *_op3;
  int selector = rand() % 25;
  if (selector < 9) {
    return randomUnaryOp(level);
  }
  else if (selector < 23) { 
    return randomBinaryOp(level);
  }
  else if (selector == 23 || selector == 24) {
    // Warp
    if (level > 2) {
      _op1 = randomNode(level - 1);
      _op2 = randomNode(level - 1);
      _op3 = randomNode(level - 1);
    }
    else {
      _op1 = randomLeaf();
      _op2 = randomLeaf();
      _op3 = randomLeaf();
    }
    if (selector == 23)
      return new Warp(_op1, _op2, _op3);
    else
      return new Dissolve(_op1, _op2, _op3);
  }
  assert(false);
  return NULL;
}

Node* Node::randomLeaf() {
  int selector = rand() % 8;
  switch (selector) {
  case 0: case 1: 
    return new X();
  case 2: case 3:
    return new Y();
  case 4: case 5:
    return new v_fix(frand(), frand(), frand());
  case 6: 
    return new bwNoise();
  case 7: 
  default:
    return new colorNoise();
  }
}

Node* UnaryOp::bypassUnary() {
  Node* son = op1()->clone();
  return son;
}

Node* BinOp::bypassBinary() {
  Node* son = frand() < 0.5 ? op1()->clone() : op2()->clone();
  return son;
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

  if (getX() < 3 || getY() < 3) return;

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

bool Image::allBallW(){
  int countB = 0;
  int countW = 0;
  RGB B(1, 1, 1);
  RGB W(0.999, 0.999, 0.999);	
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      if (getPixel(i, j) < B) { countB++; }
      if (getPixel(i, j) > W) { countW++; }
    }
  }
  //cout << countB << " " << countW << endl;
  if (countB >= int(x*y*0.9) || countW >= int(x*y*0.75)) { return true; }
  else { return false; }
}


// Mutate Operations /////////////////////////////////////////////////

Node* Node::mutate() {
  int tam = size();
  int idx = (rand() % tam) + 1;
  cout << tam << " " << idx << endl;
  return _mutate(idx);
}

Node *Leaf::_mutate(int& idx) {
  if (--idx != 0) { return this; }
  else {  
    if (frand() < replace_prob) {
      return randomNode(2);
    }
    else {
      return _mutate_leaf();
    }
  }
}

Node *X::_mutate_leaf() {
  if (frand() < .5) {
    destroy();
    return new Y();
  } 
  else {
    return randomLeaf();
  }
}

Node *Y::_mutate_leaf() {
  if (frand() < .5) {
    destroy();
    return new X();
  }
  else {
    return randomLeaf();
  }
}

Node *v_fix::_mutate_leaf() {
  if (frand() < .7) {
    p1 *= 0.8 + 0.4*frand();
    p2 *= 0.8 + 0.4*frand();
    p3 *= 0.8 + 0.4*frand();
    return this;
  }
  else {
    return randomLeaf();
  }
}

Node* bwNoise::_mutate_leaf() {
  return randomLeaf();
}

Node* colorNoise::_mutate_leaf() {
  return randomLeaf();
}

Node* Warp::_mutate(int& idx) {
  p1 = p1->_mutate(idx);
  p2 = p2->_mutate(idx);
  p3 = p3->_mutate(idx);
  if (--idx != 0) { return this; }
  else {
    if (frand() < replace_prob) {
      return randomNode(depth() + 1);  	
    }	
    else { return this; }
  }
}

Node* Dissolve::_mutate(int& idx) {
  p1 = p1->_mutate(idx);
  p2 = p2->_mutate(idx);
  p3 = p3->_mutate(idx);
  if (--idx != 0) { return this; }
  else {
    if (frand() < replace_prob) {
      return randomNode(depth() + 1);  	
    }	
    else { return this; }
  }
}

Node *UnaryOp::_mutate(int& idx) {
  p1 = p1->_mutate(idx);  
  if (--idx != 0) { return this; }
  else{ 
    if (frand() < replace_prob) {
      return randomNode(depth() + 1);
    }
    else {
      if(frand() < 0.6) { 
	return randomUnaryHead(p1); 
      }
      else { 
	return bypassUnary(); 
      }
    }
  }
}

Node *BinOp::_mutate(int& idx) {
  p1 = p1->_mutate(idx);
  p2 = p2->_mutate(idx);
  if (--idx != 0) { return this; }
  else {
    if (frand() < replace_prob) {
      // TODO: Cas 6
      return randomNode(depth() + 1);
    }
    else {
      if(frand() < 0.6) { 
	return randomBinaryHead(p1, p2); 
      }
      else { 
	return bypassBinary(); 
      }
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
  if (x == 1 && y == 1) {
    e.putPixel(0, 0, RGB( (xbr - xtl)/2.0 ));
  }
  else {
    for (int i = 0 ; i < x ; i++)
      for (int j = 0 ; j < y ; j++)
	e.putPixel(i, j, RGB( (xbr - xtl)*float(i)/float(x-1) + xtl ));
  }
}

void Y::eval(Image& e) { 
  float xtl, ytl, xbr, ybr;
  e.get_tl(xtl, ytl);
  e.get_br(xbr, ybr);
  const int x = e.getX(), y = e.getY();
  if (x == 1 && y == 1) {
    e.putPixel(0, 0, RGB( (ybr - ytl)/2.0 ));
  }
  else {
    for (int i = 0 ; i < x ; i++)
      for (int j = 0 ; j < y ; j++)
	e.putPixel(i, j, RGB( (ybr - ytl)*float(j)/float(y-1) + ytl ));
  }
}



void v_fix::eval(Image& e) {
  const int x = e.getX(), y = e.getY();
  for (int i = 0 ; i < x ; i++)
    for (int j = 0 ; j < y ; j++)
      e.putPixel(i, j, RGB( p1 , p2 , p3 ));
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

  if (x == 1 && y == 1) {
    e.putPixel(0, 0, gen_noise());
    return;
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
  if (!isfinite(scx)) {
    scx = 1;
  }
  else {
    if (scx > 10.0) scx = 10.0;
    if (scx < 0.1) scx = 0.1;
  }

  Image scaley(1, 1);
  p3->eval(scaley);
  float scy = scaley.getPixel(0, 0).getr();
  if (!isfinite(scy)) {
    scy = 1;
  }
  else {
    if (scy > 10.0) scy = 10.0;
    if (scy < 0.1) scy = 0.1;
  }
  
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

void Dissolve::eval(Image& I) {
  const int x = I.getX(), y = I.getY();
  Image _mask(x, y);
  p3->eval(_mask);
  
  Image I1(x, y); p1->eval(I1);
  Image I2(x, y); p2->eval(I2);

  for (int i = 0 ; i < x; i++)
    for (int j = 0 ; j < y; j++) {
      RGB t = _mask.getPixel(i, j).clamp();
      I.putPixel(i, j, 
		 I1.getPixel(i, j) * t + 
		 I2.getPixel(i, j) * t.invert());
    }
}

void Dissolve::destroy() {
  p1->destroy();
  p2->destroy();
  p3->destroy();
  delete this;
}


// Unary Operations //////////////////////////////////////////////////

void UnaryOp::destroy() {
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

// Forcem entre 0.0 i 1.0
float mySin(float x) {
  return (1.0 + sin(M_PI * x)) / 2.0;
}

void Sin::eval(Image& I) {
  op1()->eval(I);
  const int x = I.getX(), y = I.getY();
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      I.putPixel(i, j, I.getPixel(i,j).map( mySin ));
}

float myCos(float x) {
  return (1.0 + cos(M_PI * x)) / 2.0;
}

void Cos::eval(Image& I) {
  op1()->eval(I);
  const int x = I.getX(), y = I.getY();
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      I.putPixel(i, j, I.getPixel(i,j).map( myCos ));
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

void blur::eval (Image& I){
  static const RGB kernel[3][3] = {
    { 1./9., 1./9., 1./9. },
    { 1./9., 1./9., 1./9. },
    { 1./9., 1./9., 1./9. }
  };
  op1()->eval(I); 
  I.filtraImatge(kernel);
}

void hsv_to_rgb::eval(Image& I) {
  op1()->eval(I);
  const int x = I.getX(), y = I.getY();
  for (int i = 0; i < x; i++)
    for (int j = 0; j < y; j++)
      I.putPixel(i, j, I.getPixel(i,j).hsv_to_rgb());
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
string blur::head() const { return "blur";}
string hsv_to_rgb::head() const { return "hsv-to-rgb"; }
string Abs::head()  const { return "Abs"; }
string Expt::head()  const { return "Expt"; }
string Max::head()  const { return "Max"; }
string Min::head()  const { return "Min"; }

void Y::print(ostream& o) const { o << "y"; }
void X::print(ostream& o) const { o << "x"; }
void bwNoise::print(ostream& o) const { o << "(bwNoise)"; }
void colorNoise::print(ostream& o) const { o << "(colorNoise)"; }

void Warp::print(ostream& o) const {
  o << "(warp ";  
  p1->print(o);
  o << " ";
  p2->print(o);
  o << " ";
  p3->print(o);
  o << ")";
}

void Dissolve::print(ostream& o) const {
  o << "(dissolve "; 
  p1->print(o);
  o << " ";
  p2->print(o);
  o << " ";
  p3->print(o);
  o << ")";
}

// GraphViz ////////////////////////////////////////////////////

// Per mostrar el graph de cada arbre en pantalla

void GraphvizVisitor::visitLeaf(Leaf *p) {
  _out << "n" << ++_idx << "[label=\"" << p->name() << "\",shape=box]" << endl;
}

void GraphvizVisitor::visitUnaryOp(UnaryOp* p) {
  p->op1()->accept(*this);
  int i1 = _idx; 
  int i2 = ++_idx;
  _out << "n" << i2 << "[label=\"" << p->head() << "\",shape=oval];" << endl;
  _out << "n" << i2 << " -> " << "n" << i1 << ";" << endl;
}

void GraphvizVisitor::visitBinOp(BinOp* p) {
  p->op1()->accept(*this); 
  int i1 = _idx; 
  p->op2()->accept(*this);
  int i2 = _idx; 
  int i3 = ++_idx;
  _out << "n" << i3 << "[label=\"" << p->head() << "\",shape=oval];" << endl;
  _out << "n" << i3 << " -> " << "n" << i1 << endl;
  _out << "n" << i3 << " -> " << "n" << i2 << endl;
}

void GraphvizVisitor::visitDissolve(Dissolve* p) {
  p->op1()->accept(*this);
  int i1 = _idx; 
  p->op2()->accept(*this);
  int i2 = _idx; 
  p->op3()->accept(*this);
  int i3 = _idx; 
  int i4 = ++_idx;
  _out << "n" << i4 << "[label=\"Dissolve\",shape=oval];" << endl;
  _out << "n" << i4 << " -> " << "n" << i1 << ";" << endl;
  _out << "n" << i4 << " -> " << "n" << i2 << ";" << endl;
  _out << "n" << i4 << " -> " << "n" << i3 << ";" << endl;
}

void GraphvizVisitor::visitWarp(Warp* p) {
  p->op1()->accept(*this);
  int i1 = _idx; 
  p->op2()->accept(*this);
  int i2 = _idx; 
  p->op3()->accept(*this);
  int i3 = _idx; 
  int i4 = ++_idx;
  _out << "n" << i4 << "[label=\"Dissolve\",shape=oval];" << endl;
  _out << "n" << i4 << " -> " << "n" << i1 << ";" << endl;
  _out << "n" << i4 << " -> " << "n" << i2 << ";" << endl;
  _out << "n" << i4 << " -> " << "n" << i3 << ";" << endl;
}

void show_graph(Node *p) {
  static int idx = -1;
  {
    char name[100];
    sprintf(name, "_g%06d.dot", ++idx);
    ofstream out(name);
    {
      GraphvizVisitor G(out);
      p->accept(G);
    }
  }
  if (fork() == 0) {
    char cmd[1000];
    sprintf(cmd, "dot -Tpng -o _g%06d.png _g%06d.dot", idx, idx); 
    system(cmd);
    sprintf(cmd, "display _g%06d.png", idx); 
    system(cmd);
    sprintf(cmd, "rm _g%06d.png _g%06d.dot", idx, idx);
    system(cmd);
    exit(0);
  }
}
