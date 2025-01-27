#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>

// GPIO pin definitions
#define CLK 27  // GPIO17
#define DT 17   // GPIO27
#define BUTTON 22 // GPIO22

// State variables
volatile int counter = 0;
volatile bool buttonPressed = false;
volatile int lastEncoded = 0;

// Interrupt handlers
void ISR_CLK(int gpio, int level, uint32_t tick) {
	std::cout << "isr_clk" << std::endl;
    volatile int encoded = (level << 1) | gpioRead(DT);
    int delta = (lastEncoded - encoded);

    if (delta == 1 || delta == -3) {
        counter++;
        std::cout << "Rotated clockwise, Counter: " << counter << std::endl;
    } else if (delta == -1 || delta == 3) {
        counter--;
        std::cout << "Rotated counterclockwise, Counter: " << counter << std::endl;
    }

	std::cout << "encoded: " << encoded << std::endl;
	std::cout << "last encoded: " << lastEncoded << std::endl;
    lastEncoded = encoded; // Store the current encoded value
}

void ISR_DT(int gpio, int level, uint32_t tick) {
	std::cout << "isr_DT" << std::endl;
    volatile int encoded = (gpioRead(CLK) << 1) | level;
    int delta = (lastEncoded - encoded);

    if (delta == 1 || delta == -3) {
        counter++;
        std::cout << "Rotated clockwise, Counter: " << counter << std::endl;
    } else if (delta == -1 || delta == 3) {
        counter--;
        std::cout << "Rotated counterclockwise, Counter: " << counter << std::endl;
    }

	std::cout << "encoded: " << encoded << std::endl;
	std::cout << "last encoded: " << lastEncoded << std::endl;
    lastEncoded = encoded; // Store the current encoded value
}

void ISR_button(int gpio, int level, uint32_t tick) {
    if (level == PI_LOW) { // Only handle button press (not release)
        buttonPressed = !buttonPressed; // Toggle button state
        std::cout << "Button state changed: " << (buttonPressed ? "ON" : "OFF") << std::endl;
    }
}

void setupGPIO() {
    // Initialize pigpio
    if (gpioInitialise() < 0) {
        std::cerr << "Failed to initialize pigpio." << std::endl;
        exit(1);
    }

    // Set up GPIO pins
    gpioSetMode(CLK, PI_INPUT);
    gpioSetMode(DT, PI_INPUT);
    gpioSetMode(BUTTON, PI_INPUT);

    // Enable pull-up resistors
    gpioSetPullUpDown(CLK, PI_PUD_UP);
    gpioSetPullUpDown(DT, PI_PUD_UP);
    gpioSetPullUpDown(BUTTON, PI_PUD_UP);

	gpioGlitchFilter(CLK, 1000);
	gpioGlitchFilter(DT, 1000);
    // Attach interrupt handlers
    if(gpioSetAlertFunc(CLK, ISR_CLK) != 0){
        std::cerr << "Failed to set CLK ISR function!" << std::endl;
        gpioTerminate();
	exit(1);
    }

    if(gpioSetAlertFunc(DT, ISR_DT) != 0){
        std::cerr << "Failed to set DT ISR function!" << std::endl;
        gpioTerminate();
	exit(1);
    }
	
    // Initialize state
    lastEncoded = (gpioRead(CLK) << 1) | gpioRead(DT);
}

int main() {
    setupGPIO();
	
    std::cout << "Rotary Encoder with Pushbutton Program (using pigpio and interrupts)" << std::endl;

    // Main loop (empty since we're using interrupts)
    while (true) {
        // Sleep to reduce CPU usage, actual handling is in interrupts
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Terminate pigpio
    gpioTerminate();
    return 0;
}

