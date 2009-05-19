
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <readline/readline.h>
#include <Node.h>

using namespace std;

// Paràmetres
string outfile = "img.pnm"; // Nom imatge de sortida
int    width = 120;         // Amplada de la imatge
int    height = 120;        // Alçada de la imatge
int    level = 4;           // Profunditat de l'arbre generat
int    seed = -1;           // Llavor per als nombres aleatoris

int bwidth = 500, bheight = 500; // "Big" width, height

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
    Image thumb(width, height);
    pop[i]->eval(thumb);
    int c = i / 4, c2 = i % 4;

    for (int i = 0; i < thumb.getX(); i++)
      for (int j = 0; j < thumb.getY(); j++)
	mosaic.putPixel((c2*width)+i, (c*height)+j, thumb.getPixel(i, j));
    
    Image numTemp = getNumTemp(c, c2);
    for (int i = 0; i < 24; i++)
      for (int j = 0; j < 24; j++)
	mosaic.putPixel((c2*width)+i, (c*height)+j, numTemp.getPixel(i,j));
  }
}

bool parseArgs(int argc, char *argv[], vector<string>& args) {
  int k = 1;
  while (k < argc) {
    string arg(argv[k]);
    if (arg == "-h") return false;
    else if (arg == "-o") outfile = string(argv[++k]);
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
  for (uint i = 0; i < pop.size(); i++) {
    pop[i]->destroy();
  }
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

  vector<Node *> pop; // Population of images

  init_population(pop);

  cout << "EvoImage v0.1 (c) 2009, Enric Martí & Pau Fernández" << endl;
  string line = _readline();
  while (true) {
    istringstream csin(line);
    string cmd;
    csin >> cmd;
    if (cmd == "?" || cmd == "help") {
      cout << "[h]elp|?                           show this message" << endl
	   << "[s]how [image id]                  by default shows the last 16 images generation. " << endl  
	   << "[p]rint [image id]                 by default prints the last 16 images generation. " << endl 
	   << "config [width, height] <val>       sets images width or height at given value" << endl
	   << "new                                restart the population" << endl 
	   << "[n]ext  <image id>                 mutates given expression, creating a new 16 child generation"  << endl
	   << "[e]xport <image id> <filename>     export the image expression to a file"  << endl
	   << "[t]ree <image id>                  generates a graphic visualization of the image tree"  << endl
	   << "[q]uit                             quits the program" << endl;
    }
    if (cmd == "s" || cmd == "show") {
      uint num;
      csin >> num;
      if (csin) {
	if (num >= 0 && num <= pop.size()) {
	  Node *r = pop[num-1];
	  Image img(bwidth, bheight);
	  r->eval(img);
	  display(img);
	}
	else if (num < 0 || num > pop.size()) {
	  cerr << "show: index out of range" << endl;
	}
      }
      else {
	Image mosaic(width * 4, height * 4);
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
    else if (cmd == "config") {
      string subcmd;
      csin >> subcmd;
      if (csin) {
	if (subcmd == "width") {
	  csin >> width;
	}
	else if (subcmd == "height") {
	  csin >> height;
	}
      }
    }
    else if (cmd == "new") {
      init_population(pop);
      Image mosaic(width * 4, height * 4);
      compose16(mosaic, pop);
      display(mosaic);
    }
    else if (cmd == "n" || cmd == "next") {
      int idx = 0;
      csin >> idx;
      if (!csin) idx = 1;
      if (idx >= 1 && idx <= int(pop.size())) {
	next_generation(pop, idx-1);
	Image mosaic(width * 4, height * 4);
	compose16(mosaic, pop);
	display(mosaic);
      }
    }
    else if (cmd == "e" || cmd == "export") {
      string filename;
      int idx;
      csin >> idx >> filename;
      if (csin && idx >= 1 && idx <= (int)pop.size()) {
	ofstream fout(filename.c_str());
	pop[idx-1]->print(fout);
      }
      else {
	cout << "usage: export <idx> <filename>" << endl;
      }
    }
    else if (cmd == "t" || cmd == "tree") {
      int idx;
      csin >> idx;
      if (csin && idx >= 1 && idx <= (int)pop.size()) {
	show_graph(pop[idx-1]);
      }
      else {
	cout << "usage: tree <idx>" << endl;
      }
    }
    else if (cmd == "q" || cmd == "quit") {
      return 1;
    }
    
    line = _readline();
  }
}
