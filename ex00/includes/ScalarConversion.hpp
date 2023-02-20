#pragma once
#ifndef SCALARCONVERSION_HPP
#define SCALARCONVERSION_HPP

#include <string>

enum type_e
{
	NAN,
	NAN_F,
	MINUS_INF_F,
	MAXIM_INF_F,
	MINUS_INF,
	MAXIM_INF,
	CHAR,
	INT,
	FLOAT,
	DOUBLE
};

class ScalarConversion
{
public:
	ScalarConversion();
	~ScalarConversion();
	ScalarConversion(const ScalarConversion &oth);
	ScalarConversion &operator=(const ScalarConversion &oth);
	ScalarConversion(const std::string &input);
	void convert() const;
private:
	void convertFromChar(char c) const;
	void convertFromInt(int i) const;
	void convertFromFloat(float f) const;
	void convertFromDouble(double d) const;
	std::string _input;
	long _value;
	type_e _type;

    bool isChar(const std::string &basicString);

    bool isInt(const std::string &basicString);

    bool isFloat(const std::string &basicString);

    bool isDouble(const std::string &basicString);
};

#endif
