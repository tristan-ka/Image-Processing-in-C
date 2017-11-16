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
	string filename;
	cout<< "Enter an image name to compute its histogram"<<endl;
	cin>> filename;

	ImagePix<int> in=ImageRead(filename);
	histogram(in);
}
