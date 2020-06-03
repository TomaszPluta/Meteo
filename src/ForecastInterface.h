#pragma once


#include "WeatherCondition.h"
#include "json11/json11.hpp"


using namespace json11;

class ForecastOutputInterface{
public:
	virtual void ProduceOutput(Json forecastJson) = 0;
	std::string dump(void);
};
