[#](#.md) The H.264 Advanced Video Compression Standard

## 2 Video formats and quality

2.4.2 YCrCb

```
Y = kr * R + kg * G + kb * B

Cr = R - Y

Cb = B - Y

Cg = G - Y

Y = 0.299R + 0.587G + 0.114B

Cb = 0.564(B - Y)

Cr = 0.713(R - Y)

R = Y + 1.402Cr

G = Y - 0.344Cb - 0.714Cr

B = Y + 1.772Cb

```

## 3 Video coding concepts

The goal of the prediction model is to reduce redundancy by forming a prediction of the data and subtracting this prediction from the current data. 


