
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
      out << clamp(getPixel( i, j ).getr( )) << ' '
	  << clamp(getPixel( i, j ).getg( )) << ' '
	  << clamp(getPixel( i, j ).getb( )) << ' ';
    }
    out << endl;
  }
}

void Image::filtraImatge (float kernel[3][3]) {
  int i, j, m, n, mm, nn;
  int kCenterX, kCenterY;
  int kernelSizeX = 3;
  int kernelSizeY = 3;                         
  RGB sum;                                      
  int rowIndex, colIndex;
  int dataSizeX = x; 
  int dataSizeY = y;
    
  kCenterX = kernelSizeX / 2;
  kCenterY = kernelSizeY / 2;

  for(i=0; i < dataSizeY; ++i) {
    for(j=0; j < dataSizeX; ++j) {
      sum = 0.0;                            
      for(m=0; m < kernelSizeY; ++m) {
	mm = kernelSizeY - 1 - m;       // index fila del kernel girat
	
	for(n=0; n < kernelSizeX; ++n) {
	  nn = kernelSizeX - 1 - n;   // index columna del kernel girat
	  
	  // index de  l'input per mirar dspres si estem treballant amb valors de fora d la img
	  rowIndex = i + m - kCenterY;
	  colIndex = j + n - kCenterX;
	  
	  // ignorar els pixels que estan fora de la img. (hi ha altres mètodes tb)
	  if(rowIndex >= 0 && rowIndex < dataSizeY && colIndex >= 0 && colIndex < dataSizeX)
	    
	    sum = sum + ( getPixel (rowIndex , colIndex ) * RGB(kernel[mm][nn]));
	}
      }
      putPixel( i , j , (sum.map( fabs ) + 0.5f));
    }
  }	
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

RGB RGB::map(PFunction f) {
  return RGB( f(_r), f(_g), f(_b) );
}

RGB RGB::map2(PFunction2 f , RGB o) {
  return RGB( f(_r, o.getr()), f(_g, o.getg()), f(_b, o.getb()) );
}



void Sum::eval(Image& e) {
  
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) + e2.getPixel(i,j)));
  		  		
    }
  }
  
  
}

void Rest::eval(Image& e) {
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) - e2.getPixel(i,j)));
  		  		
    }
  }
}

void Mult::eval(Image& e) {
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) * e2.getPixel(i,j)));
  		  		
    }
  }
}

void Div::eval(Image& e) {
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) / e2.getPixel(i,j)));
  		  		
    }
  }
}

void Mod::eval(Image& e){

	
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,((e1.getPixel(i,j)).map2( fmod ,  (e2.getPixel(i,j)))));
  		  		
    }
  }
	
	
}

void Log::eval(Image& e) {

  
  
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(((e1.getPixel(i,j)).map( log10 )) /  ((e2.getPixel(i,j)).map( log10))));
  		  		
    }
  }
  
  
}

void Round::eval(Image& e) {

  RGB offs = RGB( 0.5, 0.5, 0.5);
  
  
  
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,((((e1.getPixel(i,j))/(e1.getPixel(i,j)))+offs).map( floor)));
  		  		
    }
  }
  
  
}

void And::eval ( Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) & e2.getPixel(i,j)));
  		  		
    }
  }	
	
}
	
void Or::eval ( Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) | e2.getPixel(i,j)));
  		  		
    }
  }	
	
}
	
void Xor::eval ( Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) ^ e2.getPixel(i,j)));
  		  		
    }
  }	
	
}

void Sin::eval ( Image& e){

	
	
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  
  op1()->eval(e1); 
  
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)).map( sin ));
  		  		
    }
  }	
	
	
}
	
void Cos::eval ( Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  
  op1()->eval(e1); 
  
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)).map( cos ));
  		  		
    }
  }
}

void Atan::eval(Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,((e1.getPixel(i,j)).map2( atan2 ,  (e2.getPixel(i,j)))));
  		  		
    }
  }
	
}

void X::eval(Image& e) { 
 
  int x=e.getX();
  int y=e.getY();
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j = 0 ; j < y ; j++){
  		
      e.putPixel(i,j,RGB(float(i)/float(x)));
  		  		
    }
  }
 
}

void Y::eval(Image& e) { 
  
  int x=e.getX();
  int y=e.getY();
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j = 0 ; j < y ; j++){
  		
      e.putPixel(i,j,RGB(float(j)/float(y)));
  		  		
    }
  }
  
}

