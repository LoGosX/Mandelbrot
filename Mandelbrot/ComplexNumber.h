#pragma once
class ComplexNumber
{
public:
	ComplexNumber();
	ComplexNumber(float a, float b);
	~ComplexNumber();

	float a{ 0 }, b{ 0 };

	ComplexNumber operator + (const ComplexNumber& other) const;
	ComplexNumber operator * (const ComplexNumber& other) const;
	void square();
	ComplexNumber squared();
	float squaredAbs();
};

