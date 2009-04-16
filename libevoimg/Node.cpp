#include <string>
#include "Node.h"
using namespace std;

Node* Node::randomNode(int level) {
  int selector;
  
  selector = rand() % 21;
  cout << selector;
  
  if( selector == 0) { 
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Sum ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Sum ( _op1, _op2);
    }
  }
  else if( selector == 1) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Rest ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Rest ( _op1, _op2);
    }
  }
  else if( selector == 2) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Mult ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Mult ( _op1, _op2);
    }
  }
  else if( selector == 3) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Div ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Div ( _op1, _op2);
    }
  }
  else if( selector == 4) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Mod ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Mod ( _op1, _op2);
    }
  }
  else if( selector == 5) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Log ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Log ( _op1, _op2);
    }
  }
  else if( selector == 6) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Round ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Round ( _op1, _op2);
    }
  }
  else if( selector == 7) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new And ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new And ( _op1, _op2);
    }
  }
  else if( selector == 8) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Or ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Or ( _op1, _op2);
    }
  }
  else if( selector == 9) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Xor ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Xor ( _op1, _op2);
    }
  }
  else if( selector == 10) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      return new Sin ( _op1);
    }
    else{
      Node* _op1 = randomLeave ();
      return new Sin ( _op1);
    }
  }
  else if( selector == 11) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      return new Cos ( _op1);
    }
    else{
      Node* _op1 = randomLeave ();
      return new Cos ( _op1);
    }
  }
  else if( selector == 12) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Atan ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Atan ( _op1, _op2);
    }
  }
  else if( selector == 13) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      return new gradDir ( _op1);
    }
    else{
      Node* _op1 = randomLeave ();
      return new gradDir ( _op1);
    }
  }
  else if( selector == 14) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      return new gaussBlur ( _op1);
    }
    else{
      Node* _op1 = randomLeave ();
      return new gaussBlur ( _op1);
    }
  }
  else if( selector == 15) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      return new emboss ( _op1);
    }
    else{
      Node* _op1 = randomLeave ();
      return new emboss ( _op1);
    }
  }
  else if( selector == 16) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      return new sharpen ( _op1);
    }
    else{
      Node* _op1 = randomLeave ();
      return new sharpen ( _op1);
    }
  }
  else if( selector == 17) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      return new warp ( _op1);
    }
    else{
      Node* _op1 = randomLeave ();
      return new warp ( _op1);
    }
  }
  else if( selector == 18) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      return new blur ( _op1);
    }
    else{
      Node* _op1 = randomLeave ();
      return new blur ( _op1);
    }
  }
  else if( selector == 19) {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      return new Abs ( _op1);
    }
    else{
      Node* _op1 = randomLeave ();
      return new Abs ( _op1);
    }
  }
  else  {  
    if ( level > 2){
      level = level - 1;
      Node* _op1 = randomNode ( level);
      Node* _op2 = randomNode ( level);
      return new Expt ( _op1, _op2);
    }
    else{
      Node* _op1 = randomLeave ();
      Node* _op2 = randomLeave ();
      return new Expt ( _op1, _op2);
    }
  }
}

Node* Node::randomLeave() {
  int selector = rand() % 5;
  if( selector == 0) {return new X ( );}
  else if( selector == 1){return new Y ( );}
  else if( selector == 2){return new v_fix ( float(rand() % 255), float(rand() % 255), float(rand() % 255));}
  else if( selector == 3){return new bwNoise ( );}
  else{
    return new colorNoise ( );
  }
}

