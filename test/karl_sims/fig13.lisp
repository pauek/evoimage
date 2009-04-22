(sin 
 (+ (- (grad-direction (blur (if (hsv-to-rgb (warped-color-noise 
					      #(0.57 0.73 0.92) 
					      (/ 1.85 (warped-color-noise x y 0.02 3.08)) 
					      0.11 2.4)) 
				 #(0.54 0.73 0.59) 
				 #(1.06 0.82 0.06)) 
			     3.1) 
		       1.46 5.9) 
       (hsv-to-rgb 
	(warped-color-noise y (/ 4.5 (warped-color-noise y (/ x y) 2.4 2.4)) 
			    0.02 2.4))) 
    x))

