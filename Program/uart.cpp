#include <wiringPi.h>
#include <wiringSerial.h>

int main() {
    // Serial port initialization
    int serial_port;
    
    // Open the UART port (e.g., /dev/serial0 or /dev/ttyAMA0)
    serial_port = serialOpen("/dev/serial0", 9600); // 9600 baud rate

    if (serial_port == -1) {
        std::cerr << "Error: Unable to open UART port." << std::endl;
        return 1;
    }

    // Message to send over UART
    std::string message = "Hello, Raspberry Pi UART!";
    
    // Sending message byte by byte
    for (size_t i = 0; i < message.size(); i++) {
        serialPutchar(serial_port, message[i]);
    }

    // Flush the serial port
    serialFlush(serial_port);

    std::cout << "Message sent over UART: " << message << std::endl;

    // Close the UART port
    serialClose(serial_port);

    return 0;
}
