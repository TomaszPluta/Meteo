#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <Fl/Fl_Output.H>


#include <FL/Fl_Box.H>


#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>
#include "json11/json11.hpp"
#include "ForecastInterface.h"
using namespace json11;

//http://www3.telus.net/public/robark/
//http://quay.poly.asu.edu/Ser321/Resources/doc/FLTK-Tutorial.pdf
//https://github.com/gammasoft71/Examples_FLTK


//--------------------------------------------
void SaveCallback(Fl_Widget* widg, void*) {
   Fl_Button* button = (Fl_Button*)widg;
   button->label("Refreshed"); //redraw not necessary

   button->clear_active();
   button->redraw();
}




class ForecastOutputGui : public Fl_Window , public ForecastOutputInterface{
public:
	ForecastOutputGui() :  Fl_Window (winH, winV, "Weather forecasts"){
		this->resizable(this);
	}


	void ProduceOutput(Json forecastJson) {
		Json::object j = forecastJson.object_items();

		for (auto & entity : j){
			std::shared_ptr<Fl_Output> label = std::make_shared<Fl_Output>(indent, vPos+=spaceV, labelH, labelV);
			label->copy_label(entity.first.c_str());
			label->value(std::to_string(entity.second.int_value()).c_str());
			label->labelsize(labelV);
			label->textsize(labelV-2);
			labels.push_back(label);

		}

		this->resizable(this);
	    this->show();
	};


	void update(Json forecastJson){
		Json::object j = forecastJson.object_items();
		for (auto & entity : j){
			auto result = std::find_if(labels.begin(), labels.end(), [&](std::shared_ptr<Fl_Output> lb){
				return (std::string(lb->label()) == std::string(entity.first));
			});
			if (result != labels.end()){
				(*result)->value(std::to_string(entity.second.int_value()).c_str());
		}
		}
	}


private:

	static constexpr int winH = 250;
	static constexpr int winV = 350;
	static constexpr int labelH = 50;
	static constexpr int labelV = 20;
	static constexpr int indent = 60;
	static constexpr int spaceV = 40;
	int vPos = 0;


std::vector<std::shared_ptr<Fl_Output>> labels;

};




//--------------------------------------------
int main() {


	Json::object j ={{"hour", 11},{"temp", 27}, {"humid", 60}, {"press", 1024}};
	Json jj(j);
	ForecastOutputGui fg;
	fg.ProduceOutput(jj);

	Json::object k ={{"hour", 10},{"temp", 11}, {"humid", 50}, {"press", 1024}};
	Json kk(j);
	fg.update(kk);
	return Fl::run();

}






