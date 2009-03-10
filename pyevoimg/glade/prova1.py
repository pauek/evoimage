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
	def on_inicia_activate(self):
		print "inicia"

	def __init__(self):
		self.gladefile = "prova1.glade"  
		self.wTree = gtk.glade.XML(self.gladefile, "window1")
		dic = { "on_inicia_activate" : self.on_inicia_activate }
		self.wTree.signal_autoconnect(dic)

if __name__ == "__main__":
	p1g = Prova1GTK()
	gtk.main()