void v_fix::eval(Image& e) {
	  
  int x=e.getX();
  int y=e.getY();
	  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j = 0 ; j < y ; j++){
  		
      e.putPixel(i,j,RGB( p1 , p2 , p3 ));
  		  		
    }
  }
}




	
void gaussBlur::eval ( Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  
  op1()->eval(e1); 
  float kernel[3][3];
  kernel[0][0]=1.0;
  kernel[0][1]=2.0;
  kernel[0][2]=1.0;
  kernel[1][0]=2.0;
  kernel[1][1]=4.0;
  kernel[1][2]=2.0;
  kernel[2][0]=1.0;
  kernel[2][1]=2.0;
  kernel[2][2]=1.0;
  e1.filtraImatge(kernel);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)));
  		  		
    }
  }
}
	
void gradDir::eval ( Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  
  op1()->eval(e1); 
  float kernel[3][3];
  kernel[0][0]=1.0;
  kernel[0][1]=-2.0;
  kernel[0][2]=1.0;
  kernel[1][0]=-2.0;
  kernel[1][1]=5.0;
  kernel[1][2]=-2.0;
  kernel[2][0]=1.0;
  kernel[2][1]=-2.0;
  kernel[2][2]=1.0;
  e1.filtraImatge(kernel);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)));
  		  		
    }
  }
}
	
void emboss::eval ( Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  
  op1()->eval(e1); 
  float kernel[3][3];
  kernel[0][0]=2.0;
  kernel[0][1]=0.0;
  kernel[0][2]=0.0;
  kernel[1][0]=0.0;
  kernel[1][1]=-1.0;
  kernel[1][2]=0.0;
  kernel[2][0]=0.0;
  kernel[2][1]=0.0;
  kernel[2][2]=-1.0;
  e1.filtraImatge(kernel);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)));
  		  		
    }
  }
}

void sharpen::eval ( Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  
  op1()->eval(e1); 
  float kernel[3][3];
  kernel[0][0]=-1.0;
  kernel[0][1]=-1.0;
  kernel[0][2]=-1.0;
  kernel[1][0]=-1.0;
  kernel[1][1]=9.0;
  kernel[1][2]=-1.0;
  kernel[2][0]=-1.0;
  kernel[2][1]=-1.0;
  kernel[2][2]=-1.0;
  e1.filtraImatge(kernel);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)));
  		  		
    }
  }
}

void warp::eval ( Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  
  op1()->eval(e1); 
  
  e1.warpGeneric();
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)));
  		  		
    }
  }
}

void blur::eval ( Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  
  op1()->eval(e1); 
  
  
  
  int i,j;
  for (i = 1 ; i < (x-1) ; i++){
    for (j = 1 ; j < (y-1) ; j++){
      RGB mitjana = ((e1.getPixel(i-1,j)) + (e1.getPixel(i,j-1)) + 
		     (e1.getPixel(i+1,j)) + (e1.getPixel(i,j+1)) +
		     (e1.getPixel(i-1,j-1)) + (e1.getPixel(i+1,j+1)) + 
		     (e1.getPixel(i-1,j+1)) + (e1.getPixel(i+1,j-1)) + 
		     (e1.getPixel(i,j)))/9;
      e.putPixel(i,j,mitjana);
  		  		
    }
  }
}
	
	
void bwNoise::eval(Image& e) {
	  
  int x=e.getX();
  int y=e.getY();
  if ( seed!=-1 ){ srand(seed);  }
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j = 0 ; j < y ; j++){
  		
      e.putPixel ( i, j, RGB ( float(rand( )/128)));
    }
  }
}

void colorNoise::eval(Image& e) {
	  
  int x=e.getX();
  int y=e.getY();
  if ( seed!=-1 ){ srand(seed);  }
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j = 0 ; j < y ; j++){
  		
      e.putPixel ( i, j, RGB ( float(rand( )/128), float(rand( )/128), float(rand( )/128)));
    }
  }
}

void Abs::eval ( Image& e){

	
	
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  
  op1()->eval(e1); 
  
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)).map( fabs ));
  		  		
    }
  }	
	
	
}
	
	
void Expt::eval(Image& e){
  int x=e.getX();
  int y=e.getY();
   
  Image e1(x , y);
  Image e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,((e1.getPixel(i,j)).map2( pow ,  (e2.getPixel(i,j)))));
  		  		
    }
  }
	
}

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

void Y::print(ostream& o) const { o << "y"; }
void X::print(ostream& o) const { o << "x"; }
void bwNoise::print(ostream& o) const { o << "bwNoise"; }
void colorNoise::print(ostream& o) const { o << "colorNoise"; }
