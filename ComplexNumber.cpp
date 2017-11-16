#include "ComplexNumber.hpp"

#include <cmath>

// Override default constructor
// Set real and imaginary parts to zero
ComplexNumber::ComplexNumber()
{
    re = 0.0;
    im = 0.0;
}

// Constructor that sets complex number z=x+iy
ComplexNumber::ComplexNumber(double x, double y)
{
    re = x;
    im = y;
}

// Copy constructor
ComplexNumber::ComplexNumber(const ComplexNumber& c)
	: re(c.GetRealPart()),
	  im(c.GetImaginaryPart())
{}

// Constructor for number with only real part
ComplexNumber::ComplexNumber(const double d)
	: re(d),
	  im(0.0)
{}

// Get methods

double ComplexNumber::GetRealPart() const {
	return re;
}

double ComplexNumber::GetImaginaryPart() const {
	return im;
}

// Method for computing the modulus of a
// complex number
double ComplexNumber::CalculateMagnitude() const
{
    return sqrt(re*re+
    im*im);
}

// Method for computing the argument of a
// complex number
double ComplexNumber::CalculateArgument() const
{
    return atan2(im, re);
}

// Method for raising complex number to the power n
// using De Moivre’s theorem - first complex
// number must be converted to polar form
ComplexNumber ComplexNumber::CalculatePower(double n) const
{
    double modulus = CalculateMagnitude();
    double argument = CalculateArgument();
    double mod_of_result = pow(modulus, n);
    double arg_of_result = argument*n;
    double real_part = mod_of_result*cos(arg_of_result);
    double imag_part = mod_of_result*sin(arg_of_result);
    ComplexNumber z(real_part, imag_part);

    return z;
}

// Computes the complex conjugate
ComplexNumber ComplexNumber::CalculateConjugate() const
{
	return ComplexNumber(re, -im);
}

void ComplexNumber::SetConjugate()
{
	im = - im;
}

ComplexNumber ComplexNumber::ComplexFromPolar(double r, double theta_radians){
    double real_part = r * cos(theta_radians);
    double imag_part = r * sin(theta_radians);
    ComplexNumber result(real_part,imag_part);
    return result;
};

// Overloading the = (assignment) operator
ComplexNumber& ComplexNumber::operator=(const ComplexNumber& z)
{
    re = z.re;
    im = z.im;
    return *this;
}

// Overloading the unary - operator
ComplexNumber ComplexNumber::operator-() const
{
    ComplexNumber w;
    w.re = -re;
    w.im = -im;
    return w;
}

// Overloading the binary + operator
ComplexNumber ComplexNumber::operator+(const ComplexNumber& z) const
{
    ComplexNumber w;
    w.re = re + z.re;
    w.im = im + z.im;
    return w;
}
bool ComplexNumber::operator>(const ComplexNumber& z) const
{
	double mag;
	mag=this->CalculateMagnitude();
	if (mag>z.CalculateMagnitude())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool ComplexNumber::operator<(const ComplexNumber& z) const
{
	double mag;
	mag=this->CalculateMagnitude();
	if (mag<z.CalculateMagnitude())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Overloading the binary - operator
ComplexNumber ComplexNumber::operator-(const ComplexNumber& z) const
{
    ComplexNumber w;
    w.re = re - z.re;
    w.im = im - z.im;
    return w;
}

ComplexNumber ComplexNumber::operator*(const double d) const
{
	ComplexNumber t(re * d, im * d);

	return t;
}
ComplexNumber ComplexNumber::operator/(const double d)const
{
	ComplexNumber t(re / d,im/d);
	return t;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber& z) const
{
	return ComplexNumber(re * z.GetRealPart()
						 - im * z.GetImaginaryPart(),
						 im * z.GetRealPart()
						 + re * z.GetImaginaryPart());
}

// Overloading the insertion << operator
std::ostream& operator<<(std::ostream& output, const ComplexNumber& z)
{
    // Format as "(a + bi)" or as "(a - bi)"
    output << "(" << z.re << " ";
    if (z.im >= 0.0)
    {
        output << "+ " << z.im << "i)";
    }
    else
    {
        // z.im < 0.0
        // Replace + with minus sign
        output << "- " << -z.im << "i)";
    }

    return output;
}

double RealPart(const ComplexNumber& z)
{
	return z.re;
}

double ImaginaryPart(const ComplexNumber& z)
{
	return z.im;
}
