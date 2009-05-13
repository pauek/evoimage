
#include <cassert>
#include <iostream>
#include <fstream>
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
int    level = 4;           // Profunditat de l'arbre generat
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

#include "digits.cpp"

void read_digit(float digMat[11][22], int digit) {
  stringstream fin(_digit[digit]);
  string aux; 
  int x, y;
  float pixVal;
  fin >> aux;
  fin >> x;
  fin >> y;
  fin >> aux;
  for (int j = 0; j < 22; j++) {
    for(int i = 0; i < 11; i++) {
      digMat[i][j] = 0.0;
      if (fin >> pixVal) {
	digMat[i][j] = pixVal/255;
      }
    }
  }
}

void  pgm2digit(float idxMat[24][24], int idx) {
  for (int i = 0; i < 24; i++) 
    for(int j = 0; j < 24; j++) 
      idxMat[i][j] = 1.0;

  float digMat[11][22];
  // Desenes
  if (idx / 10 > 0) {
    read_digit(digMat, idx / 10);
    for (int j = 0; j < 22; j++)
      for (int i = 0; i < 11; i++)
	idxMat[i+1][j+1] = digMat[i][j];
  }
  read_digit(digMat, idx % 10);
  for (int j = 0; j < 22; j++)
    for (int i = 0; i < 11; i++)
      idxMat[i+12][j+1] = digMat[i][j];
}

Image getNumTemp(int i, int j){
  Image numTemp(24,24);
  RGB Black(0.0, 0.0, 0.0);
  RGB White(1.0, 1.0, 1.0);
  float _digit[24][24];
  pgm2digit(_digit, i*4 + j + 1);
  for (int k = 0; k < 24; k++) 
    for (int l = 0; l < 24; l++) 
      numTemp.putPixel(k, l, _digit[k][l] );

  return numTemp;
}

void compose16(Image& mosaic, const vector<Node *>& pop) {
  assert(pop.size() <= 16);
  for (uint i = 0; i < pop.size(); i++) {
    Image thumb(192, 192);
    pop[i]->eval(thumb);
    int c = i / 4, c2 = i % 4;

    for (int i = 0; i < thumb.getX(); i++)
      for (int j = 0; j < thumb.getY(); j++)
	mosaic.putPixel((c2*192)+i, (c*192)+j, thumb.getPixel(i, j));
    
    Image numTemp = getNumTemp(c, c2);
    for (int i = 0; i < 24; i++)
      for (int j = 0; j < 24; j++)
	mosaic.putPixel((c2*192)+i, (c*192)+j, numTemp.getPixel(i,j));
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

void display(const Image& I) {
  static int idx = 0;
  char tmpfile[] = "/tmp/evoimgXXXXXX";
  sprintf(tmpfile, "/tmp/evoimg%06d", idx++);
  outfile = string(tmpfile) + ".pnm";
  I.save_pnm(outfile);

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

void init_population(vector<Node *>& pop) {
  pop.resize(16);
  for (int i = 0; i < 16; i++) 
    pop[i] = Node::randomNode(level);
}

void next_generation(vector<Node *>& pop, int ifather) {
  Node *father = pop[ifather];
  vector<Node *> next;
  next.push_back(father);
  while (next.size() < pop.size()) {
    next.push_back(father->clone()->mutate());
  }
  pop.swap(next);
}

int main(int argc, char *argv[]) {
  vector<string> _args;
  if (!parseArgs(argc, argv, _args)) {
    usage();
  }

  srand(seed != -1 ? seed : unsigned(time(0)));

  vector<Node *> history;
  vector<Node *> pop; // Population of images
  Image mosaic(768, 768), img(width, height);

  init_population(pop);

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
	   << "[r]andom -- new random expression" << endl
	   << "[q]uit   -- quits the program" << endl;
    }
    if (cmd == "s" || cmd == "show") {
      uint num;
      csin >> num;
      if (csin) {
	if (num >= 0 && num < pop.size()) {
	  Node *r = pop[num-1];
	  r->eval(img);
	  display(img);
	}
	else if (num < 0 || num > pop.size()) {
	  cerr << "show: index out of range" << endl;
	}
      }
      else {
	compose16(mosaic, pop);
	display(mosaic);
      }
    }
    else if (cmd == "p" || cmd == "print") {
      for (uint i = 0; i < pop.size(); i++) {
	cout << i+1 << " = ";
	pop[i]->print(cout);
	cout << endl;
      }
    }
    else if (cmd == "save") {
      int idx;
      csin >> idx;
      if (csin) {
	history.push_back(pop[idx-1]);
      }
      else {
	cout << "usage: save <idx>" << endl;
      }
    }
    else if (cmd == "r" || cmd == "random") {
      int i;
      csin >> i;
      if (csin) {
	i--;
	if (i >= 0 && i < pop.size()) {
	  do {
	    pop[i]->destroy();
	    pop[i] = Node::randomNode(level);
	  }
	  while (BadImg(pop[i]));
	  pop[i]->print(cout);
	  cout << endl;
	}
	else {
	  cout << "index out of range" << endl;
	}
      }
      else {
	cout << "usage: random <idx>" << endl;
      }
    }
    else if (cmd == "n" || cmd == "next") {
      int idx = 0;
      csin >> idx;
      if (!csin) idx = 1;
      next_generation(pop, idx-1);
      compose16(mosaic, pop);
      display(mosaic);
    }
    else if (cmd == "h" || cmd == "history") {
      uint i;
      for (i = 0 ; i < history.size(); i++) {
	cout << i+1 << " = ";
	history[i]->print(cout);
	cout << endl;
      }
      cout << i << " = ";
      history[i]->print(cout);
      cout << endl;
    }
    else if (cmd == "q" || cmd == "quit") {
      return 1;
    }
    
    line = _readline();
  }

  pop[0]->eval(img);
  img.save_pnm(outfile);
  pop[0]->print(cout);
  cout << endl;
}
