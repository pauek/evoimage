
#include <cstdlib>
#include <cassert>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
#include "Node.h"
using namespace std;

////////////////////////////////////////////////////////////

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

Node* Node::randomUnaryHead(Node* p1) {
   int selector = rand() % 9;
   switch (selector) {
   case 0: return new Sin(p1);
   case 1: return new Cos(p1);
   case 2: return new GradDir(p1);
   case 3: return new GaussBlur(p1);
   case 4: return new Emboss(p1);
   case 5: return new Sharpen(p1);
   case 6: return new Blur(p1);
   case 7: return new HsvToRgb(p1);
   case 8: return new Abs(p1);
   }
   assert(false);
   return NULL;
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
   case 1: return new Sub(p1, p2);
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
   int selector = rand() % 3;
   switch (selector) {
   case 0: 
      return new X();
   case 1:
      return new Y();
   case 2: default:
      return new Const(frand(), frand(), frand());
   }
}

Node* UnaryOp::bypassUnary() {
   Node* son = op1()->clone();
   return son;
}

Node* BinaryOp::bypassBinary() {
   Node* son = frand() < 0.5 ? op1()->clone() : op2()->clone();
   return son;
}

Node* UnaryOp::nodeAsParam(){
	
	Node* nodeP1 = this->clone();
	
	if (frand() < 0.5){
		Node* newFather = randomBinaryHead(nodeP1, randomLeaf());
		return newFather;
	}
	else{
		Node* newFather = randomUnaryHead(nodeP1);
		return newFather;
   }

	
}

