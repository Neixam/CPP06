#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <iomanip>
#include "ScalarConversion.hpp"

void output(const std::string &charVal, const std::string &intVal, const std::string &floatVal, const std::string &doubleVal)
{
	std::cout << "char: " << charVal << std::endl;
	std::cout << "int: " << intVal << std::endl;
	std::cout << "float: " << floatVal << std::endl;
	std::cout << "double: " << doubleVal << std::endl;
}

ScalarConversion::ScalarConversion() : _input("")
{
}

ScalarConversion::~ScalarConversion()
{

}

ScalarConversion::ScalarConversion(const ScalarConversion &oth) : _input(oth._input)
{}

ScalarConversion &ScalarConversion::operator=(const ScalarConversion &oth)
{
	if (this == &oth)
		return *this;
	_input = oth._input;
	return *this;
}

ScalarConversion::ScalarConversion(const std::string &input) : _input(input)
{
    static const std::string species[6] =
            {
            "nan", "nanf", "-inff", "+inff", "-inf", "+inf"
            };

	if (_input.empty())
		throw std::invalid_argument("empty string");
    if (isChar(_input))
    {
        _type = CHAR;
        _value = static_cast<long>(_input[0]);
    }
    else if (isInt(_input))
    {
        _type = INT;
        _value = std::strtol(_input.c_str(), NULL, 10);
        if (INT_MAX < _value || INT_MIN > _value)
            throw std::invalid_argument("overflow");
    }
    else if (isFloat(_input))
    {
        _type = FLOAT;
        float tmp = std::strtof(_input.c_str(), NULL);
        _value = *reinterpret_cast<long*>(&tmp);
    }
    else if(isDouble(_input))
    {
        _type = DOUBLE;
        double tmp = std::strtod(_input.c_str(), NULL);
        _value = *reinterpret_cast<long*>(&tmp);
    }
    else
    {
        for (int specie = NAN; specie < CHAR; specie++)
        {
            if (species[specie] == _input)
            {
                _type = static_cast<type_e>(specie);
                return;
            }
        }
        throw std::invalid_argument("no conversion for this argument");
    }
}

void ScalarConversion::convert() const
{
	static const struct
	{
		std::string charVal;
		std::string intVal;
		std::string floatVal;
		std::string doubleVal;
	} convertTab[6] =
			{
				{ "impossible", "impossible", "nanf", "nan" },
				{ "impossible", "impossible", "nanf", "nan" },
				{ "impossible", "impossible", "-inff", "-inf" },
				{ "impossible", "impossible", "+inff", "+inf" },
				{ "impossible", "impossible", "-inff", "-inf" },
				{ "impossible", "impossible", "+inff", "+inf" }
			};

	switch (_type)
	{
		case NAN:
			/* fall thought */
		case NAN_F:
			/* fall thought */
		case MINUS_INF_F:
			/* fall thought */
		case MAXIM_INF_F:
			/* fall thought */
		case MINUS_INF:
			/* fall thought */
		case MAXIM_INF:
			output(convertTab[_type].charVal, convertTab[_type].intVal,
				   convertTab[_type].floatVal, convertTab[_type].doubleVal);
			break;
		case CHAR:
			convertFromChar(static_cast<char>(_value));
			break;
		case INT:
			convertFromInt(static_cast<int>(_value));
			break;
		case FLOAT:
			convertFromFloat(*reinterpret_cast<const float*>(&_value));
			break;
		case DOUBLE:
			convertFromDouble(*reinterpret_cast<const double*>(&_value));
			break;
	}
}

void ScalarConversion::convertFromChar(char c) const
{
    std::stringstream ssChar;
	std::stringstream ssInt;
	std::stringstream ssFloat;
	std::stringstream ssDouble;

    ssChar << c;
	ssInt << static_cast<int>(c);
	ssFloat << static_cast<float>(c) << ".0f";
	ssDouble << static_cast<double>(c) << ".0";
	if (std::isprint(c))
		return output("'" + ssChar.str() + "'", ssInt.str(), ssFloat.str(), ssDouble.str());
	output("Non displayable", ssInt.str(), ssFloat.str(), ssDouble.str());
}

