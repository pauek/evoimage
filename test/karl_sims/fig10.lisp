(rotate-vector (log (+ y (color-grad 
			  (round (+ (abs (round (log #(0.01 0.67 0.86) 0.19) x)) 
				    (hsv-to-rgb (bump (if x 10.7 y) 
						      #(0.94 0.01 0.4) 0.78 
						      #(0.18 0.28 0.58) 
						      #(0.4 0.92 0.58) 10.6 0.23 0.91))) 
				 x) 
			  3.1 
			  1.93 
			  #(0.95 0.7 0.35) 3.03)) 
		    -0.03) 
	       x 
	       #(0.76 0.08 0.24))

