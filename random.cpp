
#include <iostream>
#include <sstream>
#include <vector>
#include <Node.h>

using namespace std;

// Paràmetres
string outfile1 = "<none>"; // Nom imatge de sortida
string outfile2 = "<none>"; // Nom imatge de sortida
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

bool parseArgs(int argc, char *argv[], vector<string>& args) {
  int k = 1;
  while (k < argc) {
    string arg(argv[k]);
    if (arg == "--help") return false;
    else if (arg == "-o1") outfile1 = string(argv[++k]);
    else if (arg == "-o2") outfile2 = string(argv[++k]);
    else if (arg == "-w")  width  = str2int(argv[++k]);
    else if (arg == "-h")  height = str2int(argv[++k]);
    else if (arg == "-l")  level  = str2int(argv[++k]);
    else if (arg == "-s")  seed   = str2int(argv[++k]);
    else {
      args.push_back(arg);
      k++;
    }
  }
  return true;
}

void usage() {
  cout << "usage: random [options]" << endl;
  cout << endl;
  cout << "options: " << endl;
  cout << " -w, image width [" << width << "]" << endl;
  cout << " -h, image height [" << height << "]" << endl;
  cout << " -l, expr depth [" << level << "]" << endl;
  cout << " -s, seed [" << seed << "]" << endl;
  cout << " -o1, output file 1 [\"" << outfile1 << "\"]" << endl;
  cout << " -o2, output file 2 [\"" << outfile2 << "\"]" << endl;
  cout << endl;
  exit(0);
}

void display(const Image& I) {
  static int idx = 0;
  char tmpfile[] = "/tmp/evoimgXXXXXX";
  sprintf(tmpfile, "/tmp/evoimg%06d", idx++);
  string outfile = string(tmpfile) + ".pnm";
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
  vector<string> _args;
  if (!parseArgs(argc, argv, _args)) {
    usage();
  }

  srand(seed != -1 ? seed : unsigned(time(0)));
  
  Node* root = Node::randomNode(level);
  root->print(cout);
  cout << endl;

  // Imatge a l'atzar
  Image I(width, height);
  root->eval(I);
  if (outfile1 == "<none>") {
    display(I);
  }
  else {
    I.save_pnm(outfile1);
  }

  // 1 Mutant
  root = root->mutate();
  root->print(cout);
  cout << endl;

  Image I2(width, height);
  root->eval(I2);
  if (outfile2 == "<none>") {
    display(I2);
  }
  else {
    I2.save_pnm(outfile2);
  }
}
