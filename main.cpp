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

/**
\mainpage Short Description of the Program
\author Tristan Karch

This program uses a restrictive algorithm to compute the FFT of an image and to perfrom basic operation
of image processing based on the Fourier domain.
The program is linked and built using the cmake method. In order to be able to use it, the user must have installed
the magick++ library from the ImageMagick API. The CmakeList.txt file is provided with all the source file. The user is invited
to comment or uncomment the lines corresponding to the OS on which he is using the program.

All kind of image can be read. If they are in RGB format, they are automatically converted to grayscale.
The gray levels are defined to start from 0 and go to 255, 0 being black and 255 being white.

Three different types of padding are implemented :
	- Mirror Folding
	- Zero Padding
	- Periodization

Two types of filters are implemented :
	- Noise removing (Low Pass Filter)
	- Edge Detection (High Pass Filter)

Restriction :
	- Only grayscale images are treated
	- The input images can only be of size that are multiple of two
	- The padding is always extending the size of the image by two
	- The filters implemented are always centered at the origin. Hence no band cut or band pass can be performed

The user has the following choice when running the main :
	- The name of the input image on which the operations are going to be carried out.
	- The type of Padding desired
	- The type of Filtering desired
	- The gain of the filter (must be between 0 and 1)

The default output are :
	- The histogram (contained in the file histogram.dat)
	- The filtered image in the file named as desired
	- The Phase and Magnitude of the image after and before filtering (contained in the files magnitude/phase_filtered.png and magnitude/phase_origin.png)
 
 Note to the professor : I have built my project on my mac and everything is compiling fine with cmake. I hope that the note that I have put in the CMakeLists.txt
 also work on the Linux platform.

 */
InitializeMagick(*argv);

// User Interface
string input_name;
string output_name;
string pad;
bool filter_type;
double filter_gain;
cout<< "Enter name of the input image"<<endl;
cin >> input_name;
cout <<"Enter type of padding"<< endl <<"Padding type are :"<<endl << "mirror ; zero ; periodization"<<endl;
cin >> pad;
cout <<"Enter type of filter "<<endl << "- 0 for Low pass filter" <<endl<< "- 1 for High pass filter"<<endl;
cin>>filter_type;
cout <<"Enter filter gain"<< endl << "Gain must be between 0 and 1" << endl << "0.1 is a good tuning"<<endl;
cin>>filter_gain;
cout <<"Enter name of the output image"<<endl;
cin>>output_name;

// Core of Main
ImagePix<int> input=ImageRead(input_name);

histogram(input);

FFTPix fft_im(input,pad);

ImagePix<ComplexNumber> fft_im_extracted=fft_im.getFourier();
ImagePix<int> lili=fft_im.getSpace();
ImagePix<int> magnitude_origin =ConvertCplx2Mod(fft_im_extracted);
ImagePix<int> phase_origin= ConvertCplx2Phas(fft_im_extracted);

filter(filter_type,filter_gain,fft_im_extracted);

ImagePix<int> magnitude_filtered =ConvertCplx2Mod(fft_im_extracted);
ImagePix<int> phase_filtered= ConvertCplx2Phas(fft_im_extracted);


FFTPix inverse(fft_im_extracted);
ImagePix<int>output=inverse.getSpace();

ImageGenerator(phase_origin,"phase_origin.png");
ImageGenerator(magnitude_origin,"magnitude_origin.png");

ImageGenerator(output,output_name);
ImageGenerator(phase_filtered,"phase_filtered.png");
ImageGenerator(magnitude_filtered,"magnitude_filtered.png");

}
