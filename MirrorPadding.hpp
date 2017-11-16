/**
 * Performs the Mirror folding of the image.
 */

#ifndef MIRRORPADDING_HPP_
#define MIRRORPADDING_HPP_

#include <iostream>
#include "AbstractPadding.hpp"

class MirrorPadding :public AbstractPadding{
public :
	MirrorPadding();
	virtual~MirrorPadding();

	ImagePix<int> PerformPad(ImagePix<int> &in);
private:
};

#endif
