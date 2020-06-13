//#pragma once
//
//#include <iostream>
//
//enum class Clouds{
//	cloud0,cloud1, cloud2
//};
//
//enum class Precipitation{
//	precip0, precip1, precip2
//};
//
//
//enum class ForecastDay{
//	today,
//	tomorrow,
//	afterTomorrow
//};
//
//
//std::ostream & operator<<(std::ostream & os, ForecastDay day){
//	std::string dayName;
//	switch(day)
//	{
//	case ForecastDay::today   : os << "today";    break;
//	case  ForecastDay::tomorrow: os << "tomorrow"; break;
//	case ForecastDay::afterTomorrow: os << "afterTomorrow";  break;
//	default    : os.setstate(std::ios_base::failbit);
//	}
//	return os;
//}
//
//
//
//
//class WeatherCondition{
//
//public:
//	//private:
//	//std::chrono::time_point<std::chrono::system_clock> time;
//	std::string hour;
//	int temp;
//	int humid;
//	std::string windChill;
//	std::string wind;
//	int press;
//	std::string clouds;
//	std::string perc;
//	friend std::ostream & operator<<(std::ostream & os, WeatherCondition & wd);
//};
//
//
//using DayForcasts = std::vector<WeatherCondition>;
//
//
//std::ostream& operator<<(std::ostream & os, const WeatherCondition & wd){
//	os<<wd.hour<<" - "<<wd.temp<<", "<<wd.humid<<", "<<wd.windChill<<std::endl;
//	return os;
//}
//
//
//std::ostream& operator<<(std::ostream & os,  WeatherCondition & wd){
//	os<<wd.hour<<" - "<<wd.temp<<", "<<wd.humid<<", "<<wd.windChill<<std::endl;
//	return os;
//}
//
//std::ostream& operator<<(std::ostream & os,  DayForcasts & w){
//	std::copy(w.begin(), w.end(), std::ostream_iterator<WeatherCondition>(std::cout, " "));
//}
//
//
//std::ostream& operator<<(std::ostream & os,  const DayForcasts & w){
//	std::copy(w.begin(), w.end(), std::ostream_iterator<WeatherCondition>(std::cout, " "));
//}
