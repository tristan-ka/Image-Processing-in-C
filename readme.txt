{\rtf1\ansi\ansicpg1252\cocoartf1404\cocoasubrtf130
{\fonttbl\f0\fnil\fcharset0 Monaco;}
{\colortbl;\red255\green255\blue255;\red0\green0\blue0;}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx560\tx1120\tx1680\tx2240\tx2800\tx3360\tx3920\tx4480\tx5040\tx5600\tx6160\tx6720\pardirnatural\partightenfactor0

\f0\fs22 \cf2 This project is compatible with Doxygen. For a clearer documentation, the user is invited to run Doxygen in the current directory.\
\
\pard\pardeftab720\partightenfactor0
\cf2 This program uses a restrictive algorithm to compute the FFT of an image and to \ul perform\ulnone  basic operation\
of image processing based on the Fourier domain.\
The program is linked and built using the \ul cmake\ulnone  method. In order to be able to use it, the user must have installed\
the \ul magick\ulnone ++ library from the ImageMagick API. The CmakeList.txt file is provided with all the source file. The user is invited\
to comment or \ul uncomment\ulnone  the lines corresponding to the OS on which he is using the program.\
\
All kind of image can be read. If they are in RGB format, they are automatically converted to \ul grayscale\ulnone .\
The gray levels are defined to start from 0 and go to 255, 0 being black and 255 being white.\
\
Three different types of padding are implemented :\
	- Mirror Folding\
	- Zero Padding\
	- \ul Periodization\ulnone \
\
Two types of filters are implemented :\
	- Noise removing (Low Pass Filter)\
	- Edge Detection (High Pass Filter)\
\
Restriction :\
	- Only \ul grayscale\ulnone  images are treated\
	- The input images can only be of size that are multiple of two\
	- The padding is always extending the size of the image by two\
	- The filters implemented are always centered at the origin. Hence no band cut or band pass can be performed\
\
The user has the following choice when running the main :\
	- The name of the input image on which the operations are going to be carried out.\
	- The type of Padding desired\
	- The type of Filtering desired\
	- The gain of the filter (must be between 0 and 1)\
\
The default output are :\
	- The histogram (contained in the file histogram.dat)\
	- The filtered image in the file named as desired\
	- The Phase and Magnitude of the image after and before filtering (contained in the files magnitude/phase_filtered.png and magnitude/phase_origin.png)}