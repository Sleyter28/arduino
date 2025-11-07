//
// Created by Sleyter Angulo on 11/7/25.
//

#ifndef ARDUINO_MAIN_HH
#define ARDUINO_MAIN_HH

#include <gtkmm-4.0/gtkmm.h>
#include "arduino-controller.hh"
#include <iostream>
#include <thread>
#include <chrono>



class MainWindow: public Gtk::Window {
public:
    MainWindow();
    ~MainWindow();

private:
    Gtk::Box vbox{Gtk::Orientation::VERTICAL};
    Gtk::Label* titleLbl = Gtk::manage(new Gtk::Label("Hello Arduino!"));
    Gtk::Entry* inputTxt = Gtk::manage(new Gtk::Entry());
    Gtk::Button sendBtn;

    ArduinoController arduino;

    void on_sendBtn_on_clicked();
};

#endif //ARDUINO_MAIN_HH