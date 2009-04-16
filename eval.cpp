
#include <iostream>
#include <sstream>
#include <vector>
#include <Node.h>

using namespace std;

// Paràmetres
int    width = 400;        // Amplada de la imatge
int    height = 400;       // Alçada de la imatge
string outfile = "img.pnm"; // Nom de fitxer de sortida

int str2int(string s) {
  double d;
  stringstream sin(s);
  sin >> d;
  return d;
}

void parseArgs(int argc, char *argv[], vector<string>& args) {
  int k = 1;
  while (k < argc) {
    string arg(argv[k]);
    if (arg == "-o")      outfile = string(argv[++k]);
    else if (arg == "-w") width  = str2int(argv[++k]);
    else if (arg == "-h") height = str2int(argv[++k]);
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
  cout << " -o, output file [\"" << outfile << "\"]" << endl;
  cout << endl;
  exit(0);
}

int main(int argc, char *argv[]) {
  vector<string> args;
  parseArgs(argc, argv, args);
  if (args.size() != 1) usage();
  
  stringstream sin(args[0]); 
  Node* root = read(sin);
  Image I(width, height);
  root->eval(I);  
  I.save_pnm(outfile);
}
