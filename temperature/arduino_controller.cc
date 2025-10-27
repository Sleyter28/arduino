//
// Created by Sleyter Angulo on 10/26/25.
//

#include "arduino_controller.hh"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <algorithm>

ArduinoController::ArduinoController() : serial_port(-1), connected(false) {}

ArduinoController::~ArduinoController() {
    if (connected) close(serial_port);
}

bool ArduinoController::connect(const std::string& port) {
    serial_port = open(port.c_str(), O_RDWR | O_NOCTTY);
    if (serial_port < 0) {
        std::cerr << "Error abriendo el puerto " << port << std::endl;
        return false;
    }

    termios tty;
    if (tcgetattr(serial_port, &tty) != 0) {
        std::cerr << "Error obteniendo configuración del puerto." << std::endl;
        return false;
    }

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_lflag = 0;
    tty.c_oflag = 0;
    tty.c_iflag = 0;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 5;

    tcflush(serial_port, TCIFLUSH);
    tcsetattr(serial_port, TCSANOW, &tty);

    connected = true;
    return true;
}

std::string ArduinoController::readData() {
    if (!connected) return "";

    char buffer[32];
    int n = read(serial_port, &buffer, sizeof(buffer) - 1);
    if (n > 0) {
        buffer[n] = '\0';
        std::string data(buffer);
        data.erase(std::remove(data.begin(), data.end(), '\r'), data.end());
        data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());
        return data;
    }
    return "";
}


