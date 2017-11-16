/*
 * Performs the unpadding of an image
 */

#ifndef UNPAD_HPP_
#define UNPAD_HPP_

#include<iostream>
#include"AbstractPadding.hpp"

class Unpad : public AbstractPadding{
public :
	Unpad();
	virtual~Unpad();

	ImagePix<int> PerformPad(ImagePix<int> &in);
	ImagePix<ComplexNumber> PerformPadCplx(ImagePix<ComplexNumber>&in);
private :
};

#endif
