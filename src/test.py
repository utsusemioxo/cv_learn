from __future__ import print_function
import numpy as np
import cv2 as cv
alpha = 0.5

try:
    raw_input
except NameError:
    raw_input = input

print(''' Simple Linear Blender
      -------------------------
      * Enter alpha [0.0-1.0]:
      ''')
input_alpha = float(raw_input().strip())
if 0<=alpha <= 1:
    alpha = input_alpha

src1 = cv.imread("C:/Users/niuti/Documents/Dev/cv_learn/image/blend_001.jpg")
src2 = cv.imread("C:/Users/niuti/Documents/Dev/cv_learn/image/blend_002.jpg")

if src1 is None:
    print("Error loading src1")
    exit(-1)
elif src2 is None:
    print("Error loading src2")
    exit(-1)

beta = (1.0 - alpha)
# cv version: faster
dst = cv.addWeighted(src1, alpha, src2, beta, 0.0)
# numpy version: 2x slower than cv version
dst = np.uint8(alpha*(src1) + beta*(src2))

cv.imshow('dst', dst)
cv.waitKey(0)

cv.destroyAllWindows()