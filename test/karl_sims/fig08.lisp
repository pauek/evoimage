(+ (min 10.8 
	(warp-rel image image 
		  (bump image x 9.6 
			#(0.57 0.02 0.15) 
			#(0.52 0.03 0.38) 3.21 2.49 10.8))) 
   (dissolve #(0.81 0.4 0.16) x 
	     (dissolve y #(0.88 0.99 0.66) image)))

