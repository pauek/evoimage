
#include <pthread.h>
#include "Node.h"

// ThreadedEvaluator ///////////////////////////////////////

// Traiem això perquè no es pot compilar a Javascript [03/Feb/2014]

class ThreadedEvaluator {
   struct _Thread {
      pthread_t thr;
      Node *_node;
      Image *_img;
      _Thread(Node *n, Image *i)
         :_node(n), _img(i) {}
   };

   vector<_Thread> _threads;

   static void *eval_one(void *);

public:
   ~ThreadedEvaluator() {
      for (uint i = 0; i < _threads.size(); i++)
         delete _threads[i]._img;
   }

   void add_node(Node *n, int w, int h) { 
      _threads.push_back(_Thread(n, new Image(w, h))); 
   }

   void run();

   Image *img(int n) { return _threads.at(n)._img; }
};

void ThreadedEvaluator::run() {
   // launch them
   for (uint i = 0 ; i < _threads.size(); i++) {
      pthread_create(&_threads[i].thr, NULL, eval_one, &_threads[i]);
   }
   // wait...
   for (uint i = 0 ; i < _threads.size(); i++) {
      pthread_join(_threads[i].thr, NULL);
   }
}

void *ThreadedEvaluator::eval_one(void *x) {
   _Thread *t = (_Thread*)x;
   t->_node->eval(*t->_img);
   return NULL;
}
