//
// Created by sangulo on 10/26/25.
//

#include <gtkmm-4.0/gtkmm.h>
#include <gtkmm-4.0/gtkmm/entry.h>
#include "arduino_controller.hh"
#include <iostream>
#include "main.hh"

extern "C" void hello(const char*name);

MainWindow::MainWindow():
    button_on("Turn On"),
    button_off("Turn Off"),
    button_greet("Say hello")
{
        set_title("Arduino LED Controller");
        set_default_size(300, 150);

        vbox.set_margin(20);
        vbox.set_spacing(10);

        button_on.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_on_clicked));
        button_off.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_off_clicked));
        button_greet.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_greet_clicked));

        vbox.append(*label);

        my_entry->set_placeholder_text("Enter your name");
        my_entry->set_max_length(50);
        my_entry->set_visibility(true); // For password mode

        vbox.append(*my_entry);
        vbox.append(button_greet);
        vbox.append(button_on);
        vbox.append(button_off);

        set_child(vbox);

        if (!arduino.connect("/dev/ttyACM0")) {
            std::cerr << "Failed to connect to Arduino." << std::endl;
        }

}

void MainWindow::on_button_on_clicked()
{
    arduino.sendCommand('1');
}

void MainWindow::on_button_off_clicked()
{
    arduino.sendCommand('0');
}

void MainWindow::on_button_greet_clicked()
{
    std::string name = my_entry->get_text();
    const char* cname = name.c_str();
    hello(cname);
    label->set_text("Hello, " + name + "!");
}

MainWindow::~MainWindow()
{
}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.ledcontroller");

    return app->make_window_and_run<MainWindow>(argc, argv);
}