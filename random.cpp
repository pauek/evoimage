
#include <iostream>
#include <sstream>
#include <vector>
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

int main(int argc, char *argv[]) {
  vector<string> _args;
  if (!parseArgs(argc, argv, _args)) {
    usage();
  }

  srand(seed != -1 ? seed : unsigned(time(0)));
  
  Node* root = Node::randomNode(level);
  Image I(width, height);
  root->eval(I);
  I.save_pnm(outfile);
  
  root->print(cout);
  cout << endl;
  root->destroy();
}
