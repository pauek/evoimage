
#include <vector>
#include <string>
#include <cstdlib>
#include <cassert>
#include "Node.h"
using namespace std;

char next(istream& i) {
   char c = i.get();
   while (isspace(c)) {
      c = i.get();
   }
   return c;
}

string read_token(istream& i) {
   string acum;
   char c = next(i);
   while (!i.eof() && !isspace(c) && c != ')') {
      acum += c;
      c = i.get();
   }
   if (!i.eof()) { 
      i.putback(c);
   }
   return acum;
}

float read_number(istream& i) {
   string token = read_token(i);
   return strtod(token.c_str(), NULL);
}

Node* read_vec(istream& i) {
   char c;
   c = i.get(); assert(c == '(');
   float n1 = read_number(i);
   float n2 = read_number(i);
   float n3 = read_number(i);
   c = i.get(); assert(c == ')');
   return new Const(n1, n2, n3);
}	

Node* read_list(istream& i) {
   vector<Node*> acum;
   string head = read_token(i);
   char c = next(i);
   while (c != ')') {
      i.putback(c);
      Node* n = read(i);
      if (n != NULL) {
         acum.push_back(n);
      }
      c = next(i);
   }
   if      (head == "Sin" || head == "sin")                   { return new Sin(acum[0]); }
   else if (head == "Cos" || head == "cos")                   { return new Cos(acum[0]); }
   else if (head == "Abs" || head == "abs")                   { return new Abs(acum[0]);}
   else if (head == "gradDir" || head == "grad-dir")          { return new GradDir(acum[0]); }
   else if (head == "gaussBlur" || head == "gauss-blur")      { return new GaussBlur(acum[0]); }
   else if (head == "Emboss" || head == "emboss")             { return new Emboss(acum[0]); }
   else if (head == "Sharpen" || head == "sharpen")           { return new Sharpen(acum[0]); }
   else if (head == "blur")                                   { return new Blur(acum[0]);}
   else if (head == "hsv-to-rgb" )                            { return new HsvToRgb(acum[0]); }
   else if (head == "bwNoise" || head == "bw-noise")          { return new BwNoise(acum[0]); }
   else if (head == "colorNoise" || head == "color-noise")    { return new ColorNoise(acum[0]); }

   else if (head == "+" || head == "Sum" || head == "sum")    { return new Sum(acum[0], acum[1]); }
   else if (head == "-"  || head == "Rest" || head == "rest") { return new Sub(acum[0] , acum[1]); }
   else if (head == "*" || head == "Mult" || head == "mult")  { return new Mult(acum[0], acum[1]); }
   else if (head == "/" || head == "Div" || head == "div")    { return new Div(acum[0], acum[1]); }
   else if (head == "%" || head == "Mod" || head == "mod")    { return new Mod(acum[0], acum[1]); }
   else if (head == "Log" || head == "log")                   { return new Log(acum[0], acum[1]); }
   else if (head == "Round" || head == "round")               { return new Round(acum[0], acum[1]); }
   else if (head == "&" || head == "And" || head == "and")    { return new And(acum[0], acum[1]); }
   else if (head == "|" || head == "Or" || head == "or")      { return new Or(acum[0], acum[1]); }
   else if (head == "^" || head == "Xor" || head == "xor")    { return new Xor(acum[0], acum[1]); }
   else if (head == "Atan" || head == "atan")                 { return new Atan(acum[0], acum[1]); }
   else if (head == "Expt" || head == "expt")                 { return new Expt(acum[0], acum[1]); }
   else if (head == "Max" || head == "max")                   { return new Max(acum[0], acum[1]); }
   else if (head == "Min" || head == "min")                   { return new Min(acum[0], acum[1]); }

   else if (head == "warp" )                                  { return new Warp(acum[0], acum[1], acum[2]); }
   else if (head == "dissolve" )                              { return new Dissolve(acum[0], acum[1], acum[2]); }
   else { 
      assert(false); 
   }
}

Node* read(istream& i) {
   char c = next(i);
   switch (c) {
   case '(':
      return read_list(i);
   case '#':
      return read_vec(i);
   case 'x': case 'X':
      return new X();
   case 'y': case 'Y':
      return new Y();
   default:
      i.putback(c);
      return new Const(read_number(i));
   }
}
