#!/usr/bin/env python 
 
import sys
try:
 	import pygtk
  	pygtk.require("2.0")
except:
  	pass
try:
	import gtk
  	import gtk.glade
except:
	sys.exit(1)

def genera_escacs():
	M = []
	for i in range(256):
		fila = []
		for j in range(256):
			fila.append(((i+j)%2)*255)
		M.append(fila)
	return M

import evoimg

def matriu2pixbuf(M):
	height = len(M)
	width = len(M[0])
	B = gtk.gdk.Pixbuf(gtk.gdk.COLORSPACE_RGB, False, 8, height, width)
	A = B.get_pixels_array()
	for j in range(height):
		for i in range(width):
			A[i][j][0] = M[i][j][0]
			A[i][j][1] = M[i][j][1]
			A[i][j][2] = M[i][j][2]
	return B

class Prova1GTK:
	def on_inicia_activate(self , window):
		w_img = gtk.glade.XML.get_widget(self.wTree , "image1")
		M = evoimg.eval("(cos (* 255 x))")
		print M
		w_img.set_from_pixbuf( matriu2pixbuf(M) )
		print "inicia"

	def on_atura_i_surt_activate(self , window):
		gtk.main_quit()
	
	def on_resolucio_activate(self , window):
        	self.setter.show()
	def on_quant_a_activate(self , window):
		self.quanta.show()
	
	def gtk_widget_hide(self , window):
		print "esborrat2"
		self.setter.hide()
		
	def on_res_setter_hide(self , window):
		print "esborrat"
		self.setter.hide()
		
	def on_buttonOK_clicked(self, window):
		res = gtk_entry_get_text (self.entry1)
		print res

	def on_quant_a_close(self , window):
		self.quanta.hide()

	def on_window1_destroy(self , window):
		gtk.main_quit()

	def __init__(self):
		self.gladefile = "prova1.glade"  
		self.wTree = gtk.glade.XML(self.gladefile)
		self.window1 = gtk.glade.XML.get_widget(self.wTree , "window1")
		self.quanta = gtk.glade.XML.get_widget(self.wTree , "quant_a")
		self.setter = gtk.glade.XML.get_widget(self.wTree , "res_setter")
		
		dic = { "on_inicia_activate" : self.on_inicia_activate,
			"on_atura_i_surt_activate" : self.on_atura_i_surt_activate,
			"on_resolucio_activate" : self.on_resolucio_activate,
			"on_quant_a_activate" : self.on_quant_a_activate,
			"gtk_widget_hide" : self.gtk_widget_hide,
			"on_res_setter_hide" : self.on_res_setter_hide,
			"on_buttonOK_clicked" : self.on_buttonOK_clicked,
			"on_quant_a_close" : self.on_quant_a_close,
			"on_window1_destroy" : self.on_window1_destroy }
		self.wTree.signal_autoconnect(dic)

if __name__ == "__main__":
	p1g = Prova1GTK()
	gtk.main()
