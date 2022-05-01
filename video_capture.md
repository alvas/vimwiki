[#](#.md) The H.264 Advanced Video Compression Standard

Quarter Common Intermediate Format(QCIF)

Scalable Video Coding(SVC)

Multiview Video Coding(MVC)

multi-resolution frame-compatible(MFC)

## 2 Video formats and quality

2.3.3 Frames and fields

A video signal may be sampled as a series of complete frames, progress sampling, or as a sequence of interlaced fields, interlaced sampling. In an interlaced video sequence, half of the data in a frame, one field, is typically sampled at each temporal sampling interval. A field may consist of either the odd-numbered or even-numbered lines within a complete video frame and an interlaced video sequence typically contains a series of fields, each representing half of the information in a complete video frame.

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

2.5 Video formats

2.5.1 Intermediate formats

Common Intermediate Format(CIF)

## 3 Video coding concepts

The goal of the prediction model is to reduce redundancy by forming a prediction of the data and subtracting this prediction from the current data. 

3.4.2.2 DCT

Discrete Cosine Transform(DCT)

3.5.2.2. Pre-calculated Huffman-based coding

Transform Coefficients(TCOEF)

Motion Vector Difference(MVD)

3.5.3.1 Context-based Arithmetic Coding

Context-based Arithmetic Encoding(CAE)

## What is H.264

4.2 What is H.264?

H.264 Advanced Video Coding(AVC)

4.3 How does an H.264 codec work?

coded picture buffer(CPB); decoded picture buffer(DPB)


## H.264 syntax

5.2 H.264 syntax

Network Abstraction Layer(NAL)

Coded Block Pattern(CBP)

Sequence Parameter Sets(SPS); Picture Parameter Sets(PPS)

Coded video data is communicated in Video Coding Layer(VCL) NAL units, know as coded slices.

An access unit, a coded frame or field, is made up of one or more slices.

At the slice layer, each slice consists of a Slice Header and Slice Data. The Slice Data is a series of coded macroblocks(MB) and skip macroblock indicators which signal that certain macroblock positions contain no data.

A coded video sequence begins with an Instantaneous Decoder Refresh(IDR) Access Unit, made up of one ore more IDR slices, a special type of Intra coded slice.

Raw Byte Sequence Payload(RBSP)

frame: an array of luma samples and two corresponding arrays of chroma samples

The two fields, top field and bottom field, that make up a frame may be sampled at the same time instance, progressive scan, or at different time instants, interlaced scan.

picture: a frame or a field

Picture Order Count(POC)

Supplement Enhancementn Information(SEI)

5.3.4.1 Coding pictures in frame or field mode

Picture Adaptive Frame Field Codinng(PAFF)

5.3.4.2 Coding macroblocks in frame or field mode(MBAFF)

Macroblock Adaptive Frame Field Coding(MBAFF)

5.4 NAL unit

Video Coding Layer(VCL)

5.7.2 The Intra PCM mode

Pulse Code Modulationn(PCM)

Motion vector differences(mvd)

## H.264 Prediction

6.3.1 4x4 luma prediction modes

Sum of Absolute Errors(SAE)

6.4.2.1 Generating interpolated sub-pixel samples

Finite Impulse Reponse(FIR)

6.4.5.4 Frame/field prediction

Macroblock Adaptive Frame Field Coding(MBAFF)

6.4.6 Inter prediction examples

Rate Distortion Optimized(RDO)

6.4.7.2 'Classic' Group of Pictures structure

Group of Pictures(GOP)

6.5.1 Bounndary strength(bs)

## H.264 transform and coding

transform: converting a block of image samples into a different domain

quanntization: reducing the precision of transform coefficients

context adaptive variable length codes(CAVLC)

connext adaptive binary arithmetic coding(CABAC)

## H.264 conformance, transport and licensing

Supplemental Enhancement Information(SEI)

Video Usability Information(VUI)

8.2 Conforming to the Standard

The profile places algorithmic constraints on the decoder, determing which decoding tools the decoder should be capable of handling.

The level places data processing and storage constraints on the decoder, determining how much data the decoder should be capable of storing, procesing and outputting to a display.

8.6 Licensing H.264/AVC

Hypothetical Reference Decoder(HRD)

8.3.2 Arbitrary Slice Order(ASO)

8.3.3 Slice Groups/Flexible Macroblock Order(FMO)

8.4.2 Transport protocols

Packetized elementary stream(PES)

Real-Time Protocol(RTP)

8.5 Supplement Informtion

Supplement Enhancement Information(SEI)

Video Usability Information(VUI)

## H.264 performance

9.5.1 Rate Distortion Optimized mode selection

Rate Distortion Optimized(RDO)

Sum of Squared Distortion(SSD)

Sum of Absolute Differences(SAD)

Sum of Absolute Transformed Differences(SATD)

## Extensions and directions

10.1 Introduction

Scalable Video Coding(SVC)

Multiview Video Coding(MVC)

Reconfigurable Video Coding(RVC)

Fully Configurable Video Coding(FCVC)

10.2.9 Quality scalability in detail

Coarse Grain Quality Scalability(CGS)

Medium Grain Quality Scalability(MGS)

10.4.1 MPEG Reconfigurable Video Coding

Functional Units(FUs)

Video Tool Library(VTL)

10.4.2 Fully Configurable Video Coding(FCVC)

Universal Video Decoder(UVD)

