#include "ImageTools.hpp"


int isPowerOfTwo (unsigned int x)
{
 while (((x % 2) == 0) && x > 1) /* While x is even and > 1 */
   x /= 2;
 return (x == 1);
}

ImagePix<ComplexNumber> ConvertInt2Cplx(ImagePix<int>& in)
{
	int Nx=in.getNx();
	int Ny=in.getNy();
	ImagePix<ComplexNumber> out(Nx,Ny);
	for (int i=0;i<Nx;++i)
	{
		for (int j=0;j<Ny;++j)
		{
			out(i,j)=ComplexNumber(in(i,j));
		}
	}
	return out;
}

ImagePix<int> ConvertCplx2Int(ImagePix<ComplexNumber>& in)
{
	int Nx=in.getNx();
	int Ny=in.getNy();
	ImagePix<int> out(Nx,Ny);
	for (int i=0;i<Nx;++i)
	{
		for (int j=0;j<Ny;++j)
		{
			out(i,j)=in(i,j).GetRealPart();
		}
	}
	return out;
}

ImagePix<int> ConvertCplx2Mod(ImagePix<ComplexNumber>& in)
{
	int Nx=in.getNx();
	int Ny=in.getNy();
	ImagePix<double> out (Nx,Ny);
	for (int i=0;i<Nx;++i)
	{
		for (int j=0;j<Ny;++j)
		{
			out(i,j)=in(i,j).CalculateMagnitude();
		}
	}

	double max=out.getMax();
	double min=out.getMin();
	ImagePix<int> out2 (Nx,Ny);
	for (int i=0;i<Nx;++i)
	{
		for (int j=0;j<Ny;++j)
		{
			out2(i,j)=(double)((out(i,j)-min)/(max-min))*255*255;
		}
	}
	return out2;
}

ImagePix<int> ConvertCplx2Phas(ImagePix<ComplexNumber>& in)
{
	int Nx=in.getNx();
	int Ny=in.getNy();
	ImagePix<int> out (Nx,Ny);
	for (int i=0;i<Nx;++i)
	{
		for (int j=0;j<Ny;++j)
		{
			out(i,j)=in(i,j).CalculateArgument();
		}
	}
	return out;
}

void Swap(ImagePix<ComplexNumber> &in)
{
	int Nx=in.getNx();
	int Ny=in.getNy();
	ImagePix<ComplexNumber> tmp(Nx,Ny);
	for (int i=0;i<Nx/2;++i)
	{
		for(int j=0;j<Ny/2;++j)
		{
			tmp(i+Nx/2,j+Ny/2)=in(i,j);
			tmp(i,j)=in(i+Nx/2,j+Ny/2);
			tmp(i+Nx/2,j)=in(i,j+Ny/2);
			tmp(i,j+Ny/2)=in(i+Nx/2,j);
		}
	}
	in=tmp;
}

void filter(bool type ,double scale, ImagePix<ComplexNumber> & in)
{
	int Nx=in.getNx();
	int Ny=in.getNy();
	double scalex;
	double scaley;
	scalex=scale*Nx/2;
	scaley=scale*Ny/2;

	int originx =Nx/2;
	int originy =Ny/2;
	double facteur=0;
	for (int i=0;i<Nx;i++)
	{
		for (int j=0;j<Ny;j++)
		{
			if (type==true)
			{
				if (abs(i-originx)<scalex && abs(j-originy)<scaley)
				{
					in(i,j)=0;
				}
			}
			if (type==false)
			{
				if (abs(i-originx)>scalex || abs(j-originy)>scaley)
				{
					in(i,j)=0;
				}
			}
		}
	}
}

void histogram(ImagePix<int> &in)
{
	int Nx=in.getNx();
	int Ny=in.getNy();

	int hist[256];
	int pixvalue[256];
	for (int i=0;i<256;++i)
	{
		hist[i]=0;
		pixvalue[i]=i;
	}

	for(int i=0;i<Nx;++i)
	{
		for (int j=0;j<Ny;++j)
		{
			hist[in(i,j)]+=1;
		}
	}
	std::ofstream write_output("Histogram.dat");
	assert(write_output.is_open());
	for (int i=0;i<256;++i)
	{
		write_output <<pixvalue[i] << " " << hist[i]  << "\n";
	}
}

ImagePix<int> ImageRead(string filename)
{
	Image ImageIN(filename);

	int height = ImageIN.rows();
	int width = ImageIN.columns();
	int size = height * width;
	assert(isPowerOfTwo(height)==1 && "size of image is not a power of two");
	assert(isPowerOfTwo(width)==1 && "size of image is not a power of two");

	ImageIN.type( GrayscaleType );

	PixelPacket* pp = ImageIN.getPixels(0, 0, width, height);
	int PixelArray[size];
	unsigned char CharPixelArray[size];
	for (int i = 0; i < size; i++)
	{
		PixelArray[i] = (double) pp[i].red /65535.0f*255;
	}
	ImagePix<int> out(PixelArray,width,height);
	return out;
}

void ImageGenerator(ImagePix<int>& im, string filename){

	int width = im.getNx();
	int height= im.getNy();

	Image my_image(Geometry(width,height),Color("white"));

	Pixels my_pixel_cache(my_image);
	PixelPacket * my_pixels = my_pixel_cache.get(0,0,width,height);

	for (int j = 0 ; j < width ; ++j){
	   for (int i = 0 ; i < height ; ++i){
		 int color = MaxRGB * im(j,i)/255;
		 my_pixels[j+i*width] = Color(color,color,color,0);
	  }
	}
	my_pixel_cache.sync();
	my_image.write(filename);
}