void Env::filtraImatge (float kernel[3][3]) {
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

void Env::warpGeneric () {
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

RGB RGB::operator+(const RGB& o) {
  return RGB(_r + o._r, _g + o._g, _b + o._b);
}

RGB RGB::operator-(const RGB& o) {
  return RGB(_r - o._r, _g - o._g, _b - o._b);
}

RGB RGB::operator*(const RGB& o) {
  return RGB(_r * o._r, _g * o._g, _b * o._b);
}

RGB RGB::operator/(const RGB& o) {
  return RGB(_r / o._r, _g / o._g, _b / o._b);
}

RGB RGB::operator&(const RGB& o) {
  return RGB(float(int(_r) & int(o._r)), float(int(_g) & int(o._g)), float(int(_b) & int(o._b)));
}

RGB RGB::operator|(const RGB& o) {
  return RGB(float(int(_r) | int(o._r)), float(int(_g) | int(o._g)), float(int(_b) | int(o._b)));
}

RGB RGB::operator^(const RGB& o){
  return RGB(float(int(_r) ^ int(o._r)), float(int(_g) ^ int(o._g)), float(int(_b) ^ int(o._b)));
}

RGB RGB::map(PFunction f) {
  return RGB( f(_r), f(_g), f(_b) );
}

RGB RGB::map2(PFunction2 f , RGB o) {
  
  
  return RGB( f(_r, o.getr()), f(_g, o.getg()), f(_b, o.getb()) );
}



void Sum::eval(Env& e) {
  
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) + e2.getPixel(i,j)));
  		  		
    }
  }
  
  
}

void Rest::eval(Env& e) {
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) - e2.getPixel(i,j)));
  		  		
    }
  }
}

void Mult::eval(Env& e) {
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) * e2.getPixel(i,j)));
  		  		
    }
  }
}

void Div::eval(Env& e) {
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) / e2.getPixel(i,j)));
  		  		
    }
  }
}

void Mod::eval(Env& e){

	
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,((e1.getPixel(i,j)).map2( fmod ,  (e2.getPixel(i,j)))));
  		  		
    }
  }
	
	
}

void Log::eval(Env& e) {

  
  
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(((e1.getPixel(i,j)).map( log10 )) /  ((e2.getPixel(i,j)).map( log10))));
  		  		
    }
  }
  
  
}

void Round::eval(Env& e) {

  RGB offs = RGB( 0.5, 0.5, 0.5);
  
  
  
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,((((e1.getPixel(i,j))/(e1.getPixel(i,j)))+offs).map( floor)));
  		  		
    }
  }
  
  
}

void And::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) & e2.getPixel(i,j)));
  		  		
    }
  }	
	
}
	
void Or::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) | e2.getPixel(i,j)));
  		  		
    }
  }	
	
}
	
void Xor::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j) ^ e2.getPixel(i,j)));
  		  		
    }
  }	
	
}

void Sin::eval ( Env& e){

	
	
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
  op1()->eval(e1); 
  
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)).map( sin ));
  		  		
    }
  }	
	
	
}
	
void Cos::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
  op1()->eval(e1); 
  
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)).map( cos ));
  		  		
    }
  }
}

void Atan::eval(Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
  op1()->eval(e1); 
  op2()->eval(e2);
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,((e1.getPixel(i,j)).map2( atan2 ,  (e2.getPixel(i,j)))));
  		  		
    }
  }
	
}

void X::eval(Env& e) { 
 
  int x=e.getX();
  int y=e.getY();
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j = 0 ; j < y ; j++){
  		
      e.putPixel(i,j,RGB(float(i)/float(x)));
  		  		
    }
  }
 
}

void Y::eval(Env& e) { 
  
  int x=e.getX();
  int y=e.getY();
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j = 0 ; j < y ; j++){
  		
      e.putPixel(i,j,RGB(float(j)/float(y)));
  		  		
    }
  }
  
}

void v_fix::eval(Env& e) {
	  
  int x=e.getX();
  int y=e.getY();
	  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j = 0 ; j < y ; j++){
  		
      e.putPixel(i,j,RGB( p1 , p2 , p3 ));
  		  		
    }
  }
}




	
void gaussBlur::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
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
	
void gradDir::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
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
	
void emboss::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
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

void sharpen::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
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

void warp::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
  op1()->eval(e1); 
  
  e1.warpGeneric();
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)));
  		  		
    }
  }
}

void blur::eval ( Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
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
	
	
void bwNoise::eval(Env& e) {
	  
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

void colorNoise::eval(Env& e) {
	  
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

void Abs::eval ( Env& e){

	
	
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  
  op1()->eval(e1); 
  
  
  int i,j;
  for (i = 0 ; i < x ; i++){
    for (j=0 ; j < y ; j++){
  		
      e.putPixel(i,j,(e1.getPixel(i,j)).map( fabs ));
  		  		
    }
  }	
	
	
}
	
	
void Expt::eval(Env& e){
  int x=e.getX();
  int y=e.getY();
   
  Env e1(x , y);
  Env e2(x , y);
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