void ScalarConversion::convertFromInt(int i) const
{
	std::stringstream ssInt;
	std::stringstream ssFloat;
	std::stringstream ssDouble;

	ssInt << i;
	ssFloat << static_cast<float>(i) << ".0f";
	ssDouble << static_cast<double>(i) << ".0";
	if (isascii(i))
	{
		std::stringstream ssChar;

		ssChar << static_cast<char>(i);
		if (std::isprint(i))
			return output("'" + ssChar.str() + "'", ssInt.str(), ssFloat.str(), ssDouble.str());
		return output("Non displayable", ssInt.str(), ssFloat.str(), ssDouble.str());
	}
	return output("impossible", ssInt.str(), ssFloat.str(), ssDouble.str());
}

void ScalarConversion::convertFromFloat(float f) const
{
	std::stringstream ssInt;
	std::stringstream ssFloat;
	std::stringstream ssDouble;

	ssInt << static_cast<int>(f);
	ssFloat << f << "f";
	ssDouble << static_cast<double>(f);
	if (isascii(static_cast<int>(f)))
	{
		std::stringstream ssChar;

		ssChar << static_cast<char>(f);
		if (std::isprint(static_cast<int>(f)))
			return output("'" + ssChar.str() + "'", ssInt.str(), ssFloat.str(), ssDouble.str());
		return output("Non displayable", ssInt.str(), ssFloat.str(), ssDouble.str());
	}
	return output("impossible", ssInt.str(), ssFloat.str(), ssDouble.str());
}

void ScalarConversion::convertFromDouble(double d) const
{
	std::stringstream ssInt;
	std::stringstream ssFloat;
	std::stringstream ssDouble;

	ssInt << static_cast<int>(d);
	ssFloat << static_cast<float>(d) << "f";
	ssDouble << d;
	if (isascii(static_cast<int>(d)))
	{
		std::stringstream ssChar;

		ssChar << static_cast<char>(d);
		if (std::isprint(static_cast<int>(d)))
			return output("'" + ssChar.str() + "'", ssInt.str(), ssFloat.str(), ssDouble.str());
		return output("Non displayable", ssInt.str(), ssFloat.str(), ssDouble.str());
	}
	return output("impossible", ssInt.str(), ssFloat.str(), ssDouble.str());
}

bool ScalarConversion::isChar(const std::string &basicString)
{
    if (basicString.size() != 1)
        return false;
    return isascii(basicString[0]) && !std::isdigit(basicString[0]);
}

bool ScalarConversion::isInt(const std::string &basicString)
{
    bool ret = false;

    for (size_t i = (basicString[0] == '-' || basicString[0] == '+') ? 1 : 0; i < basicString.size(); ++i)
    {
        ret = true;
        if (!std::isdigit(basicString[i]))
            return false;
    }
    return ret;
}

bool ScalarConversion::isFloat(const std::string &basicString)
{
    return basicString[basicString.size() - 1] == 'f'
        && isDouble(basicString.substr(0, basicString.size() - 1));
}

bool ScalarConversion::isDouble(const std::string &basicString)
{
    bool ret = false;
    size_t i;

    for (i = (basicString[0] == '-' || basicString[0] == '+') ? 1 : 0; i < basicString.size(); ++i)
    {
        if (basicString[i] == '.')
        {
            ++i;
            break;
        }
        ret = true;
        if (!std::isdigit(basicString[i]))
            return false;
    }
    if (!ret)
        return false;
    ret = false;
    for (; i < basicString.size(); ++i)
    {
        ret = true;
        if (!std::isdigit(basicString[i]))
            return false;
    }
    return ret;
}
