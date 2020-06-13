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


class Form : public Fl_Window {
public:
	Form() : Fl_Window(200, 100, 300, 300, "Label example") {
		this->resizable(this);

		this->label1.align(FL_ALIGN_LEFT | FL_ALIGN_TOP | FL_ALIGN_INSIDE | FL_ALIGN_CLIP | FL_ALIGN_WRAP);
	}

private:
	Fl_Box label1 {10, 10, 75, 25, "label1"};
};



class ForecastOutputGui : public Fl_Window , public ForecastOutputInterface{
public:
	ForecastOutputGui() :  Fl_Window (winX, winY, "Weather forecasts"){
		this->resizable(this);
	}


	void ProduceOutput(Json forecastJson) {
		Json::object v = forecastJson.object_items();
		for (auto & entity : v){
			std::cout<<entity.first.c_str()<<std::endl;
			Fl_Output *label = new Fl_Output(indent, vPos+=spaceV, labelH, labelV);
			label->copy_label(entity.first.c_str());
			label->value(std::to_string(entity.second.int_value()).c_str());
		}
		   this->resizable(this);
	    this->show();
	};

private:

	static constexpr int winX = 140;
	static constexpr int winY = 300;
	int vPos = 0;
	static constexpr int labelH = 50;
	static constexpr int labelV = 20;
	static constexpr int indent = 60;
	static constexpr int spaceV = 40;


void update(std::map<std::string, int>m);
std::vector<Fl_Output> labels;



};




//--------------------------------------------
int main() {




	Json::object j ={{"hour", 11},{"temp", 27}, {"humid", 60}, {"press", 1024}};
	Json jj(j);
	ForecastOutputGui fg;
	fg.ProduceOutput(jj);

	return Fl::run();

}






