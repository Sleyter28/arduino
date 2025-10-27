//
// Created by Sleyter Angulo on 10/26/25.
//

#ifndef ARDUINO_MAIN_HH
#define ARDUINO_MAIN_HH

#include <gtkmm-4.0/gtkmm.h>
#include "arduino_controller.hh"
#include <iostream>
#include <thread>
#include <chrono>

class MainWindow: public Gtk:: Window
{
public:
    MainWindow();
    ~MainWindow();

private:
    Gtk::Box vbox{Gtk::Orientation::VERTICAL};
    Gtk::Button button_on, button_off, button_greet;
    Gtk::Label* label = Gtk::manage(new Gtk::Label("Hello Arduino!"));
    Gtk::Entry* my_entry = Gtk::manage(new Gtk::Entry());

    ArduinoController arduino;

    void on_button_on_clicked();
    void on_button_off_clicked();
    void on_button_greet_clicked();
};

#endif //ARDUINO_MAIN_HH