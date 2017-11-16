#ifndef COMPLEXNUMBERHEADERDEF
#define COMPLEXNUMBERHEADERDEF

#include <iostream>
/**
 The class ComplexNumber contains two private members the real part and the imaginary part of the complex number.
 It contains the basic algebra to perform all the operations desired for this project
 */
class ComplexNumber
{
private:
    double re;
    double im;
public:
    // Constructors
    ComplexNumber();
    ComplexNumber(double x, double y);
    ComplexNumber(const ComplexNumber& c);
    ComplexNumber(const double d);

    // Get methods
    double GetRealPart() const;
    double GetImaginaryPart() const;

    // Public methods
    double CalculateMagnitude() const;
    double CalculateArgument() const;
    ComplexNumber CalculatePower(double n) const;
    ComplexNumber CalculateConjugate() const;
    void SetConjugate();
    ComplexNumber ComplexFromPolar(double r, double theta_radians);

    // Operators
    ComplexNumber& operator=(const ComplexNumber& z);
    ComplexNumber operator-() const;
    ComplexNumber operator+(const ComplexNumber& z) const;
    ComplexNumber operator-(const ComplexNumber& z) const;
    ComplexNumber operator*(const double d) const;
    ComplexNumber operator/(const double d)const;
    ComplexNumber operator*(const ComplexNumber& z) const;
    bool operator>(const ComplexNumber& z) const;
    bool operator<(const ComplexNumber& z) const;

    // Friend functions
    friend std::ostream& operator<<(std::ostream& output,
    								const ComplexNumber& z);
    friend double RealPart(const ComplexNumber& z);
    friend double ImaginaryPart(const ComplexNumber& z);
};

#endif

