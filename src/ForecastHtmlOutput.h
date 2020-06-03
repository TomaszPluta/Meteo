#pragma once


#include "ForecastInterface.h"



class ForecastHtmlOutput : public ForecastOutputInterface{
	public:

	void produceOutput(Json forecastJson){
			m_outputHtmlFile.open("todayWeather.html");
			m_outputHtmlFile<< HEADER << BODY_START << "\n"
					<< DIV_START << "DAY: "<< m_day << DIV_END << "\n"
					<< DIV_START << "TMP: "<< m_wc.temp << DIV_END << "\n"
					<< DIV_START << "OPD: "<< m_wc.humid << DIV_END << "\n"
					<< DIV_START << "CNS: "<< m_wc.press << DIV_END << "\n"
					<< DIV_START << "WTR: "<< m_wc.wind << DIV_END << "\n";
			m_outputHtmlFile.close();
		}

	void getVals(Json json){

	}


	private:
		std::string m_day;
		std::ofstream m_outputHtmlFile;
		static inline constexpr const char * HEADER = "<head> \n"
				"<script type=\"text/javascript\" language=\"javascript\"> \n"
				"setTimeout(function(){ \n"
				"window.location.reload(1); \n"
				"}, 5000);\n"
				"   </script>\n"
				"</head>\n";
		static inline constexpr const char * BODY_START = "<body>";
		static inline constexpr const char * BODY_END = "<body>";
		static inline constexpr const char * DIV_START = "<div style=\"font-size:180px;font-weight:bold;line-height:120%\" align=\"center\" id=\"val\">";
		static inline constexpr const char * DIV_END = "</div>";
	};


	}
};
