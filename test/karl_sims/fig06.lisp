(dissolve (cos (and 0.25 #(0.43 0.73 0.74))) 
	  (log (+ (warped-bw-noise (min z 11.1) 
				   (log (rotate-vector 
					 (+ (warped-bw-noise (cos x) 
							     (dissolve (cos (and 0.25 
										 #(0.43 0.73 0.74))) 
								       (log (+ (warped-bw-noise 
										(max (min z 8.26) 
										     (/ -0.5 #(0.82 0.39 0.19))) 
										(log (+ (warped-bw-noise 
											 (cos x) z -0.04 0.89) 
											#(0.82 0.39 0.19)) 
										     #(0.15 0.34 0.50)) 
										-0.04 -3.0) 
									       y) 
									    #(0.15 0.34 0.50)) 
								       y) 
							     -0.04 -3.0) 
					    x) 
					 z y) 
					#(0.15 0.34 0.5)) 
				   -0.02 -1.79) 
		  -0.4) 
	       #(-0.09 0.34 0.55)) 
	  -0.7)

