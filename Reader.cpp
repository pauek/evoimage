
#include "Node.h"
using namespace std;

string read_token( std::istream& i) {
	std::string acum="";
	char c=i.get();
	while ( !i.eof() && !isspace(c) && c != ')'){
		acum += c;
		c=i.get();
		cout << acum << endl;
		}
	
	if(!i.eof()) { i.putback(c );  }
	return acum;
	
	}

double read_number (std::istream& i){
	std::string token = read_token ( i);
	return (strtod (token.c_str(), NULL));	
	}



Node* read_vec(std::istream& i) {
	char c = i.get();
	c = i.get();
	//assert( c != 'c')
	cout << c << endl;
	double n1 = read_number(i);
	cout << i.get() << endl;
	double n2 = read_number(i);
	cout << i.get() << endl;
	double n3 = read_number(i);
	
	cout << n1 << " " << n2 << " " << n3 << endl;
	
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
	char c;
	Node* n;
	i.get();
	string head = read_token ( i);
	while ( c != ')' ) {
		n = read ( i);
		if ( n != NULL) {acum.push_back ( n);}
		c = i.get ();  // aqui no seria get_next?
		}
	if ( head == "+") { return new Sum ( acum [0], acum [1] ); }
	else if ( head == "-") { return new Rest ( acum [0] , acum [1] ); }
	else if ( head == "*") { return new Mult ( acum [0], acum [1] ); }
	else if ( head == "/") { return new Div ( acum [0], acum [1] ); }
	else if ( head == "%") { return new Mod ( acum [0], acum [1] ); }
	else if ( head == "Log") { return new Log ( acum [0], acum [1] ); }
	else if ( head == "Round") { return new Round ( acum [0], acum [1] ); }
	else if ( head == "&") { return new And ( acum [0], acum [1] ); }
	else if ( head == "|") { return new Or ( acum [0], acum [1] ); }
	else if ( head == "^") { return new Xor ( acum [0], acum [1] ); }
	else if ( head == "Sin") { return new Sin ( acum [0]);}
	else if ( head == "Cos") { return new Cos ( acum [0]);}
	else if ( head == "Atan") { return new Atan ( acum [0], acum [1] ); }
	else if ( head == "X") { return new X ( ); }
	else if ( head == "Y") { return new Y ( ); }
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
