#include "displayCountries.h"

void displayCountries::run()
{
	for (auto& country : stored_countries_)
	{
		std::cout << "\n";
		std::cout << "------------------------------------" << "\n";
		std::cout << "[COUNTRY]: " << country.name << "\n";
		std::cout << "[CONFIRMED CASES]: " << country.confirmed << "\n";
		std::cout << "[DEATHS]: " << country.deaths << "\n";
		std::cout << "------------------------------------" << "\n";
		std::cout << "\n";
	}
}