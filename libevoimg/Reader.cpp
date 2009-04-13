
#include <vector>
#include <string>
#include <cstdlib>
#include "Node.h"
using namespace std;

string read_token( std::istream& i) {
	std::string acum="";
	char c=i.get();
	while ( !i.eof() && !isspace(c) && c != ')'){
		acum += c;
		c=i.get();
		
		}
	
	if(!i.eof()) { i.putback(c );  }
	return acum;
	
	}

float read_number (std::istream& i){
	std::string token = read_token ( i);
	return (strtod (token.c_str(), NULL));	
	}



Node* read_vec(std::istream& i) {
	char c = i.get();
	c = i.get();
	//assert( c != 'c')
	
	float n1 = read_number(i);
	 c = i.get();
	float n2 = read_number(i);
	c = i.get();
	float n3 = read_number(i);
	
	
	
	c = i.get();
	//assert (c != ')');
	
	return new v_fix (n1, n2, n3);
	
	}	

char getnext (std::istream& i) {
	char c = i.get();
	while(isspace(c)){
		c=i.get();		
		}			
	i.putback(c);
	return c;
	}

Node* read_list ( std::istream& i ){
	
	vector <Node*> acum;
	char c = i.get();
	Node* n;
	string head = read_token ( i);
	while ( c != ')' ) {
		n = read ( i);
		if ( n != NULL) {acum.push_back ( n);}
		c = i.get ();  // aqui no seria get_next?
		}
	if ( head == "+" || head == "Sum" || head == "sum") { return new Sum ( acum [0], acum [1] ); }
	else if ( head == "-"  || head == "Rest" || head == "rest") { return new Rest ( acum [0] , acum [1] ); }
	else if ( head == "*" || head == "Mult" || head == "mult") { return new Mult ( acum [0], acum [1] ); }
	else if ( head == "/" || head == "Div" || head == "div") { return new Div ( acum [0], acum [1] ); }
	else if ( head == "%" || head == "Mod" || head == "mod") { return new Mod ( acum [0], acum [1] ); }
	else if ( head == "Log" || head == "log") { return new Log ( acum [0], acum [1] ); }
	else if ( head == "Round" || head == "round") { return new Round ( acum [0], acum [1] ); }
	else if ( head == "&" || head == "And" || head == "and") { return new And ( acum [0], acum [1] ); }
	else if ( head == "|" || head == "Or" || head == "or") { return new Or ( acum [0], acum [1] ); }
	else if ( head == "^" || head == "Xor" || head == "xor") { return new Xor ( acum [0], acum [1] ); }
	else if ( head == "Sin" || head == "sin") { return new Sin ( acum [0]);}
	else if ( head == "Cos" || head == "cos") { return new Cos ( acum [0]);}
	else if ( head == "Atan" || head == "atan") { return new Atan ( acum [0], acum [1] ); }
	else if ( head == "X" || head == "x") { return new X ( ); }
	else if ( head == "Y" || head == "y") { return new Y ( ); }
	else if ( head == "firGeneric" ) { return new firGeneric ( acum [0]);}
	else if ( head == "warp" ) { return new warp ( acum [0]);}
	else if ( head == "blur" ) { return new blur ( acum [0]);}
	else if ( head == "bwNoise" ) { return new bwNoise ( ); }
	else if ( head == "colorNoise" ) { return new colorNoise ( ); }
	else {return NULL;}
	
	
	}


Node* read (std::istream& i){
	std::string acum="";
	char c=getnext(i);
	
	while(isspace(c)){c=i.get();} //és redundant si ja ehem posat el getnext abans????
	
	if(c=='('){
		return read_list(i);
	}
	else if (c=='#'){
		return read_vec(i);
	}
	//Aqui és on hem de fer l'if per veure si és (x o y) o bé un numero
	else if ( c == 'x' || c == 'X' ) {
		return new X();
		}
	else if ( c == 'y' || c == 'Y' ) {
		return new Y();
		}
	return new v_fix(read_number( i));
}
