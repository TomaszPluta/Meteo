#include <string>
#include "NetworkTools.h"
#include "WeatherCondition.h"
#include "json11/json11.hpp"
#include "HtmlDownloader.h"
#include "HtmlDownloaderCurl.h"
#include <htmlcxx/html/ParserDom.h>

using namespace json11;
using namespace htmlcxx;
using namespace kp;




#include <stdio.h>
#include <tidy/tidy.h>
#include <tidy/tidybuffio.h>
#include <curl/curl.h>


constexpr const char * DWNLD_FILENAME = "meteo.html";
constexpr const char * DWNLD_URL = "https://www.meteoprog.pl/pl/meteograms/Krakow/";




int convertMmToHpa(int mm){
	return std::round(mm * 1.33);
}


class WebPageExtractor{
public:
	virtual Json extract(void) = 0;
private:
	HtmlDownloader * m_downloader;
};



class WeatherParser : public WebPageExtractor{
public:
	WeatherParser(HtmlDownloader * downloader, std::string url) : m_downloader{downloader}, m_url{url}{}

	Json extract(void){
		download(m_url);
		tidyInit();
		parse();
		//clear();
		return get();
	}

private:
	Json::array forecasts;
	HtmlDownloader * m_downloader;
	std::string m_url;
	CURL *curl = nullptr;
	TidyDoc tdoc;
	TidyBuffer docbuf = {0};
	TidyBuffer tidy_errbuf = {0};

	std::string GetHtmlNodeContent(TidyDoc doc, TidyNode node){
		TidyBuffer buf;
		tidyBufInit(&buf);
		tidyNodeGetText(doc, node, &buf);
		std::string content((const char*)buf.bp);
		tidyBufFree(&buf);
		return content;
	}


	bool parse(){
		if (tidyParseFile(tdoc, "meteo.html") < 0){
			return false;
		}
		if (tidyRunDiagnostics(tdoc) < 0){
			return false;
		}
		dumpNode(tdoc, tidyGetRoot(tdoc), 0);

		tidyBufFree(&docbuf);
		tidyRelease(tdoc);
		return 1;
	}


	void tidyInit(void){
		tdoc = tidyCreate();
		tidyOptSetBool(tdoc, TidyForceOutput, yes);
		tidyOptSetInt(tdoc, TidyWrapLen, 4096);
		tidySetErrorBuffer(tdoc, &tidy_errbuf);
		tidyBufInit(&docbuf);
	}

	void download (std::string url){
		m_downloader->Download(url, "meteo.html"); //domain name as filename
	}

	Json get(){
		return Json(forecasts);
	}


  void dumpNode(TidyDoc doc, TidyNode tnod, int indent)
  {
	for(TidyNode child = tidyGetChild(tnod); child; child = tidyGetNext(child) ) {
		ctmbstr name = tidyNodeGetName(child);
		Json::object forecastEntity;
			if ((name) && std::string(name) == "tr"){
				TidyNode trChild = tidyGetChild(child);
				ctmbstr TRnextName = tidyNodeGetName(trChild);
				if (std::string(TRnextName) == "td"){
					TidyNode tdHour = tidyGetChild(child);
					if (!tdHour){
						break;
					}
					TidyNode cell = tidyGetChild(tdHour);
					ctmbstr cellName = tidyNodeGetName(cell);
					int hour = 99;
					if (!cellName){
						try{
							hour = std::stoi(GetHtmlNodeContent(doc, cell));
						}
						catch (const std::invalid_argument& ia){

						}
						catch (const std::out_of_range& oor) {

						}
					}
					forecastEntity["hour"] = hour;

					TidyNode previousNode = tdHour;
					for (int i =0; i <6; i++){
						TidyNode td = tidyGetNext(previousNode);
						if (!td){
							break;
						}
						ctmbstr TRnextName = tidyNodeGetName(td);
						if (std::string(TRnextName) == "td"){

							TidyNode cell = tidyGetChild(td);
							ctmbstr cellName = tidyNodeGetName(cell);
							if (!cellName){
								std::string content = GetHtmlNodeContent(doc, cell);
								if (content.find("°C")!= std::string::npos){
									forecastEntity["temp"] = std::stoi(content);
								}else if (content.find("mm")!= std::string::npos){
									forecastEntity["press"] = std::stoi(content);
								}else if (content.find("%")!= std::string::npos){
									forecastEntity["humid"] = std::stoi(content);
								}
							}
						}
						previousNode = td;
					}
				}
		}
		if (forecastEntity.size() > 0){
			forecasts.push_back(forecastEntity);
		}
		dumpNode(doc, child, indent + 4);
	}
}
};


