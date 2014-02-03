
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <unistd.h>
#include <Node.h>

using namespace std;

// Paràmetres
int    width = 400;        // Amplada de la imatge
int    height = 400;       // Alçada de la imatge
long   seed = -1;
string expr = "";
string outfile = "<none>"; // Nom de fitxer de sortida

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
    else if (arg == "-s") seed   = str2int(argv[++k]);
    else if (arg == "-e") expr   = string(argv[++k]);
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
  cout << " -s, seed [" << seed << "]" << endl;
  cout << " -o, output file [\"" << outfile << "\"]" << endl;
  cout << endl;
  exit(0);
}

void display(const Image& I) {
  // display només es crida un cop
  char tmpfile[100];
  sprintf(tmpfile, "/tmp/evoimg.eval.%d", getpid());
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

int main(int argc, char *argv[]) {
  vector<string> args;
  parseArgs(argc, argv, args);
  srand(seed != -1 ? seed : unsigned(time(0)));
  
  istream* i;
  if (expr != "" && args.empty()) {
    i = new stringstream(expr);
  }
  else if (expr == "" && !args.empty()) {
    i = new ifstream(args[0].c_str()); 
  }
  else {
    usage();
  }

  Node* root = read(*i);
  Image I(width, height);

  root->print(cout);
  cout << endl;

  root->eval(I);  
  if (outfile == "<none>") {
    display(I);
  }
  else {
    I.save_pnm(outfile);
  }
}
