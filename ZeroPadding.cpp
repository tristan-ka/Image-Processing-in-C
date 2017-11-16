#include "ZeroPadding.hpp"

ZeroPadding::ZeroPadding()
{}

ZeroPadding::~ZeroPadding()
{}

ImagePix<int> ZeroPadding::PerformPad(ImagePix<int> &in)
{

	int nx = in.getNx();
	int ny = in.getNy();

	ImagePix<int> out(2*nx,2*ny);

	for (int i=0;i<2*nx;++i)
	{
		for (int j=0;j<2*ny ;++j)
		{
			if(i<nx || j<ny)
			{
				out(i,j)=0;
			}
			else
			{
				out(i-nx/2,j-ny/2)=in(i-nx,j-ny);
			}
		}
	}

	return out;
}
