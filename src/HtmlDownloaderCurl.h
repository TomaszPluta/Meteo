#include <stdio.h>
#include <curl/curl.h>

#include <string>
#include "HtmlDownloader.h"
#include <fstream>




class HtmlDownloaderCurl : public HtmlDownloader{

public:

	bool Download(std::string url, std::string filename) override{
		curl = curl_easy_init();
		if (!curl) {
			return false;
		}

		CURLcode res;
		std::ofstream fs;
		fs.open(filename);
		if (!fs.is_open()){
			return false;
		}
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fs);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fs.close();
		return true;
	}

	~HtmlDownloaderCurl(){};

private:
	static size_t write_data(char *ptr, size_t size, size_t nmemb, void *dataOut) {
		std::ofstream * fs = static_cast<std::ofstream*>(dataOut);
		size_t nBytes = size * nmemb;
		fs->write(ptr, nBytes);
		return nBytes;
	}

	CURL *curl;
};
