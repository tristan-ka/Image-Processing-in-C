#include "ComplexNumber.hpp"
#include "ImagePix.hpp"

#include <Magick++.h>
#include <iostream>
#include <cmath>
#include <string>
#include "AbstractPadding.hpp"
#include "ZeroPadding.hpp"
#include "PeriodizationPadding.hpp"
#include "MirrorPadding.hpp"
#include "Unpad.hpp"
#include "ImageTools.hpp"
#include "FFTPix.hpp"

using namespace std;


int main(int argc, char* argv[])
{
	ImagePix<int> input=ImageRead("lena_color.gif");

	histogram(input);

	FFTPix fft_im(input,"mirror");

	ImagePix<ComplexNumber> fft_im_extracted=fft_im.getFourier();
	ImagePix<int> lili=fft_im.getSpace();

	filter(true,0.1,fft_im_extracted);

	FFTPix inverse(fft_im_extracted);
	ImagePix<int>output=inverse.getSpace();


	ImageGenerator(output,"lena_edge.gif");

}
