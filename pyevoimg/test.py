#!/usr/bin/env python
from PIL import Image
import evoimg
print " inicia2"
def to_img(M):
    I = Image.new("RGB", (256, 256))
    for i in range(256):
        for j in range(256):
            I.putpixel((i, j), M[i][j])
    return I

M = evoimg.eval("(and (* x 255) (* y 255))")
I = to_img(M)
I.show()
