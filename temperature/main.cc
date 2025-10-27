//
// Created by Sleyter Angulo on 10/26/25.
//
#include <gtkmm-4.0/gtkmm.h>
#include "arduino_controller.hh"
#include <iostream>
#include <thread>
#include <chrono>
#include "main.hh"

extern "C" void print_temp(const char*name);

MainWindow::MainWindow():
    label_title("Temperature Monitor"),
    label_temperature("Current Temperature: -- °C"),
    button_refresh("Refresh Temperature"),
    running(true)
{
    set_title("Arduino Temperature Monitor");
    set_default_size(300, 200);

    vbox.set_margin(20);
    vbox.set_spacing(10);

    label_title.set_margin_bottom(10);
    label_temperature.set_margin_bottom(10);
    label_temperature.set_css_classes({"title-2"});


    button_refresh.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_refresh_clicked));

    vbox.append(label_title);
    vbox.append(label_temperature);
    vbox.append(button_refresh);

    set_child(vbox);

    if (!arduino_controller.connect("/dev/ttyACM0")) {
        std::cerr << "Failed to connect to Arduino." << std::endl;
        label_temperature.set_text("Error: Cannot connect to Arduino.");
    }

    start_reading();
}

void MainWindow::on_button_refresh_clicked()
{
    std::string temp = arduino_controller.readData();
    if (!temp.empty()) {
        label_temperature.set_text("Current Temperature: " + temp + " °C");
    } else {
        label_temperature.set_text("Error reading temperature.");
    }
}

void MainWindow::start_reading() {
    read_thread = std::thread([this]() {
        while (running) {
            std::string temp = arduino_controller.readData();
            if (!temp.empty()) {
                Glib::signal_idle().connect_once([this, temp]() {
                    label_temperature.set_text("Current Temperature: " + temp + " °C");
                    print_temp(temp.c_str());
                });
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });
}

MainWindow::~MainWindow() {
    running = false;
    if (read_thread.joinable()) {
        read_thread.join();
    }
}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.example");

    MainWindow window;

    return app->make_window_and_run<MainWindow>(argc, argv);
}