Node* BinaryOp::nodeAsParam(){
	Node* nodeP1 = this->clone();
	
	if (frand() < 0.5){
		Node* newFather = randomBinaryHead(nodeP1, randomLeaf());
		return newFather;
	}
	else{
		Node* newFather = randomUnaryHead(nodeP1);
		return newFather;
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
   int X = xsize(), Y = ysize();
   out << "P3" << endl
       << X << " " << Y << endl
       << "255" << endl;
   for (int j = 0; j < Y; j++) {
      for (int i = 0; i < X; i++) {
         out << clamp(get( i, j ).getr()) << ' '
             << clamp(get( i, j ).getg()) << ' '
             << clamp(get( i, j ).getb()) << ' ';
      }
      out << endl;
   }
}

void Image::copyPixels(const Image& I) {
   const int _x = (x > I.x ? I.x : x);
   const int _y = (y > I.y ? I.y : y);
   for (int i = 0; i < _x; i++) {
      for (int j = 0; j < _y; j++) {
         put(i, j, I.get(i, j));
      }
   }
}

void Image::filtraImatge (const RGB kernel[3][3]) {
   RGB res;

   if (xsize() < 3 || ysize() < 3) return;

   // Core
   Image Tmp(*this);
   for (int i = 1; i < x - 1; i++) {
      for (int j = 1; j < y - 1; j++) {
         res = 
            kernel[2][2] * RGB(Tmp.get(i-1, j-1)) + 
            kernel[1][2] * RGB(Tmp.get(i  , j-1)) + 
            kernel[0][2] * RGB(Tmp.get(i+1, j-1)) + 

            kernel[2][1] * RGB(Tmp.get(i-1, j  )) + 
            kernel[1][1] * RGB(Tmp.get(i  , j  )) + 
            kernel[0][1] * RGB(Tmp.get(i+1, j  )) + 

            kernel[2][0] * RGB(Tmp.get(i-1, j+1)) + 
            kernel[1][0] * RGB(Tmp.get(i  , j+1)) + 
            kernel[0][0] * RGB(Tmp.get(i+1, j+1));
	
         put(i, j, res);
      }
   }

   // Top
   for (int i = 1; i < x - 1; i++) {
      res = 
         kernel[2][2] * RGB(Tmp.get(i-1, 0)) + 
         kernel[1][2] * RGB(Tmp.get(i  , 0)) + 
         kernel[0][2] * RGB(Tmp.get(i+1, 0)) + 
      
         kernel[2][1] * RGB(Tmp.get(i-1, 0)) + 
         kernel[1][1] * RGB(Tmp.get(i  , 0)) + 
         kernel[0][1] * RGB(Tmp.get(i+1, 0)) + 
      
         kernel[2][0] * RGB(Tmp.get(i-1, 1)) + 
         kernel[1][0] * RGB(Tmp.get(i  , 1)) + 
         kernel[0][0] * RGB(Tmp.get(i+1, 1));
	
      put(i, 0, res);
   }

   // Bottom
   for (int i = 1; i < x - 1; i++) {
      res = 
         kernel[2][2] * RGB(Tmp.get(i-1, y-2)) + 
         kernel[1][2] * RGB(Tmp.get(i  , y-2)) + 
         kernel[0][2] * RGB(Tmp.get(i+1, y-2)) + 
      
         kernel[2][1] * RGB(Tmp.get(i-1, y-1)) + 
         kernel[1][1] * RGB(Tmp.get(i  , y-1)) + 
         kernel[0][1] * RGB(Tmp.get(i+1, y-1)) + 
      
         kernel[2][0] * RGB(Tmp.get(i-1, y-1)) + 
         kernel[1][0] * RGB(Tmp.get(i  , y-1)) + 
         kernel[0][0] * RGB(Tmp.get(i+1, y-1));
	
      put(i, y-1, res);
   }

   // Left
   for (int j = 1; j < y - 1; j++) {
      res = 
         kernel[2][2] * RGB(Tmp.get(0, j-1)) + 
         kernel[1][2] * RGB(Tmp.get(0, j-1)) + 
         kernel[0][2] * RGB(Tmp.get(1, j-1)) + 
      
         kernel[2][1] * RGB(Tmp.get(0, j  )) + 
         kernel[1][1] * RGB(Tmp.get(0, j  )) + 
         kernel[0][1] * RGB(Tmp.get(1, j  )) + 
      
         kernel[2][0] * RGB(Tmp.get(0, j+1)) + 
         kernel[1][0] * RGB(Tmp.get(0, j+1)) + 
         kernel[0][0] * RGB(Tmp.get(1, j+1));
    
      put(0, j, res);
   }
  
   // Right
   for (int j = 1; j < y - 1; j++) {
      res = 
         kernel[2][2] * RGB(Tmp.get(x-2, j-1)) + 
         kernel[1][2] * RGB(Tmp.get(x-1, j-1)) + 
         kernel[0][2] * RGB(Tmp.get(x-1, j-1)) + 
      
         kernel[2][1] * RGB(Tmp.get(x-2, j  )) + 
         kernel[1][1] * RGB(Tmp.get(x-1, j  )) + 
         kernel[0][1] * RGB(Tmp.get(x-1, j  )) + 
      
         kernel[2][0] * RGB(Tmp.get(x-2, j+1)) + 
         kernel[1][0] * RGB(Tmp.get(x-1, j+1)) + 
         kernel[0][0] * RGB(Tmp.get(x-1, j+1));
    
      put(x-1, j, res);
   }

   // TopLeft
   res = 
      kernel[2][2] * RGB(Tmp.get(0, 0)) + 
      kernel[1][2] * RGB(Tmp.get(0, 0)) + 
      kernel[0][2] * RGB(Tmp.get(1, 0)) + 
    
      kernel[2][1] * RGB(Tmp.get(0, 0)) + 
      kernel[1][1] * RGB(Tmp.get(0, 0)) + 
      kernel[0][1] * RGB(Tmp.get(1, 0)) + 
    
      kernel[2][0] * RGB(Tmp.get(0, 1)) + 
      kernel[1][0] * RGB(Tmp.get(0, 1)) + 
      kernel[0][0] * RGB(Tmp.get(1, 1));

   put(0, 0, res);
  
   // BottomLeft
   res = 
      kernel[2][2] * RGB(Tmp.get(0, y-2)) + 
      kernel[1][2] * RGB(Tmp.get(0, y-2)) + 
      kernel[0][2] * RGB(Tmp.get(1, y-2)) + 
    
      kernel[2][1] * RGB(Tmp.get(0, y-1)) + 
      kernel[1][1] * RGB(Tmp.get(0, y-1)) + 
      kernel[0][1] * RGB(Tmp.get(1, y-1)) + 
    
      kernel[2][0] * RGB(Tmp.get(0, y-1)) + 
      kernel[1][0] * RGB(Tmp.get(0, y-1)) + 
      kernel[0][0] * RGB(Tmp.get(1, y-1));
  
   put(0, y-1, res);


   // TopRight
   res = 
      kernel[2][2] * RGB(Tmp.get(x-2, 0)) + 
      kernel[1][2] * RGB(Tmp.get(x-1, 0)) + 
      kernel[0][2] * RGB(Tmp.get(x-1, 0)) + 
    
      kernel[2][1] * RGB(Tmp.get(x-2, 0)) + 
      kernel[1][1] * RGB(Tmp.get(x-1, 0)) + 
      kernel[0][1] * RGB(Tmp.get(x-1, 0)) + 
    
      kernel[2][0] * RGB(Tmp.get(x-2, 1)) + 
      kernel[1][0] * RGB(Tmp.get(x-1, 1)) + 
      kernel[0][0] * RGB(Tmp.get(x-1, 1));
  
   put(x-1, 0, res);

   // TopRight
   res = 
      kernel[2][2] * RGB(Tmp.get(x-2, y-2)) + 
      kernel[1][2] * RGB(Tmp.get(x-1, y-2)) + 
      kernel[0][2] * RGB(Tmp.get(x-1, y-2)) + 
    
      kernel[2][1] * RGB(Tmp.get(x-2, y-1)) + 
      kernel[1][1] * RGB(Tmp.get(x-1, y-1)) + 
      kernel[0][1] * RGB(Tmp.get(x-1, y-1)) + 
    					    
      kernel[2][0] * RGB(Tmp.get(x-2, y-1)) + 
      kernel[1][0] * RGB(Tmp.get(x-1, y-1)) + 
      kernel[0][0] * RGB(Tmp.get(x-1, y-1));
  
   put(x-1, y-1, res);
}

bool Image::allBallW(){
   int countB = 0;
   int countW = 0;
   RGB B(1, 1, 1);
   RGB W(0.999, 0.999, 0.999);	
   for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++) {
         if (get(i, j) < B) { countB++; }
         if (get(i, j) > W) { countW++; }
      }
   }
   if (countB >= int(x*y*0.9) || countW >= int(x*y*0.75)) { return true; }
   else { return false; }
}


