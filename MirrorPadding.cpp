#include "MirrorPadding.hpp"

MirrorPadding::MirrorPadding()
{}

MirrorPadding::~MirrorPadding()
{}

ImagePix<int> MirrorPadding::PerformPad(ImagePix<int> & in)
{
	int nx = in.getNx();
	int ny = in.getNy();
	ImagePix<int> out(2*nx,2*ny);

	int k;
	int l;
	for (int i=-nx/2;i<nx+nx/2;++i)
	{
		for (int j=-ny/2;j<ny+ny/2;++j)
		{
			k=i;
			l=j;
			if(k<0)
			{
				k=-k;
			}
			if(l<0)
			{
				l=-l;
			}
			if(k>=nx)
			{
				k=nx-2-(k%(nx-2));
			}
			if(l>=ny)
			{
				l=ny-2-	(l%(ny-2));
			}
			out(i+nx/2,j+ny/2)=in(k,l);
		}
	}

	return out;
}
