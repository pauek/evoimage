(dissolve (/ (Cos (+ (Cos (gaussBlur y)) (* x #(1.04529 1.02033 0.277144)))) (gradDir (gradDir y))) (sharpen #(0.989437 0.528497 0.10061)) (Cos y))
