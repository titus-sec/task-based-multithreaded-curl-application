/*
------------------------------------------------------------------------------------------------------
05/2020
Abertay University
CMP202 Data Structures and Algorithms 2
Author: Titas (Titus) Saunorius
Project "Task-based multithreaded cURL application for transferring COVID-19 Coronavirus statistics"
------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------
the documentation for using libcurl -- https://curl.haxx.se/libcurl/c/libcurl.html
the documentation for using JsonCpp -- https://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html
the API used for COVID-19 (Coronavirus) data for each country -- https://covid19api.com/
------------------------------------------------------------------------------------------------------
 */



#include "farm.h" // a class implementing task-based parallelisation collection of tasks that are ran in parallel
#include "task.h" // a base task class
#include "curlCountry.h" // implemented code of a task that gets a country's name, the number of confirmed cases and the number of deaths in that country, and pushes it back to the passed std::vector<Country>
#include "curlCountryList.h" // implemented code of a task that gets the slugs of available countries list in the API, and pushes it back to std::vector<std::string>
#include "sortCountries.h" // implemented code of a task that sorts the std::vector<Country> by the number of confirmed cases in decreasing order
#include "displayCountries.h"// implemented code of a task that displays the country's name, the number of confirmed cases and deaths in that country

int main()
{
	std::vector<std::string> available_countries; // std::vector of std::string used for listing the available countries' slugs which are used for requesting each country's data
	std::vector<Country> stored_countries; // std::vector of struct Country used for storing country name, confirmed cases and number of deaths in that country
	
	// queue and run tasks using farm
	Farm f; // Farm object f represents a collection of tasks to be performed
	std::cout << "Running task farm...\n--------------------\n\n";

	// running a task that gets a list of available countries in the API, used later for curlCountry()
	std::cout << "Curling list of countries...\n\n";
	f.add_task(new curlCountryList(available_countries)); // add the task to the farm
	f.run(); // perform the task in the farm

	// running a task that gets each available country data from the API
	std::cout << "Curling each country's data\n\n";
	for (int i = 0; i < available_countries.size(); ++i)
	{
		f.add_task(new curlCountry(available_countries[i], stored_countries)); // add the tasks to the farm
	}
	f.run(); // perform the tasks in the farm

	// running a task that sorts the updated vector of countries
	std::cout << "Sorting list of countries...\n\n";
	f.add_task(new sortCountries(stored_countries)); // add the task to the farm
	f.run(); // perform the task in the farm
	
	// running a task that displays the updated and sorted vector of countries
	std::cout << "displaying list of countries...\n";
	f.add_task(new displayCountries(stored_countries)); // add the task to the farm
	f.run(); // perform the task in the farm

	std::cout << "Tasks complete!\n";
	
	system("pause");
	return 0;
}