(* (| (warp (^ (Sin (gaussBlur y)) (+ (- #(0.350204 0.842148 0.56371) (% #(0.22916 0.0895849 0.446785) y)) (^ (bwNoise) y))) (colorNoise) x) (& (colorNoise) (colorNoise))) (Cos (gradDir (gaussBlur x))))
