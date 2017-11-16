#ifndef FFTPIX_HPP_
#define FFTPIX_HPP_

#include "ComplexNumber.hpp"
#include "ImagePix.hpp"
#include <string>

#include "ImagePix.hpp"
#include "ComplexNumber.hpp"
#include "AbstractPadding.hpp"
#include "ZeroPadding.hpp"
#include "PeriodizationPadding.hpp"
#include "MirrorPadding.hpp"
#include "Unpad.hpp"
#include "ImageTools.hpp"
/**
 Class that contains two private members :
 - mspace_image is a pointer on the object ImagePix<int>.It contains the information of the image in the space domain
 - mfourier_image is a pointer on the object ImagePix<ComplexNumber>. It contains the information of the image in the Fourier domain

 The constructor computes directly the fourier transform and the inverse fourier transform depending on the input arguments.
 The methods are only used to compute the FFT and the inverse FFT and to access the different object pointed by both pointers.
 */
class FFTPix{
private :
	ImagePix<int>* mspace_image;
	ImagePix<ComplexNumber>* mfourier_image;
public :
	//constructor
	FFTPix(ImagePix<int> &in, std::string);
	FFTPix(ImagePix<ComplexNumber> &in);

	// FFT methods
	/**
	 \param the bool parameter here is only used for the implementation of the inverse FFT. It should not be modified by the user.
	 */
	ComplexNumber* FFT(ComplexNumber* x, int N,bool inverse=false);
	ComplexNumber * iFFT(ComplexNumber * x , int N);
	ImagePix<ComplexNumber> FFT2(ImagePix<ComplexNumber> &in);
	ImagePix<ComplexNumber> iFFT2(ImagePix<ComplexNumber> &in);

	// Get method

	ImagePix<int> getSpace();
	ImagePix<ComplexNumber> getFourier();
};
#endif
