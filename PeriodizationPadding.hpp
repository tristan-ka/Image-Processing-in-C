/**
 * Performs the Periodization of the image.
 */

#ifndef PERIODIZATIONPADDING_HPP_
#define PERIODIZATIONPADDING_HPP_

#include<iostream>
#include"AbstractPadding.hpp"

class PeriodizationPadding : public AbstractPadding{
public :
	PeriodizationPadding();
	virtual~PeriodizationPadding();

	ImagePix<int> PerformPad(ImagePix<int> &in);
private :
};

#endif
