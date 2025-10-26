//
// Created by sangulo on 10/26/25.
//

#ifndef ARDUINO_CONTROLLER_HH
#define ARDUINO_CONTROLLER_HH

#include <string>
#include <termios.h>

class ArduinoController
{
public:
    ArduinoController();
    ~ArduinoController();

    bool connect(const std::string& port);
    void sendCommand(char command);

private:
    int serial_port;
    bool connected;
};

#endif //ARDUINO_CONTROLLER_HH