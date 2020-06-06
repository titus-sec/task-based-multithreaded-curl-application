#ifndef CURLCOUNTRY_H
#define CURLCOUNTRY_H

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <curl/curl.h>
#include "CountryUnit.h"
#include "task.h"

// Task that gets a country's name, the number of confirmed cases and the number of deaths in that country, and pushes it back to the passed std::vector<Country>
class curlCountry : public Task
{
public:
	curlCountry(std::string& available_countries, std::vector<Country>& vecOfCountries)
		: available_countries_(available_countries), vecOfCountries_(&vecOfCountries)
	{
	}

	~curlCountry()
	{
		delete vecOfCountries_;
	}

	void run();

private:
	const char* URL_START = "https://api.covid19api.com/live/country/"; // the base of the API URL for getting live cases for a country worldwide; getting country name, confirmed cases and number of deaths in that country
	std::string available_countries_; // std::vector of std::string, containing the list of available countries in the API
	std::vector<Country> * vecOfCountries_; // pointer to std::vector of struct Country, used for storing country name, confirmed casesand number of deaths in that country
	Country stored_country_; // temporary variable for storing data of a country
	static std::size_t write_data(char*, std::size_t, std::size_t, std::string*); // callback function used for passing data from the API
};

#endif