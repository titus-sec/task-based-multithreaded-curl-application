#ifndef CURLCOUNTRYLIST_H
#define CURLCOUNTRYLIST_H

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

// Task that gets the slugs of available countries list in the API, and pushes it back to std::vector<std::string>
// The available countries slug is used for each country request
// This task must be run before curlCountry task
class curlCountryList : public Task
{
public:
	curlCountryList(std::vector<std::string>& available_countries)
		: available_countries_(&available_countries)
	{
	}

	~curlCountryList()
	{
		delete available_countries_;
	}

	void run();

private:
	const char* URL_FOR_AVAILABLE_COUNTRIES_DATA = "https://api.covid19api.com/countries"; // the API URL for getting all the available countries and the country slug for per country requests
	
	std::vector<std::string> * available_countries_; // pointer to std::vector of std::string, used for storing the list of available countries' slugs in the API
	static std::size_t write_data(char*, std::size_t, std::size_t, std::string*); // callback function used for passing data from the API
};

#endif