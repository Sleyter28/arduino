//
// Created by Sleyter Angulo on 11/7/25.
//

#include "arduino_controller.hh"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

ArduinoController::ArduinoController(): isConnected(false), serialPort(-1){};

ArduinoController::~ArduinoController(){
    if (isConnected) {
        close(serialPort);
    }
};

bool ArduinoController::connect(const std::string& port){
    serialPort = open(port.c_str(), O_RDWR);
    if (serialPort < 0){
        std::cerr << "Error opening the serial port: " << strerror(errno) << std::endl;
        return false;
    }
    termios tty;
    if (tcgetattr(serialPort, &tty) != 0) {
        std::cerr << "Error reading serial port attributes " << strerror(errno) << std::endl;
        return false;
    }
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &=  ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_iflag = 0;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 5;

    tcflush(serialPort, TCIFLUSH);
    tcsetattr(serialPort, TCSANOW, &tty);

    isConnected = true;

    return true;

}

void ArduinoController::sendCommand(char command){
    if (isConnected){
        write(serialPort, &command, 1);
    }
    else {
        std::cerr << "Not connected to Arduino." << std::endl;
    }
}