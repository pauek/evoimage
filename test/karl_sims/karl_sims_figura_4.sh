#!/bin/sh

../../eval -o 4a.pnm "x"
../../eval -o 4b.pnm "y"
../../eval -o 4c.pnm "(abs x)"
../../eval -o 4d.pnm "(mod x (abs y))"
../../eval -o 4e.pnm "(and x y)"
../../eval -o 4f.pnm "(bwNoise)"
../../eval -o 4g.pnm "(colorNoise)"
