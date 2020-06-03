#pragma once
#include <string>



class HtmlDownloader{
public:
	virtual bool Download(std::string url, std::string filename) = 0;
};
