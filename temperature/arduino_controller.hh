//
// Created by Sleyter Angulo on 10/26/25.
//

#ifndef ARDUINO_ARDUINO_CONTROLLER_HH
#define ARDUINO_ARDUINO_CONTROLLER_HH

#include <string>
#include <termios.h>

class ArduinoController
{
public:
    ArduinoController();
    ~ArduinoController();

    bool connect(const std::string& port);
    std::string readData();

private:
    int serial_port;
    bool connected;
};


#endif //ARDUINO_ARDUINO_CONTROLLER_HH