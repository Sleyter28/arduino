//
// Created by Sleyter Angulo on 11/7/25.
//

#include "main.hh"


MainWindow::MainWindow():sendBtn("Send"){
    set_title("Arduino LCD Controller");

    set_default_size(300, 200);

    vbox.set_margin(20);
    vbox.set_spacing(10);

    sendBtn.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_sendBtn_on_clicked));

    inputTxt->set_placeholder_text("Ingrese su nombre");
    inputTxt->set_max_length(50);
    inputTxt->set_visibility(true);

    vbox.append(*titleLbl);
    vbox.append(*inputTxt);
    vbox.append(sendBtn);

    set_child(vbox);

    if(!arduino.connect("/dev/ttyACM0")){
        std::cerr << "No se pudo conectar al Arduino." << std::endl;
    }

};

void MainWindow::on_sendBtn_on_clicked(){
    std::string name = inputTxt->get_text();
    std::cout << name << std::endl;
    arduino.sendCommand('1');
}

MainWindow::~MainWindow(){};


int main(int argc, char* argv[]){
    auto app = Gtk::Application::create("org.gtkmm.lcdcontroller");
    return app->make_window_and_run<MainWindow>(argc, argv);
}