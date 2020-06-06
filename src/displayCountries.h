#ifndef DISPLAYCOUNTRIES_H
#define DISPLAYCOUNTRIES_H

#include <iostream>
#include <vector>
#include <string>
#include "task.h"
#include "CountryUnit.h"

// Task that displays the country's name, the number of confirmed cases and deaths in that country
class displayCountries : public Task
{
public:
	displayCountries(const std::vector<Country> & stored_countries)
		: stored_countries_(stored_countries)
	{
	}

	void run();

private:
	std::vector<Country> stored_countries_;
};

#endif