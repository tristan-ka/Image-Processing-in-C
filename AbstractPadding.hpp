
#ifndef ABSTRACTPADDING_HPP_
#define ABSTRACTPADDING_HPP_

#include<iostream>
#include"ImagePix.hpp"
#include<string>
#include "ImageTools.hpp"
#include "ComplexNumber.hpp"

using namespace std;
/**
Abstract class to perform different kind of padding and also to perform the unpading operation.
The width and height of the images are allways extended by two so that the 2raddix fft algorithm
can still be performed once the image is padded.
 */
class AbstractPadding{

public :
	//Constructor and destructor
	AbstractPadding();
	virtual ~AbstractPadding();

	// Virutal function
	virtual ImagePix<int> PerformPad(ImagePix<int> &in)=0;
};

#endif


