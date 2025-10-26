#include "arduino_controller.hh"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

ArduinoController::ArduinoController(): connected(false), serial_port(-1) {}
ArduinoController::~ArduinoController() {
    if (connected) {
        close(serial_port);
    }
}

bool ArduinoController::connect(const std::string& port)
{
    serial_port = open(port.c_str(), O_RDWR);
    if (serial_port < 0) {
        std::cerr << "Error opening serial port: " << strerror(errno) << std::endl;
        return false;
    }
    termios tty;
    if (tcgetattr(serial_port, &tty) != 0)
    {
        std::cerr << "Error reading serial port attributes: " << strerror(errno) << std::endl;
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

void ArduinoController::sendCommand(char command)
{
    if (connected)
    {
        write(serial_port, &command, 1);
    }
    else
    {
        std::cerr << "Not connected to Arduino." << std::endl;
    }
}
