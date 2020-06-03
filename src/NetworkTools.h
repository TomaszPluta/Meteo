#pragma once

#include <string>
#include <boost/asio.hpp>
#include <iostream>

#include <stdlib.h>

class  NetworkTools{
public:

	void download(std::string url, std::string filename){

		 system(std::string("wget "  + url + " -O " + filename ).c_str());


//		boost::asio::ip::tcp::iostream stream (url, "http");
//	    stream << "GET / HTTP/1.1\r\n";
//	    stream << "Host: www.wxample.com\r\n";
//	    stream << "Accept: */*\r\n";
//	    stream << "Connection: close\r\n\r\n";
//	    stream.flush();
//	    std::cout << stream.rdbuf();
	}

private:
	static inline constexpr const char * DWNLD_CMD = "wget";
};
