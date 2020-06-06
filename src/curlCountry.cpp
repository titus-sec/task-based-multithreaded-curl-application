#include "curlCountry.h"

std::size_t curlCountry::write_data(char* in, std::size_t size, std::size_t nmemb, std::string* out)
{
	std::size_t total_size = size * nmemb;
	if (total_size) // if contains data
	{
		out->append(in, total_size);
		return total_size;
	}
	else
	{
		std::cout << "Error. (callback function)\n";
		return 0;
	}
}
void curlCountry::run()
{
	CURL* handle = curl_easy_init(); // creating an easy handle for this session
	// important, a new handle must be created for each "easy" session, i.e. for each thread

	if (handle)
	{
		curl_easy_setopt(handle, CURLOPT_URL, (URL_START + available_countries_).c_str()); //setting URL property to transfer with CURLOP_URL
		
		curl_easy_setopt(handle, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4); // decreasing DNS resolution time by trying IPv4 only, resulting in decreased running time

		curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L); // follow HTPP redirects found in the HTTP 3xx response header if there are any

		// setting up variables for response data
		long httpCode(0); // long used for storing HTTP response code
		std::unique_ptr<std::string> httpData(new std::string()); // std::string smart pointer used for storing HTTP response data

		curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data); // pass all data to callback function write_data

		curl_easy_setopt(handle, CURLOPT_WRITEDATA, httpData.get()); // storing the data in httpData

		curl_easy_perform(handle); // connecting to the API and receiving the data

		curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &httpCode); // store the response data in httpCode

		if (httpCode == 200) // HTTP 200 OK, parse the received data
		{
			Json::Value jsonData; // used to store a JSON object
			Json::Reader jsonReader; // used to unserialize JSON into a Json::Value object

			if (jsonReader.parse(*httpData.get(), jsonData)) // received HTTP data parsing to Json::Value has succeeded, continue to proceed
			{
				if (jsonData[jsonData.size() - 1]["Country"]) // if there is information about the country
				{
					stored_country_.name = jsonData[jsonData.size() - 1]["Country"].asString(); // store the country name
					for (Json::Value::ArrayIndex i = 0; i != jsonData.size(); ++i) // iterate through the JSON object
					{
						stored_country_.confirmed += jsonData[i]["Confirmed"].asInt(); // sum and store the number of confirmed cases in the country
						stored_country_.deaths += jsonData[i]["Deaths"].asInt(); // sum and store the number of deaths in the country
					}
					vecOfCountries_->push_back(stored_country_); // push the Country data to a std::vector of Country
				}
			}
			else // parsing to Json::Value failed, display HTTP data which could be the root of the error
			{
				std::cout << "Could not parse HTTP data as JSON\n";
			}
		}

		else // failed, display HTTP response code
		{
			std::cout << "HTTP ERROR: " << httpCode << "\n";
		}

		curl_easy_cleanup(handle); // end the easy handle
	}
}