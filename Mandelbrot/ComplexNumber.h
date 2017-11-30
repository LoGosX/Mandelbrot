#pragma once

class ComplexNumber
{
public:
	ComplexNumber();
	ComplexNumber(double a, double b);
	~ComplexNumber();

	double a{ 0 }, b{ 0 };

	ComplexNumber operator + (const ComplexNumber& other) const;
	ComplexNumber operator * (const ComplexNumber& other) const;
	void square();
	ComplexNumber squared();
	float squaredAbs();
	float abs();
};

