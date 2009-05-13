(Sin (+ (Atan (gaussBlur (sharpen x)) y) (gaussBlur (Atan (+ (warp y y y) (blur (sharpen (/ (blur y) (+ #(0.894061 0.86843 0.0604137) x))))) #(0.151793 0.393576 0.592094)))))
