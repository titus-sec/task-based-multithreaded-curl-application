# Task-based multithreaded cURL application for transferring COVID-19 Coronavirus statistics

I've implemented open source libcurl (https://github.com/curl/curl) and json parser (https://github.com/open-source-parsers/jsoncpp) libraries to get COVID-19 statistics of each country worldwide. My goal was to get countries’ number of confirmed cases and deaths caused by COVID-19 efficiently, hence I've implemented multithreaded task-based parallelism system. 


*update this*

## Getting Started *update this*

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Installing libraries

You can download and install JsonCpp using the vcpkg dependency manager:
```
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install jsoncpp
```

You can download and install curl and libcurl using the vcpkg dependency manager:

```
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install libcurl
```

Libraries used (alternative installation methods are provided in the provided GitHub repositories):
libcurl (https://curl.haxx.se/ ; GitHub repo: https://github.com/curl/curl)
JsonCpp (GitHub repo: https://github.com/open-source-parsers/jsoncpp)

## Running the tests *update this*

Explain how to run the automated tests for this system

### Break down into end to end tests *update this*

Explain what these tests test and why

```
Give an example
```

*update this*

## Authors
**Titas Saunorius** (1800284@uad.ac.uk) [titus-sec](https://github.com/titus-sec)
Abertay University
CMP 202 Data Structures and Algorithms 2

## Acknowledgments *update this*

Thanks libcurl (https://github.com/curl/curl) and JsonCpp (https://github.com/open-source-parsers/jsoncpp) :)
