#include "ComplexNumber.h"



ComplexNumber::ComplexNumber()
{
}

ComplexNumber::ComplexNumber(float a, float b) : a(a), b(b)
{
}


ComplexNumber::~ComplexNumber()
{
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber & other) const
{
	return ComplexNumber(this->a + other.a, this->b + other.b);
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber & other) const
{
	//(a + bi)(c + di) = ac + adi + bci - bd = ac - bd + (ad + bc)i
	return ComplexNumber(this->a * other.b - this->b * other.b, this->a * other.b + this->b * other.a);
}

void ComplexNumber::square()
{
	*this = this->squared();
}

ComplexNumber ComplexNumber::squared()
{
	//(a+bi)^2 = a^2 + 2abi - b^2 = a^2 - b^2 + 2abi
	return ComplexNumber(this->a * this->a - this->b * this->b, 2 * this->a*this->b);
}

float ComplexNumber::squaredAbs()
{
	return this->a * this->a + this->b * this->b;
}
