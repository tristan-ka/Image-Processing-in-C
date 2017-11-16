/**
 * Performs the zero padding of the image.
 */

#ifndef ZEROPADDING_HPP_
#define ZEROPADDING_HPP_

#include<iostream>
#include"AbstractPadding.hpp"

class ZeroPadding : public AbstractPadding{
public :
	ZeroPadding();
	virtual~ZeroPadding();

ImagePix<int>PerformPad(ImagePix<int> &in);
private :
};

#endif
