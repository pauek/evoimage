(sharpen (dissolve (blur (hsv-to-rgb (hsv-to-rgb (+ (Sin #(75 156 129)) 
(+ (colorNoise) x))))) (Min (/ (blur (Log (gradDir x) (warp x (bwNoise) 
(bwNoise)))) (gaussBlur (Round (hsv-to-rgb x) (gaussBlur #(242 23 
119))))) (Abs (* (^ (^ (bwNoise) (colorNoise)) (emboss x)) (Log (% y 
(bwNoise)) (gaussBlur (bwNoise)))))) (Cos (Cos (| (+ (sharpen x) (Expt 
(bwNoise) #(227 25 38))) (Abs (Expt (colorNoise) x)))))))
