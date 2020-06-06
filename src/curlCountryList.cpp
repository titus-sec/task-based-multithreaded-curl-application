#include "curlCountryList.h"

std::size_t curlCountryList::write_data(char* in, std::size_t size, std::size_t nmemb, std::string* out)
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
void curlCountryList::run()
{
	CURL* handle = curl_easy_init(); // creating an easy handle for this session

	if (handle)
	{
		curl_easy_setopt(handle, CURLOPT_URL, URL_FOR_AVAILABLE_COUNTRIES_DATA); //setting URL property to transfer with CURLOP_URL

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
				for (Json::Value::ArrayIndex i = 0; i != jsonData.size(); ++i) // iterate through the JSON object
				{
					available_countries_->push_back(jsonData[i]["Slug"].asString()); // push the slug data (std::string) of a country to the vector
				}
			}
			else // parsing to Json::Value failed, display HTTP data which could be the root of the error
			{
				std::cout << "Could not parse HTTP data as JSON" << std::endl;
				std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
			}
		}

		else // failed, display HTTP response code
		{
			std::cout << "HTTP ERROR: " << httpCode << std::endl;
		}

		curl_easy_cleanup(handle); // end the easy handle
	}
}