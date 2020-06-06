#include "sortCountries.h"

void sortCountries::run()
{
	std::sort(stored_countries_->begin(), stored_countries_->end(),
		// lambda expression begins
		[](const Country& a, const Country& b) {
		return a.confirmed > b.confirmed;
	});// end of lambda expression
}