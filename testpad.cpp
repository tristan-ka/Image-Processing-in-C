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
	cout<< "Enter an image name to be padded"<<endl;
	cin>> filename;

	ImagePix<int> in=ImageRead(filename);
	int Nx=in.getNx();
	int Ny=in.getNy();
	ImagePix<int> pad1(2*Nx,2*Ny);
	ImagePix<int> pad2(2*Nx,2*Ny);
	ImagePix<int> pad3(2*Nx,2*Ny);

	AbstractPadding *pPadding=0;
	pPadding = new MirrorPadding;
	pad1=pPadding->PerformPad(in);

	pPadding = new PeriodizationPadding;
	pad2=pPadding->PerformPad(in);

	pPadding = new ZeroPadding;
	pad3=pPadding->PerformPad(in);

	ImageGenerator(pad1,"mirrorpad.png");
	ImageGenerator(pad2,"periopad.png");
	ImageGenerator(pad3,"zeropad.png");

}
