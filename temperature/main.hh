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
    Gtk::Label label_title, label_temperature;
    Gtk::Button button_refresh;
    ArduinoController arduino_controller;
    std::thread read_thread;
    bool running;

    void on_button_refresh_clicked();
    void start_reading();
};


#endif //ARDUINO_MAIN_HH