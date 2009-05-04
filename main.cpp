
#include <iostream>
#include <sstream>
#include <vector>
#include <readline/readline.h>
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
  
  Node* root = new X();
  Image I(width, height);

  cout << "EvoImage v0.1 (c) 2009, Enric Martí & Pau Fernández" << endl;
  string cmd = _readline();
  while (cmd != "quit" && cmd != "q") {
    if (cmd == "?" || cmd == "help") {
      cout << "help | ? -- show this message" << endl
	   << "[s]how   -- show image" << endl
	   << "[p]rint  -- print expression" << endl
	   << "[m]utate -- mutate expression" << endl
	   << "[r]andom -- new random expression" << endl;
    }
    if (cmd == "s" || cmd == "show") {
      root->eval(I);
      char _templ[] = "evalXXXXXX";
      char *tmpfile = _templ;
      tmpfile = tmpnam(tmpfile);
      outfile = string(tmpfile) + ".pnm";
      I.save_pnm(outfile);
      display(outfile);
    }
    else if (cmd == "p" || cmd == "print") {
      root->print(cout);
      cout << endl;
    }
    else if (cmd == "r" || cmd == "random") {
      root->destroy();
      root = Node::randomNode(level);
      root->print(cout);
      cout << endl;
    }
    else if (cmd == "m" || cmd == "mutate") {
      root = root->mutate();
      root->print(cout);
      cout << endl;
    }

    cmd = _readline();
  }

  I.save_pnm(outfile);
  
  root->print(cout);
  cout << endl;
  root->destroy();
}
