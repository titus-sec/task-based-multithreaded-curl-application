#ifndef SORTCOUNTRIES_H
#define SORTCOUNTRIES_H

#include <vector>
#include <string>
#include <algorithm>
#include "task.h"
#include "CountryUnit.h"
// Task that sorts the std::vector<Country> by the number of confirmed cases in decreasing order
class sortCountries : public Task
{
public:
	sortCountries(std::vector<Country>& stored_countries)
		: stored_countries_(&stored_countries)
	{
	}

	~sortCountries()
	{
		delete stored_countries_;
	}

	void run();

private:
	std::vector<Country>* stored_countries_;
};

#endif