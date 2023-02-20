#include "ScalarConversion.hpp"
#include <stdexcept>
#include <iostream>

int main(int ac, char **av)
{
	if (ac != 2)
		return 0;
    try
    {
        ScalarConversion scalarConversion(av[1]);
        scalarConversion.convert();
    } catch (std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
	return 0;
}