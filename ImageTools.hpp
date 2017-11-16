#ifndef IMAGETOOLS_HPP_
#define IMAGETOOLS_HPP_
#include <cmath>
#include "ImagePix.hpp"
#include "ComplexNumber.hpp"
#include <Magick++.h>
#include <fstream>
#include <assert.h>

using namespace std;
using namespace Magick;
/**
 The Image tools package contains several functions :
 */
int isPowerOfTwo (unsigned int x);
void ImageGenerator(ImagePix<int> & im, string filename);
ImagePix<int> ImageRead(string filename);
ImagePix<ComplexNumber> ConvertInt2Cplx(ImagePix<int>& in);
ImagePix<int> ConvertCplx2Int(ImagePix<ComplexNumber>& in);
ImagePix<int> ConvertCplx2Mod(ImagePix<ComplexNumber>& in);
ImagePix<int> ConvertCplx2Phas(ImagePix<ComplexNumber>& in);
void Swap(ImagePix<ComplexNumber> &in);
void filter(bool type,double scale, ImagePix<ComplexNumber> & in);
void histogram(ImagePix<int> &in);

#endif
