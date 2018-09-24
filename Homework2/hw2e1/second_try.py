from Ex1 import binarize
from tesst import drawPattern

num_linearly_separable = 0
for i in range(256):
    if drawPattern(binarize(i)):
        num_linearly_separable += 1

print(num_linearly_separable)
