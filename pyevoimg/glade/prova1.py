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
		import test
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
