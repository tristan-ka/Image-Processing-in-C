#include <iostream>
#include <cmath>
#include "ComplexNumber.hpp"
#include "ImagePix.hpp"
#include "FFTPix.hpp"

using namespace std;

#define PI  3.1415926535897932


int main(int argc, char* argv[])
{

	//Test on 2D signal
	ImagePix<int> a(4,2);
	for (int i=0;i<4;++i)
	{
		for(int j=0; j<2;++j)
		{
			a(i,j)=(i+1)*(j+1);
			cout << a(i,j)<<" ";
		}
		cout << endl;
	}
	cout <<endl;


	FFTPix fft(a,"zero");
	ImagePix<ComplexNumber> b= fft.getFourier();
	for (int i=0;i<8;++i)
	{
		for(int j=0; j<4;++j)
		{
			cout << b(i,j)<< " ";
		}
		cout <<endl;
	}
	cout << endl;

	FFTPix ifft(b);
	ImagePix<int> c=ifft.getSpace();

	for (int i=0;i<4;++i)
	{
		for(int j=0; j<2;++j)
		{
			cout << (double)c(i,j)/255*8<< " ";
		}
		cout <<endl;
	}

	// The output is compared to the answer given by the function FFT2 in matlab. They match.
	// The scaling introduced in the inverse FFT to put back the value of the pixel between 0 and 255 introduce
	// small errors of rounding when going back to the space domain but the sequence returned is almost the
	// the same as the initial one.
return 0;
}

