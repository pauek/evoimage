
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include "Node.h"
using namespace std;

// Per mostrar el graf de cada arbre en pantalla

class GraphvizVisitor : public Visitor {
   std::ostream& _out;
   int _idx;
public:
   GraphvizVisitor(std::ostream& out)
      :_out(out), _idx(0) {
      _out << "digraph G {" << std::endl;
   }

   ~GraphvizVisitor() {
      _out << "}" << std::endl;
   }

   void visitLeaf(Leaf *);
   void visitUnaryOp(UnaryOp *);
   void visitBinaryOp(BinaryOp *);
   void visitDissolve(Dissolve *);
   void visitWarp(Warp *);
};

void GraphvizVisitor::visitLeaf(Leaf *p) {
   _out << "n" << ++_idx << "[label=\"" << p->name() << "\",shape=box]" << endl;
}

void GraphvizVisitor::visitUnaryOp(UnaryOp* p) {
   p->op1()->accept(*this);
   int i1 = _idx; 
   int i2 = ++_idx;
   _out << "n" << i2 << "[label=\"" << p->head() << "\",shape=oval];" << endl;
   _out << "n" << i2 << " -> " << "n" << i1 << ";" << endl;
}

void GraphvizVisitor::visitBinaryOp(BinaryOp* p) {
   p->op1()->accept(*this); 
   int i1 = _idx; 
   p->op2()->accept(*this);
   int i2 = _idx; 
   int i3 = ++_idx;
   _out << "n" << i3 << "[label=\"" << p->head() << "\",shape=oval];" << endl;
   _out << "n" << i3 << " -> " << "n" << i1 << endl;
   _out << "n" << i3 << " -> " << "n" << i2 << endl;
}

void GraphvizVisitor::visitDissolve(Dissolve* p) {
   p->op1()->accept(*this);
   int i1 = _idx; 
   p->op2()->accept(*this);
   int i2 = _idx; 
   p->op3()->accept(*this);
   int i3 = _idx; 
   int i4 = ++_idx;
   _out << "n" << i4 << "[label=\"Dissolve\",shape=oval];" << endl;
   _out << "n" << i4 << " -> " << "n" << i1 << ";" << endl;
   _out << "n" << i4 << " -> " << "n" << i2 << ";" << endl;
   _out << "n" << i4 << " -> " << "n" << i3 << ";" << endl;
}

void GraphvizVisitor::visitWarp(Warp* p) {
   p->op1()->accept(*this);
   int i1 = _idx; 
   p->op2()->accept(*this);
   int i2 = _idx; 
   p->op3()->accept(*this);
   int i3 = _idx; 
   int i4 = ++_idx;
   _out << "n" << i4 << "[label=\"Warp\",shape=oval];" << endl;
   _out << "n" << i4 << " -> " << "n" << i1 << ";" << endl;
   _out << "n" << i4 << " -> " << "n" << i2 << ";" << endl;
   _out << "n" << i4 << " -> " << "n" << i3 << ";" << endl;
}

void show_graph(Node *p) {
   static int idx = -1;
   {
      char name[100];
      sprintf(name, "_g%06d.dot", ++idx);
      ofstream out(name);
      {
         GraphvizVisitor G(out);
         p->accept(G);
      }
   }
   if (fork() == 0) {
      char cmd[1000];
      sprintf(cmd, "dot -Tpng -o _g%06d.png _g%06d.dot", idx, idx); 
      system(cmd);
      sprintf(cmd, "display _g%06d.png", idx); 
      system(cmd);
      sprintf(cmd, "rm _g%06d.png _g%06d.dot", idx, idx);
      system(cmd);
      exit(0);
   }
}
