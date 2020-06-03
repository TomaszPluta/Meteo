#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <iterator>

#include "WeatherCondition.h"




class WeatherStats{

	WeatherStats(DayForcasts weatherCond) : m_weatherCond{weatherCond}{};

	template <typename Pred>
	std::pair<WeatherCondition, WeatherCondition>  GetMinMaxForecastCondition(ForecastDay day, Pred pred){
		const auto [min, max] = std::minmax_element(m_weatherCond.begin(), m_weatherCond.end(), pred);
		return std::make_pair(*min, *max);
	}


	std::vector<WeatherCondition> GetWeatherForecastsForHotestHours(ForecastDay day, int margin = 0){
		auto [min, max]  =  GetMinMaxForecastCondition(day, minTempComp);
		std::vector<WeatherCondition> hotest;
		auto hotestEndIter = std::stable_partition(m_weatherCond.begin(), m_weatherCond.end(),   [&](WeatherCondition const & w){
			return (w.temp > max.temp - (margin));} );
		std::copy(m_weatherCond.begin(), hotestEndIter, std::ostream_iterator<WeatherCondition>(std::cout, " "));
		std::cout<<m_weatherCond;
		std::cout<<std::endl<<std::endl;
		return hotest;
	}


	int GetTempDiff(ForecastDay day){
		const auto [min,max] = GetMinMaxForecastCondition(day, minTempComp);
		return max.temp - min.temp;
	}

	int GetPressDiff(ForecastDay day){
		const auto [min,max] = GetMinMaxForecastCondition(day, minTempComp);
		return max.temp - min.temp;
	}

	int GetHumidDiff(ForecastDay day){
		const auto [min,max] = GetMinMaxForecastCondition(day, minTempComp);
		return max.temp - min.temp;
	}

	static inline constexpr auto minPressComp = [](WeatherCondition const & a, WeatherCondition const & b){
		return a.press < b.press;
	};

	static inline constexpr auto minTempComp = [](WeatherCondition const & a, WeatherCondition const & b){
		return a.temp < b.temp;
	};

private:
	DayForcasts m_weatherCond;
};
