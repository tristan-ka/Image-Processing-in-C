#include "Unpad.hpp"

Unpad::Unpad()
{}

Unpad::~Unpad()
{}

ImagePix<int> Unpad::PerformPad(ImagePix<int> &in)
{
	int nx = in.getNx();
	int ny = in.getNy();
	ImagePix<int> out(nx/2,ny/2);

	for (int i=0 ;i<nx/2; ++i)
	{
		for (int j=0;j<ny/2;++j)
		{
			out(i,j)=in(i+nx/4,j+ny/4);
		}
	}
	return out;
}

ImagePix<ComplexNumber> Unpad::PerformPadCplx(ImagePix<ComplexNumber>&in)
{
	int nx = in.getNx();
	int ny = in.getNy();
	ImagePix<ComplexNumber> out(nx/2,ny/2);

	for (int i=0 ;i<nx/2; ++i)
	{
		for (int j=0;j<ny/2;++j)
		{
			out(i,j)=in(i+nx/4,j+ny/4);
		}
	}
	return out;
}
