/**
 Templated class to implement an image either of int or of ComplexNumber in the Fourrier domain
 It contains several constructor:
 	 - a default constructor
 	 - an empty constructor of the desired size
 	 - a constructor from the Pixelarray generated while reading an image
 	 (see the ImageTools.cpp file to know how images are read)
 */
#ifndef IMAGEPIXHEADERDEF
#define IMAGEPIXHEADERDEF

#include <iostream>
#include <assert.h>

template<typename pixel>class ImagePix
{
private :
	// Number of column
	int nx;
	// Number of row
	int ny;
	pixel ** mMatrix;

public :
    // Constructors
	ImagePix(){}
	ImagePix(int Nx, int Ny);
	ImagePix( int PixelArray[], int width, int height);
    // Destructor
    ~ImagePix();

    // Get
    int getNx() const;
    int getNy() const;

    pixel* getRow(int x);
    pixel* getColumn(int y);
    pixel getPixel(int x, int y)const;
    pixel getMax();
    pixel getMin();

    //Set
    void SetRow(pixel * row,int x);
    void SetColumn(pixel * column,int y);
    // Operators [][]

    pixel &operator()(int i, int j);
    ImagePix &operator=(const ImagePix& im);


};

// Empty constructor
template<typename pixel>
ImagePix<pixel>::ImagePix(int Nx, int Ny){
	nx=Nx;
	ny=Ny;
	assert (Nx>0 && "Nx must be a positive integer");
	assert (Ny>0 && "Ny must be a positive integer");
	mMatrix= new pixel*[Nx];
	for (int i=0;i<Nx;++i)
	{
		mMatrix[i]=new pixel[Ny];
		for (int j=0;j<Ny;++j)
		{
			mMatrix[i][j]=0;
		}
	}
}

// Constructor from ImageMagick input
template<typename pixel>ImagePix<pixel>::ImagePix( int PixelArray[], int width, int height)
{
	nx=width;
	ny=height;
//    	double mPix[nx][ny];
	mMatrix= new pixel*[nx];
	for (int i=0;i<nx;++i)
	{
		mMatrix[i]=new pixel[ny];
		for (int j=0;j<ny;++j)
		{
			mMatrix[i][j]=PixelArray[i+j*width];
		}
	}
}

// Destructor
template<typename pixel>ImagePix<pixel>::~ImagePix()
{
	for (int i = 0; i < nx; ++i) {
		delete[] mMatrix[i];
	}
	delete[] mMatrix;
}

// Get
template<typename pixel> int ImagePix<pixel>::getNx() const
{
	return nx;
}

template<typename pixel> int ImagePix<pixel>::getNy() const
{
	return ny;
}

template<typename pixel> pixel* ImagePix<pixel>::getRow(int x)
{
	pixel* row = new pixel[ny];
	for (int i=0;i<ny;++i)
	{
		row[i]=mMatrix[x][i];
	}
	return row;
}
template<typename pixel> pixel* ImagePix<pixel>::getColumn(int y)
{
	pixel*column= new pixel[nx];
	for (int i=0;i<nx;++i)
	{
		column[i]=mMatrix[i][y];
	}
	return column;

}

template<typename pixel> pixel ImagePix<pixel>::getMax()
{
pixel max = 0;
	for (int i=0; i<nx; ++i)
	{
		for (int j=0 ; j<ny ; ++j)
		{
			if (mMatrix[i][j]>max)
			{
				max=mMatrix[i][j];
			}
		}
	}
	return max;
}

template<typename pixel> pixel ImagePix<pixel>::getMin()
{
pixel min = 10000;
	for (int i=0; i<nx; ++i)
	{
		for (int j=0 ; j<ny ; ++j)
		{
			if (mMatrix[i][j]<min)
			{
				min=mMatrix[i][j];
			}
		}
	}
	return min;
}
//Set
template<typename pixel> void ImagePix<pixel>::SetRow(pixel * row, int x)
{
	for (int i=0;i<ny;++i)
	{
		mMatrix[x][i]=row[i];
	}
}
template<typename pixel> void ImagePix<pixel>::SetColumn(pixel * column, int y)
{
	for (int i=0;i<nx;++i)
	{
		mMatrix[i][y]=column[i];
	}
}

template<typename pixel> pixel ImagePix<pixel>::getPixel(int x,int y) const
{
	return mMatrix[x][y];
}

//Operator
template<typename pixel> pixel &ImagePix<pixel>::operator()(int i, int j)
{
	return mMatrix[i][j];
}

template<typename pixel> ImagePix<pixel>& ImagePix<pixel>::operator=(const ImagePix<pixel>& im)
{
	int Nx=im.getNx();
	int Ny=im.getNy();
	nx=Nx;
	ny=Ny;
	for (int i=0;i<Nx;++i)
	{
		for (int j=0;j<Ny;++j)
		{
			mMatrix[i][j]=im.getPixel(i,j);
		}
	}
	return *this;
}


#endif
