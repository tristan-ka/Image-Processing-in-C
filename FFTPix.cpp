#include "FFTPix.hpp"

#define PI  3.1415926535897932

FFTPix::FFTPix(ImagePix<int> &in , std::string padtype)
{
	int Nx=in.getNx();
	int Ny=in.getNy();

	mspace_image = new ImagePix<int>(Nx,Ny);
	*mspace_image=in;
	mfourier_image= new ImagePix<ComplexNumber>(2*Nx,2*Ny);
	ImagePix<int> inpad(2*Nx,2*Ny);
	AbstractPadding* pPadding=0;
	if (padtype=="mirror")
	{
		pPadding = new MirrorPadding;
		inpad= pPadding->PerformPad(in);
	}
	else if (padtype=="zero")
	{
		pPadding = new ZeroPadding;
		inpad= pPadding->PerformPad(in);
	}
	else if (padtype=="periodization")
	{
		pPadding = new PeriodizationPadding;
		inpad= pPadding->PerformPad(in);
	}
	else
	{
		std::cerr<<std::endl<<"ERROR :Type of Padding not recognized"<<std::endl<<"Type are : mirror, zero or periodization"<<std::endl;
	}
	assert(padtype =="mirror" || padtype=="periodization" || padtype=="zero");

	ImagePix<ComplexNumber>inpadcomplex(2*Nx,2*Ny);
	inpadcomplex=ConvertInt2Cplx(inpad);
	*mfourier_image=FFT2(inpadcomplex);
	Swap(*mfourier_image);
}


FFTPix::FFTPix(ImagePix<ComplexNumber> &in)
{
	int Nx=in.getNx();
	int Ny=in.getNy();
	mspace_image = new ImagePix<int>(Nx/2,Ny/2);
	mfourier_image= new ImagePix<ComplexNumber>(Nx,Ny);
	*mfourier_image=in;
	Swap(*mfourier_image);

	ImagePix<ComplexNumber> spacepad=iFFT2(*mfourier_image);
	ImagePix<int> spacepadint=ConvertCplx2Int(spacepad);

	int max=spacepadint.getMax();
	int min=spacepadint.getMin();
// Rescaling for ImageMagick generation of image : the value of the pixel must be between 0 and 255
	for (int i=0;i<Nx;++i)
	{
		for (int j=0;j<Ny;++j)
		{
			spacepadint(i,j)=(double)(spacepadint(i,j)-min)/(max-min)*255;
		}
	}
	AbstractPadding* pPadding=0;
	pPadding = new Unpad;
	*mspace_image=pPadding->PerformPad(spacepadint);
}

ImagePix<int> FFTPix::getSpace()
{
	ImagePix<int> out(mspace_image->getNx(),mspace_image->getNy());
	out=*mspace_image;
	return out;
}
ImagePix<ComplexNumber> FFTPix::getFourier()
{
	ImagePix<ComplexNumber> out(mfourier_image->getNx(),mfourier_image->getNy());
	out=*mfourier_image;
	return out;
}

ComplexNumber * FFTPix::FFT(ComplexNumber * x , int N, bool inverse)
{

	// Allocating memory for the output
	ComplexNumber* X = new ComplexNumber[N];

	// Allocating memory for the sub vectors
	    ComplexNumber*d;
	    ComplexNumber*e;
	    ComplexNumber*D;
	    ComplexNumber*E;

	    int k=0;

	    if (N == 1) {
	        X[0] = x[0];
	        return X;
	    }

	    e = new ComplexNumber[N/2];
	    d = new ComplexNumber[N/2];
	    for(k = 0; k < N/2; k++) {
	        e[k] = x[2*k];
	        d[k] = x[2*k + 1];

	    }

	    E = FFT(e, N/2,inverse);
	    D = FFT(d, N/2,inverse);


	    ComplexNumber twiddle;
	    for(k = 0; k < N/2; k++) {
	        /* Multiply entries of D by the twiddle factors e^(-2*pi*i/N * k) */
	    	if (inverse==true)
	    	{
	    	twiddle=twiddle.ComplexFromPolar(1, 2.0*PI*k/N);
	    	}
	    	else
	    	{
	    		twiddle=twiddle.ComplexFromPolar(1, -2.0*PI*k/N);
	    	}
	        D[k] = twiddle*D[k];
	    }

	    for(k = 0; k < N/2; k++) {
	        X[k]       = E[k]+D[k];
	        X[k + N/2] = E[k]- D[k];
	    }

	    free(D);
	    free(E);
	    return X;
}

ComplexNumber * FFTPix::iFFT(ComplexNumber * x , int N){
	ComplexNumber* X = new ComplexNumber[N];
	X=FFT(x,N,true);
	for (int i=0;i<N;++i)
		X[i]=X[i]/N;
	return X;
}

ImagePix<ComplexNumber> FFTPix::FFT2(ImagePix<ComplexNumber> &in)
{
	int Nx=in.getNx();
	int Ny=in.getNy();
	ImagePix<ComplexNumber> out (Nx,Ny);
	ComplexNumber *row = new ComplexNumber[Ny];
	ComplexNumber*ROW = new ComplexNumber[Ny];
	for (int i=0;i<Nx;++i)
	{
		row=in.getRow(i);
		ROW=FFT(row,Ny);
		out.SetRow(ROW,i);
	}
	delete row;
	delete ROW;

	ComplexNumber *column = new ComplexNumber[Nx];
	ComplexNumber*COLUMN = new ComplexNumber[Nx];
	for (int j=0;j<Ny	;++j)
	{
		column=out.getColumn(j);
		COLUMN=FFT(column,Nx);
		out.SetColumn(COLUMN,j);
	}
	delete column;
	delete COLUMN;
return out;
}

ImagePix<ComplexNumber> FFTPix::iFFT2(ImagePix<ComplexNumber> &in)
{
	int Nx=in.getNx();
	int Ny=in.getNy();
	ImagePix<ComplexNumber> out (Nx,Ny);
	ComplexNumber *row = new ComplexNumber[Ny];
	ComplexNumber*ROW = new ComplexNumber[Ny];
	for (int i=0;i<Nx;++i)
	{
		row=in.getRow(i);
		ROW=iFFT(row,Ny);
		out.SetRow(ROW,i);
	}
	delete row;
	delete ROW;

	ComplexNumber *column = new ComplexNumber[Nx];
	ComplexNumber*COLUMN = new ComplexNumber[Nx];
	for (int j=0;j<Ny	;++j)
	{
		column=out.getColumn(j);
		COLUMN=iFFT(column,Nx);
		out.SetColumn(COLUMN,j);
	}
	delete column;
	delete COLUMN;
return out;
}

