#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>.H>
#include <Fl/Fl_Output.H>

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(340,180);

  Fl_Output *outputTemp = new Fl_Output(60, 20, 50, 20, "temp");
  outputTemp->value("26");
  Fl_Output *outputHumid = new Fl_Output(60, 60, 50, 20, "humid");
  outputHumid->value("67");
  Fl_Output *outputPress = new Fl_Output(60, 100, 50, 20, "press");
  outputPress->value("1017");



  window->end();
  window->show(argc, argv);
  return Fl::run();
}


