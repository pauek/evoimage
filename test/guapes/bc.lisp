(/ (hsv-to-rgb (- (abs (cos (| y (^ (sharpen (cos y)) x)))) x)) (cos (abs (/ y (* y y)))))