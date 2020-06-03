#include "WeatherForecastParser.h"



int main (void){
	HtmlDownloaderCurl curlDownloader;
	WeatherParser wp(&curlDownloader, DWNLD_URL);


	Json weatherForecast = wp.extract();
	std::cout<<weatherForecast.dump();
	std::cout<<"\n\n\n";
	std::cout<<weatherForecast["hour"].int_value()<<"\n";

	std::cout<<weatherForecast["humid"].int_value()<<"\n";
	std::cout<<weatherForecast["press"].int_value()<<"\n";

	//	int hour = WeatherConditionJson["hour"].int_value();
	//	Json::array cond = WeatherConditionJson["conditions"].array_items();
	//	Json temp = cond[0];
	//	Json::array  tempArr = temp["temp"].array_items();
	//	int tempVal  = tempArr[0].int_value();
	//	std::string  tempSymbol  = tempArr[1].string_value();
	//

}





//int i =0;
//class App{
//
//public:
//
//	void  EventLoop (void){
//		Gpio gpio;
//		bool touchKeyPressed;
//		bool irKeyPressed;
//		constexpr int touchpadKey = 25;
//		constexpr int irKey = 2;
//
//		gpio.initPin(touchpadKey, Gpio::Mode::input);
//		gpio.initPin(irKey, Gpio::Mode::input);
//		while (1){
//			touchKeyPressed = gpio.getPinState(touchpadKey);
//			irKeyPressed = gpio.getPinState(irKey);
//
//			if (touchKeyPressed || irKeyPressed){
//				std::cout<<"key pressed"<<std::endl;
//				std::lock_guard<std::mutex> lock (m_mutex);
//				m_touchKeypressesEvent.notify_one();
//				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//				m_dayNo++;
//				if (m_dayNo == 3){
//					m_dayNo = 0;
//				}
//			}
//			std::this_thread::sleep_for(std::chrono::milliseconds(300));
//		}
//	}
//
//	void OutputUpdate(void){
//		while (1){
//			WeatherForecastParser weatherForecast("aaaa");
//			ForecastDay dayToDisplay;
//			if (m_dayNo == 0){
//				dayToDisplay = ForecastDay::today;
//			}else if (m_dayNo == 1){
//				dayToDisplay = ForecastDay::tomorrow;
//			}else if (m_dayNo == 2){
//				dayToDisplay = ForecastDay::afterTomorrow;
//			}
//
//			//			weatherForecast.ProduceForecastFileForHourInDay(dayToDisplay, 13);
//			//			std::chrono::time_point now = std::chrono::system_clock::now();
//			//			time_t tt = std::chrono::system_clock::to_time_t(now);
//			//			tm local_tm = *localtime(&tt);
//			//			//local_tm.tm_hour += 3;
//			//			local_tm.tm_sec += 30;
//			//			std::unique_lock<std::mutex> lock(m_mutex);
//			//			//std::chrono::system_clock::from_time_t (mktime(&local_tm))
//			//			std::chrono::duration<long> waitMin =  std::chrono::minutes(60);
//			//			m_touchKeypressesEvent.wait_for(lock, waitMin);
//		}
//	}
//
//
//
//private:
//	int m_dayNo = 0;
//	std::mutex m_mutex;
//	std::condition_variable m_touchKeypressesEvent;
//};
//
