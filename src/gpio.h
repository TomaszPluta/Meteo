#pragma once



#include "wiringPi.h"




class Gpio{
public:

	enum class Mode{
		input = 0, output =1
	};

	enum class State{
			low = 0, high =1
		};


	Gpio(){
		  wiringPiSetup();
	}

	void initPin(int pinNumber, Mode mode){
		 pinMode(pinNumber, static_cast<int>(mode));
	}

	bool getPinState(int pinNumber){
		return  (digitalRead(pinNumber) == LOW);
	}


};

