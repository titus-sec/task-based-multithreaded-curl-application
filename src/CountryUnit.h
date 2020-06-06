#ifndef COUNTRYUNIT_H
#define COUNTRYUNIT_H

#include <string>

struct Country
{
	std::string name; // std::string storing the name of the country
	int confirmed = 0; // integer storing the number of confirmed cases in the country
	int deaths = 0; // integer storing the number of deaths in the country
};

#endif