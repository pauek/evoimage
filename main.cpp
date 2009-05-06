
#include <iostream>
#include <sstream>
#include <vector>
#include <readline/readline.h>
#include <readline/history.h>
#include <Node.h>

using namespace std;

// Paràmetres
string outfile = "img.pnm"; // Nom imatge de sortida
int    width = 400;         // Amplada de la imatge
int    height = 400;        // Alçada de la imatge
int    level = 3;           // Profunditat de l'arbre generat
int    seed = -1;           // Llavor per als nombres aleatoris

int str2int(string s) {
  double d;
  stringstream sin(s);
  sin >> d;
  return d;
}

bool BadImg (Node* n){
	Image I(20, 20);
	Image I2(33, 33);
	n->eval(I);
	n->eval(I2);
	return (I.allBallW() && I2.allBallW());	
}




char[24][24] pgm2digit(int digit){
	
ifstream fin("digit1.pgm");
string aux;
fin >> aux;
fin >> aux;
fin >> aux;	
	
}

Image getNumTemp(int i, int j){
	Image numTemp(24,24);
	RGB Black(0.0, 0.0, 0.0);
	RGB White(1.0, 1.0, 1.0);
	char _digit[24][24] = pgm2digit(1);
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 24; j++) {
			numTemp.putPixel(i, j, (_digit[i][j] == 'x' ? Black : White));
		}
	}

	return numTemp;
}

void compose16(Image& mosaic, Node* root, vector<Node *>& history){
  for (int c = 0; c < 4; c++){
	for (int c2 = 0; c2 < 4; c2++){
      history.push_back(root->clone());
      root->destroy();
      root = Node::randomNode(level);
	  while (BadImg(root)){
        root->destroy();
        root = Node::randomNode(level);
        }
      root->print(cout);
      cout << endl;	
      Image thumb(192, 192);
      root->eval(thumb);
      for (int i=0; i < thumb.getX(); i++){
    	  for (int j=0; j < thumb.getY(); j++){
    		  mosaic.putPixel((c2*191)+i, (c*191)+j, thumb.getPixel(i, j));
    		  
    		  }
    	
    	  }
    	  Image numTemp = getNumTemp(c, c2);
    	  for (int i = 0; i < 24; i++){
    	  	for (int j = 0; j < 24; j++){
    	  		
    	  		mosaic.putPixel((c2*191)+i, (c*191)+j, numTemp.getPixel(i,j));
    	  		}
    	  	}
      }
   }
}



bool parseArgs(int argc, char *argv[], vector<string>& args) {
  int k = 1;
  while (k < argc) {
    string arg(argv[k]);
    if (arg == "-h") return false;
    else if (arg == "-o") outfile = string(argv[++k]);
    else if (arg == "-w") width  = str2int(argv[++k]);
    else if (arg == "-h") height = str2int(argv[++k]);
    else if (arg == "-l") level  = str2int(argv[++k]);
    else if (arg == "-s") seed   = str2int(argv[++k]);
    else {
      args.push_back(arg);
    }
    k++;
  }
  return true;
}

void usage() {
  cout << "usage: random [options] <expr>..." << endl;
  cout << endl;
  cout << "options: " << endl;
  cout << " -w, image width [" << width << "]" << endl;
  cout << " -h, image height [" << height << "]" << endl;
  cout << " -l, expr depth [" << level << "]" << endl;
  cout << " -s, seed [" << seed << "]" << endl;
  cout << " -o, output file [\"" << outfile << "\"]" << endl;
  cout << endl;
  exit(0);
}

void display(string outfile) {
  // Launch a new process
  if (fork() == 0) {
    int ret;
    // I'm the child
    {
      stringstream sout;
      sout << "display " << outfile;
      ret = system(sout.str().c_str());
    }

    // When display finishes, we delete the file
    {
      stringstream sout;
      sout << "rm " << outfile;
      exit(system(sout.str().c_str()));
    }
  }
}

string _readline() {
  static char *_line = NULL;
  free(_line);
  _line = readline("> ");
  if (_line == NULL) {
    cout << endl;
    exit(0);
  }
  return string(_line);
}

int main(int argc, char *argv[]) {
  vector<string> _args;
  if (!parseArgs(argc, argv, _args)) {
    usage();
  }

  srand(seed != -1 ? seed : unsigned(time(0)));

  vector<Node *> history;
  Node* root = new X();
  history.push_back(root->clone());
  Image I(width, height);

  cout << "EvoImage v0.1 (c) 2009, Enric Martí & Pau Fernández" << endl;
  string line = _readline();
  while (true) {
    istringstream csin(line);
    string cmd;
    csin >> cmd;
    if (cmd == "?" || cmd == "help") {
      cout << "[h]elp|? -- show this message" << endl
	   << "[s]how   -- show image" << endl
	   << "[g]roup  -- show a group of 16 random expressions" << endl
	   << "[p]rint  -- print expression" << endl
	   << "[m]utate -- mutate expression" << endl
	   << "[r]andom -- new random expression" << endl;
    }
    if (cmd == "s" || cmd == "show") {
      uint num;
      Node *img = root;
      csin >> num;
      if (csin) {
	if (num >= 0 && num < history.size()) {
	  img = history[num];
	}
	else if (num < 0 || num > history.size()) {
	  cerr << "show: index out of range" << endl;
	}
      }
      img->eval(I);
      char _templ[] = "evalXXXXXX";
      char *tmpfile = _templ;
      tmpfile = tmpnam(tmpfile);
      outfile = string(tmpfile) + ".pnm";
      I.save_pnm(outfile);
      display(outfile);
    }
    
    else if (cmd == "g" || cmd == "group") {
      
      Image mosaic(768, 768);
      
      compose16(mosaic, root, history);
      
      char _templ[] = "evalXXXXXX";
      char *tmpfile = _templ;
      tmpfile = tmpnam(tmpfile);
      outfile = string(tmpfile) + ".pnm";
      mosaic.save_pnm(outfile);
      display(outfile);
    }
    
    else if (cmd == "p" || cmd == "print") {
      root->print(cout);
      cout << endl;
    }
    else if (cmd == "r" || cmd == "random") {
      history.push_back(root->clone());
      root->destroy();
      root = Node::randomNode(level);
      while (BadImg(root)){
      	root->destroy();
        root = Node::randomNode(level);
      }
      root->print(cout);
      cout << endl;
    }
    else if (cmd == "m" || cmd == "mutate") {
      history.push_back(root->clone());
      root = root->mutate();
      root->print(cout);
      cout << endl;
    }
    else if (cmd == "h" || cmd == "history") {
      uint i;
      for (i = 0 ; i < history.size(); i++) {
	cout << i << " = ";
	history[i]->print(cout);
	cout << endl;
      }
      cout << i << " = ";
      root->print(cout);
      cout << endl;
    }
    else if (cmd == "set") {
      root = read(csin);
    }
    
    line = _readline();
  }

  I.save_pnm(outfile);
  
  root->print(cout);
  cout << endl;
  root->destroy();
}