// Mutate Operations /////////////////////////////////////////////////

Node* Node::mutate() {
   int tam = size();
   int idx = (rand() % tam) + 1;
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

string Const::name() const { 
   std::stringstream s;
   s << std::setprecision(2) << p1 << ", " 
     << std::setprecision(2) << p2 << ", " 
     << std::setprecision(2) << p3;
   return s.str(); 
}

Node *Const::_mutate(int& idx) {
   p1 *= 0.8 + 0.4*frand();
   p2 *= 0.8 + 0.4*frand();
   p3 *= 0.8 + 0.4*frand();
   return Leaf::_mutate(idx);
}

Node *Const::_mutate_leaf() {
   if (frand() < .7) {
      return this;
   }
   else {
      return randomLeaf();
   }
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
      float randVal = frand();
      if (randVal < replace_prob) {
         return randomNode(depth() + 1);
      }
      else {
         if(randVal < 0.6) { 
            return randomUnaryHead(p1); 
         }
         else if (randVal < 0.8){ 
            return bypassUnary();} 
         else { return nodeAsParam();}
      }
   }
}


Node *BinaryOp::_mutate(int& idx) {
   p1 = p1->_mutate(idx);
   p2 = p2->_mutate(idx);
   if (--idx != 0) { return this; }
   else {
      float randVal = frand();
      if (randVal < replace_prob) {
         // TODO: Cas 6
         return randomNode(depth() + 1);
      }
      else {
         if(randVal < 0.6) { 
            return randomBinaryHead(p1, p2); 
         }
         else if (randVal < 0.8){ 
            return bypassBinary(); 
         }
         else{ return nodeAsParam(); }
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
   const int x = e.xsize(), y = e.ysize();
   if (x == 1 && y == 1) {
      e.put(0, 0, RGB( (xbr - xtl)/2.0 ));
   }
   else {
      for (int i = 0 ; i < x ; i++)
         for (int j = 0 ; j < y ; j++)
            e.put(i, j, RGB( (xbr - xtl)*float(i)/float(x-1) + xtl ));
   }
}

void Y::eval(Image& e) { 
   float xtl, ytl, xbr, ybr;
   e.get_tl(xtl, ytl);
   e.get_br(xbr, ybr);
   const int x = e.xsize(), y = e.ysize();
   if (x == 1 && y == 1) {
      e.put(0, 0, RGB( (ybr - ytl)/2.0 ));
   }
   else {
      for (int i = 0 ; i < x ; i++)
         for (int j = 0 ; j < y ; j++)
            e.put(i, j, RGB( (ybr - ytl)*float(j)/float(y-1) + ytl ));
   }
}

void Const::eval(Image& e) {
   const int x = e.xsize(), y = e.ysize();
   for (int i = 0 ; i < x ; i++)
      for (int j = 0 ; j < y ; j++)
         e.put(i, j, RGB( p1 , p2 , p3 ));
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

inline RGB cubic(const RGB& a, const RGB& b, const RGB& c, const RGB& d, double x) {
   return b + 0.5 * x*(c - a + x*(2.0*a - 5.0*b + 4.0*c - d + x*(3.0*(b - c) + d - a)));
}

inline RGB bicubic(const RGB& aa, const RGB& ab, const RGB& ac, const RGB& ad,
                   const RGB& ba, const RGB& bb, const RGB& bc, const RGB& bd,
                   const RGB& ca, const RGB& cb, const RGB& cc, const RGB& cd,
                   const RGB& da, const RGB& db, const RGB& dc, const RGB& dd,
                   double u, double v) {
   return cubic(cubic(aa, ab, ac, ad, u),
                cubic(ba, bb, bc, bd, u),
                cubic(ca, cb, cc, cd, u),
                cubic(da, db, dc, dd, u), v);
}


drand48_data Noise::_data;

float Noise::random() {
   double x;
   drand48_r(&_data, &x);
   return x;
}

void Noise::set_seed(int s) {
   srand48_r(s, &_data);
}

void Noise::eval(Image& e) {
   Image seed(1, 1);
   op1()->eval(seed);
   float fseed = seed.get(0, 0).getr();
   int lseed = long(floor(fseed * 10000));
   set_seed(lseed);

   const int x = e.xsize(), y = e.ysize();
   if (x == 1 && y == 1) {
      e.put(0, 0, gen_noise());
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
         I.put(i, j, gen_noise()); // alternativa: (frand() < .5 ? 0.0 : 1.0)

   // Bicubic interpolation
   for (int i = 0 ; i < x ; i++) {
      for (int j = 0 ; j < y ; j++) {
         double u = width  * float(i) / float(x-1);
         double v = height * float(j) / float(y-1);
         u /= noise_size;
         v /= noise_size;
         int _x = floor(u), _y = floor(v);
         double u_r = u - _x, v_r = v - _y;
         int _x_1 = _x - 1, _x_2 = _x + 2;
         int _y_1 = _y - 1, _y_2 = _y + 2;
         if (_x_1 < 0)   _x_1 = 0;
         if (_x_2 >= xsz) _x_2 = xsz - 1;
         if (_y_1 < 0)   _y_1 = 0;
         if (_y_2 >= xsz) _y_2 = xsz - 1;
         e.put(i, j, 
               bicubic(I.get(_x_1, _y_1), I.get(_x, _y_1), I.get(_x+1, _y_1), I.get(_x_2, _y_1),
                       I.get(_x_1, _y  ), I.get(_x, _y  ), I.get(_x+1, _y  ), I.get(_x_2, _y  ),
                       I.get(_x_1, _y+1), I.get(_x, _y+1), I.get(_x+1, _y+1), I.get(_x_2, _y+1),
                       I.get(_x_1, _y_2), I.get(_x, _y_2), I.get(_x+1, _y_2), I.get(_x_2, _y_2),
                       u_r, v_r ));
      }
   }
   
   /*
   // Bilinear interpolation
   for (int i = 0 ; i < x ; i++) {
      for (int j = 0 ; j < y ; j++) {
         double u = width  * float(i) / float(x-1);
         double v = height * float(j) / float(y-1);
         u /= noise_size;
         v /= noise_size;
         int _x = floor(u), _y = floor(v);
         double u_r = u - _x, v_r = v - _y;
         e.put(i, j, 
                    bilinear( I.get(_x, _y),   I.get(_x+1, _y),
                              I.get(_x, _y+1), I.get(_x+1, _y+1),
                              u_r, v_r ));
      }
   }
   */
}

RGB BwNoise::gen_noise() {
   return RGB(random());
}

RGB ColorNoise::gen_noise() {
   return RGB(random(), random(), random());
}

void Warp::eval(Image& I) {
   // (warp <expr> <scale x> <scale y>)
   Image scalex(1, 1);
   p2->eval(scalex);
   float scx = scalex.get(0, 0).getr();
   if (!isfinite(scx)) {
      scx = 1;
   }
   else {
      if (scx > 10.0) scx = 10.0;
      if (scx < 0.1) scx = 0.1;
   }

   Image scaley(1, 1);
   p3->eval(scaley);
   float scy = scaley.get(0, 0).getr();
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
  
   Image result(I.xsize(), I.ysize(),
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
   const int x = I.xsize(), y = I.ysize();
   Image _mask(x, y);
   p3->eval(_mask);

   Image i1(x, y);
   Image i2(x, y);
   p1->eval(i1);
   p2->eval(i2);

   /*
   ThreadedEvaluator ev;
   ev.add_node(p1, x, y);
   ev.add_node(p2, x, y);
   ev.run();
   
   Image *i1 = ev.img(0);
   Image *i2 = ev.img(1);
   */
  
   for (int i = 0 ; i < x; i++)
      for (int j = 0 ; j < y; j++) {
         RGB t = _mask.get(i, j).clamp();
         I.put(i, j, 
                    i1.get(i, j) * t + 
                    i2.get(i, j) * t.invert());
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
   const int x = I.xsize(), y = I.ysize();
   for (int i = 0; i < x; i++)
      for (int j = 0; j < y; j++)
         I.put(i, j, I.get(i,j).map( fabs ));
}

// Forcem entre 0.0 i 1.0
float mySin(float x) {
   return (1.0 + sin(M_PI * x)) / 2.0;
}

void Sin::eval(Image& I) {
   op1()->eval(I);
   const int x = I.xsize(), y = I.ysize();
   for (int i = 0; i < x; i++)
      for (int j = 0; j < y; j++)
         I.put(i, j, I.get(i,j).map( mySin ));
}

float myCos(float x) {
   return (1.0 + cos(M_PI * x)) / 2.0;
}

void Cos::eval(Image& I) {
   op1()->eval(I);
   const int x = I.xsize(), y = I.ysize();
   for (int i = 0; i < x; i++)
      for (int j = 0; j < y; j++)
         I.put(i, j, I.get(i,j).map( myCos ));
}

void GaussBlur::eval(Image& I) {
   static const RGB kernel[3][3] = {
      {  1.,  2.,  1. },
      {  2.,  4.,  2. },
      {  1.,  2.,  1. }
   };
   op1()->eval(I); 
   I.filtraImatge(kernel);
}

void GradDir::eval(Image& I){
   static const RGB kernel[3][3] = {
      {  1., -2.,  1. },
      { -2.,  5., -2. },
      {  1., -2.,  1. }
   };
   op1()->eval(I); 
   I.filtraImatge(kernel);
}

void Sharpen::eval(Image& I){
   static const RGB kernel[3][3] = {
      { -1., -1., -1. },
      { -1.,  9., -1. },
      { -1., -1., -1. }
   };
   op1()->eval(I); 
   I.filtraImatge(kernel);
}

void Emboss::eval(Image& I){
   static const RGB kernel[3][3] = {
      {  2.,  0.,  0. },
      {  0., -1.,  0. },
      {  0.,  0., -1. }
   };
   op1()->eval(I); 
   I.filtraImatge(kernel);
}

void Blur::eval (Image& I){
   static const RGB kernel[3][3] = {
      { 1./9., 1./9., 1./9. },
      { 1./9., 1./9., 1./9. },
      { 1./9., 1./9., 1./9. }
   };
   op1()->eval(I); 
   I.filtraImatge(kernel);
}

void HsvToRgb::eval(Image& I) {
   op1()->eval(I);
   const int x = I.xsize(), y = I.ysize();
   for (int i = 0; i < x; i++)
      for (int j = 0; j < y; j++)
         I.put(i, j, I.get(i,j).hsv_to_rgb());
}

// BinaryOperations //////////////////////////////////////////////////

void BinaryOp::destroy(){
   op1()->destroy();
   op2()->destroy();
   delete this;
}

void BinaryOp::eval(Image& I) {
   const int x = I.xsize(), y = I.ysize();
   /*
   -- Fora Threaded Evaluator [03/Feb/2014]

   if (p1->size() > 5 and p2->size() > 5) {
      Image *i1, *i2;
      ThreadedEvaluator ev;
      ev.add_node(p1, x, y);
      ev.add_node(p2, x, y);
      ev.run();
      i1 = ev.img(0);
      i2 = ev.img(1);
      do_op(I, *i1, *i2);
   }
   else 

   */
   {
      Image i1(x, y), i2(x, y);
      op1()->eval(i1); 
      op2()->eval(i2);
      do_op(I, i1, i2);
   }
}

#define DO_OP(Class, expr)                                  \
   void Class::do_op(Image& res, Image& op1, Image& op2) {  \
      const int x = res.xsize(), y = res.ysize();           \
      for (int i = 0; i < x; i++)                           \
         for (int j = 0; j < y; j++)                        \
            res.put(i, j, (expr));                          \
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

DO_OP(Sum,   op1.get(i,j) + op2.get(i,j))
DO_OP(Sub,   op1.get(i,j) - op2.get(i,j))
DO_OP(Mult,  op1.get(i,j) * op2.get(i,j))
DO_OP(Div,   op1.get(i,j) / op2.get(i,j))
DO_OP(And,   op1.get(i,j) & op2.get(i,j))
DO_OP(Or,    op1.get(i,j) | op2.get(i,j))
DO_OP(Xor,   op1.get(i,j) ^ op2.get(i,j))
DO_OP(Log,   op1.get(i,j).map( log10 ) / op2.get(i,j).map( log10 ))
DO_OP(Mod,   op1.get(i,j).map2(_fmod, op2.get(i,j)))
DO_OP(Atan,  op1.get(i,j).map2( atan2, op2.get(i,j) ))
DO_OP(Expt,  op1.get(i,j).map2( pow, op2.get(i,j) ))
DO_OP(Round, (op1.get(i,j) / op1.get(i,j) + offs).map( floor ))
DO_OP(Min,   _min(op1.get(i, j), op2.get(i, j)))
DO_OP(Max,   _max(op1.get(i, j), op2.get(i, j)))

void BinaryOp::print(ostream& o) const {
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

void Const::print(ostream& o) const {
   if( p1 == p2 || p2 == p3) { o << p1; } 
   else{ o << "#(" << p1 << " " << p2 << " " << p3 << ")"; }
}

string Sum::head()  const { return "+"; }
string Sub::head() const { return "-"; }
string Mult::head()  const { return "*"; }
string Div::head()  const { return "/"; }
string Mod::head()  const { return "%"; }
string Log::head()  const { return "log"; }
string Round::head()  const { return "round"; }
string And::head()  const { return "&"; }
string Or::head()  const { return "|"; }
string Xor::head()  const { return "^"; }
string Sin::head()  const { return "sin"; }
string Cos::head()  const { return "cos"; }
string Atan::head()  const { return "atan"; }
string GaussBlur::head()  const { return "gauss-blur"; }
string GradDir::head()  const { return "grad-dir"; }
string Emboss::head()  const { return "emboss"; }
string Sharpen::head()  const { return "sharpen"; }
string Blur::head() const { return "blur";}
string HsvToRgb::head() const { return "hsv-to-rgb"; }
string Abs::head()  const { return "abs"; }
string Expt::head()  const { return "expt"; }
string Max::head()  const { return "max"; }
string Min::head()  const { return "min"; }
string BwNoise::head()  const { return "bw-noise"; }
string ColorNoise::head()  const { return "color-noise"; }

void Y::print(ostream& o) const { o << "y"; }
void X::print(ostream& o) const { o << "x"; }

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
