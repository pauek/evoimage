
#include <sstream>
using std::stringstream;

#include <Python.h>
#include <Node.h>

const int XRES = 256, YRES = 256;

static PyObject*
PyEvoimg_eval(PyObject* self, PyObject* args)
{
  char *expr;
  
  if ( !PyArg_ParseTuple(args, "s", &expr) ) 
    return NULL;
  
  stringstream sin(expr);
  Node* root = read(sin);
  
  PyObject *res = PyList_New(0);
  for (int i = 0; i < XRES; i++) {
    PyObject *line = PyList_New(0);
    for (int j = 0; j < YRES; j++) {
      Env e(double(i)/double(XRES),double(j)/double(YRES));
      RGB pix = root->eval(e);
      PyList_Append(line,
		    Py_BuildValue("(i, i, i)", 
				  (int)pix.getr(), 
				  (int)pix.getg(), 
				  (int)pix.getb()));
    }
    PyList_Append(res, line);
  }
  
  return res;
}

static PyMethodDef EvoimgMethods[] = {
  { "eval", PyEvoimg_eval, METH_VARARGS,
    "eval(expr) -> image\n"
    "\n"
    "   Evaluate an image as a Lisp expression\n"
  },
  { NULL, NULL, 0, NULL } /* Sentinel */
};

PyMODINIT_FUNC
initevoimg() {
  (void)Py_InitModule("evoimg", EvoimgMethods);
}  

