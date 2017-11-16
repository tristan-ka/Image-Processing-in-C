#include "PeriodizationPadding.hpp"

PeriodizationPadding::PeriodizationPadding()
{}

PeriodizationPadding::~PeriodizationPadding()
{}

ImagePix<int> PeriodizationPadding::PerformPad(ImagePix<int> &in)
{
	int nx = in.getNx();
	int ny = in.getNy();
	ImagePix<int> out(2*nx,2*ny);

	for (int i=0;i<2*nx;++i)
	{
		for (int j=0;j<2*ny;++j)
		{
			out(i,j)=in((nx/2+i)%nx,(ny/2+j)%ny);
		}
	}
	return out;
}
