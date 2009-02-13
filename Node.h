#include <math.h>

#ifndef Node_h
#define Node_h

typedef double (*PFunction)(double);

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

  RGB operator+(const RGB& o);
  RGB operator*(const RGB& o);
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

//! Classe Node: Mare de les altres
class Node {
  //! 1r parametre
public:
  //! eval virtual, s'implanta en les filles.
  virtual RGB eval(Env& e) = 0;
};

class BinOp : public Node {
  Node *p1, *p2;

protected:
  Node* op1() { return p1; }
  Node* op2() { return p2; }
  
public:
  BinOp(Node* _p1, Node* _p2) {
    p1 = _p1;
    p2 = _p2;
  }
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
  //! constructor.
  Sum(Node* p1, Node* p2): BinOp(p1, p2) {}
  //! Aqui l'eval seria fer la suma de l'eval dels dos punters que tenim no?
  RGB eval( Env& e);
};

class Mult : public BinOp {
 public:
  //! constructor. 
 Mult(Node* p1, Node* p2): BinOp(p1, p2) {}

  //! Aquí l'eval seria fer el producte de l'eval dels dos punters que tenim no?
  RGB eval(Env& e);
};

class Log10 : public UnaryOp {
 public:
  //! constructor. 
 Log10(Node* p1): UnaryOp(p1) {}

  //! Aquí l'eval seria fer el producte de l'eval dels dos punters que tenim no?
  RGB eval(Env& e);
};


class X : public Node {
public:
  //! aqui evaluar seria unicament passar el valor de la posicio del vector no? la variable x aquesta
  RGB eval( Env& e);
};

class Y : public Node {
  //! Aquest parametre és el que considero que és el valor de l'index de l'eix y, aixo està bé?
public:
  //! aqui evaluar seria unicament passar el valor de la posicio del vector no? la variable y aquesta
  RGB eval( Env& e);
};



#endif
