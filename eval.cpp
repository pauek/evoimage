
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Node.h>

using namespace std;

// Paràmetres
int    width = 400;    // Amplada de la imatge
int    height = 400;   // Alçada de la imatge
string prefix = "img"; // Prefix del nom de fitxer

void parseArgs(int argc, char *argv[], 
	       int& width, int& height, string& prefix, 
	       vector<string>& args) {
  int k = 1;
  while (k < argc) {
    string arg(argv[k]);
    if (arg == "-o") {
      prefix = string(argv[++k]);
    } 
    else if (arg == "-w") {
      stringstream sin(argv[++k]);
      sin >> width;
    }
    else if (arg == "-h") {
      stringstream sin(argv[++k]);
      sin >> height;
    }
    else {
      args.push_back(arg);
    }
    k++;
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
    Image I(width, height);
    root->eval(I);  
    stringstream sout;
    sout << prefix << k << ".pgm";
    I.save_pnm(sout.str());
  }
}
