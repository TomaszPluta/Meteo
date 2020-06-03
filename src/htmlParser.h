#pragma once
#include <string>
#include <map>
#include <algorithm>






using StrIter = std::string::const_iterator;


//for (node n = parseElements(); e.ContainNodes)
std::pair<StrIter, StrIter> GetHtmlElementIters(StrIter contentFirst, StrIter contentLast, std::string tag){
	std::string openingTag = "<"+tag;
	std::string openingTagEnd = ">";
	std::string closingTag = "</"+tag+">";
	auto  openingTagStartIter = std::search(contentFirst, contentLast, openingTag.begin(), openingTag.end());
	if(openingTagStartIter == contentLast){
		return std::make_pair(contentLast, contentLast);
	}

	auto  openingTagEndIter =  std::search(openingTagStartIter, contentLast, openingTagEnd.begin(), openingTagEnd.end());
	if(openingTagEndIter == contentLast){
		return std::make_pair(contentLast, contentLast);
	}
	std::advance(openingTagEndIter, 1);
	if(openingTagEndIter == contentLast){
		return std::make_pair(contentLast, contentLast);
	}

	auto  closingTagIter =  std::search(openingTagEndIter, contentLast, closingTag.begin(), closingTag.end());
	if(closingTagIter == contentLast){
		return std::make_pair(contentLast, contentLast);
	}

	return std::make_pair(openingTagEndIter, closingTagIter);

}

