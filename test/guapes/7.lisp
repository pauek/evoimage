(sharpen (dissolve (blur (hsv-to-rgb (hsv-to-rgb (+ (Sin #(75 156 129)) 
(+ (colorNoise 0) x))))) (Min (/ (blur (Log (gradDir x) (warp x (bwNoise 0) 
(bwNoise 0)))) (gaussBlur (Round (hsv-to-rgb x) (gaussBlur #(242 23 
119))))) (Abs (* (^ (^ (bwNoise 0) (colorNoise 0)) (emboss x)) (Log (% y 
(bwNoise 0)) (gaussBlur (bwNoise 0)))))) (Cos (Cos (| (+ (sharpen x) (Expt 
(bwNoise 0) #(227 25 38))) (Abs (Expt (colorNoise 0) x)))))))
