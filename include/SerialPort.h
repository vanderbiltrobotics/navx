#ifndef NAVX_SERIALPORT_H
#define NAVX_SERIALPORT_H

#include <string>
#include <termios.h>
#include <unistd.h>

class SerialPort {

private:
    int ReadBufferSize;
    int timeout;
    char terminationChar;
    bool termination;
    std::string id;
    int baudRate;
    int fd;
    struct termios tty;
    int err;

public:
    SerialPort(int baudRate, std::string id);

    void Init(int baudRate, std::string id);

    void SetReadBufferSize(int size);

    void SetTimeout(int timeout);

    void EnableTermination(char c);

    void Flush();

    void Write(char* data, int length);

    int GetBytesReceived();

    int Read(char* data, int size);

    void WaitForData();

    void Reset();

    void Close();
};

#endif // NAVX_SERIALPORT_H
