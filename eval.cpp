
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Node.h>

using namespace std;

// Paràmetres
int width = 400, height = 400;
string prefix = "img"; // Prefix del nom de fitxer

void parseArgs(int argc, char *argv[], 
	       int& width, int& height, string& prefix, 
	       vector<string>& args) {
  int k = 1;
  while (k < argc) {
    string arg(argv[k]);
    if (arg == "-o") {
      prefix = string(argv[++k]);
      k++;
    } 
    else if (arg == "-x") {
      stringstream sin(argv[++k]);
      sin >> width;
    }
    else if (arg == "-y") {
      stringstream sin(argv[++k]);
      sin >> height;
    }
    else {
      args.push_back(arg);
    }
    k++;
  }
}

int clamp(float x) {
  int v = int(x*255);
  if (v > 255) v = 255;
  if (v < 0)   v = 0;
  return v;
}

void save_pnm(Env& e, string name) {
  ofstream out(name.c_str());
  int X = e.getX(), Y = e.getY();
  out << "P3" << endl
      << X << " " << Y << endl
      << "255" << endl;
  for (int i = 0; i < X; i++) {
    for (int j = 0; j < Y; j++) {
      out << clamp(e.getPixel( i, j ).getr( )) << ' '
	  << clamp(e.getPixel( i, j ).getg( )) << ' '
	  << clamp(e.getPixel( i, j ).getb( )) << ' ';
    }
    out << endl;
  }
}

void usage() {
  cout << "usage: eval [options] <expr>..." << endl;
  cout << endl;
  cout << "options: " << endl;
  cout << " -w, image width [" << width << "]" << endl;
  cout << " -h, image height [" << height << "]" << endl;
  cout << " -o, output file prefix [\"" << prefix << "\"]" << endl;
  cout << endl;
  exit(0);
}

int main(int argc, char *argv[]) {
  vector<string> args;

  parseArgs(argc, argv, width, height, prefix, args);
  if (args.empty()) usage();
  
  for (int k = 0; k < (int)args.size(); k++) {
    stringstream sin(args[k]); 
    Node* root = read(sin);
    Env e(width, height);
    root->eval(e);  
    stringstream sout;
    sout << prefix << k << ".pgm";
    save_pnm(e, sout.str());
  }
}
