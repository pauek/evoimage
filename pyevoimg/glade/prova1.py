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

class Prova1GTK:
	def on_inicia_activate(self , window):
		print "inicia"

	def on_atura_i_surt_activate(self , window):
		gtk.main_quit()
	
	def on_resolucio_activate(self , window):
        	self.setter.show()
	
	def gtk_widget_destroy(self , window):
		print "esborrat"
		gtk_widget_destroy()
		
	

	def on_window1_destroy(self , window):
		gtk.main_quit()

	def __init__(self):
		self.gladefile = "prova1.glade"  
		self.wTree = gtk.glade.XML(self.gladefile)
		
		self.setter = gtk.glade.XML.get_widget(self.wTree , "res_setter")
		
		dic = { "on_inicia_activate" : self.on_inicia_activate,
			"on_atura_i_surt_activate" : self.on_atura_i_surt_activate,
			"on_resolucio_activate" : self.on_resolucio_activate,
			"getk_widget_destroy" : self.gtk_widget_destroy,
			"on_window1_destroy" : self.on_window1_destroy }
		self.wTree.signal_autoconnect(dic)

if __name__ == "__main__":
	p1g = Prova1GTK()
	gtk.main()
