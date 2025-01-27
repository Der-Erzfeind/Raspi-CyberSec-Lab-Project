#ifndef ENCODER_H
#define ENCODER_H

#include <iostream>
#include <pigpio.h>
#include <thread>

#define CLK 17
#define DT 27
#define BUTTON 22


void ISR_rotation(int gpio, int level, uint32_t tick) {
    if (level == PI_LOW) {
        volatile int clk = gpioRead(CLK);
        if (clk == 1) {
            std::cout << "\u2193" << std::endl;	//Arrow Down
        } else {
            std::cout << "\u2191" << std::endl;	//Arrow Up
        }
    }
}

void ISR_button(int gpio, int level, uint32_t tick) {
    	if (level == PI_LOW) {
    	    std::cout << "\u21B5" << std::endl; //Enter
    	}
}

void gpioInit() {
    	if (gpioInitialise() < 0) {
    	    std::cerr << "Failed to initialize pigpio." << std::endl;
    	    exit(1);
    	}

    	gpioSetMode(CLK, PI_INPUT);
    	gpioSetMode(DT, PI_INPUT);
    	gpioSetMode(BUTTON, PI_INPUT);

    	gpioSetPullUpDown(CLK, PI_PUD_UP);
    	gpioSetPullUpDown(DT, PI_PUD_UP);
    	gpioSetPullUpDown(BUTTON, PI_PUD_UP);

	gpioGlitchFilter(CLK, 500);
	gpioGlitchFilter(DT, 500);
	gpioGlitchFilter(BUTTON, 500);

    if (gpioSetAlertFunc(DT, ISR_rotation) != 0) {
        std::cerr << "Failed to set ISR_rotation function!" << std::endl;
        gpioTerminate();
        exit(1);
    }

    if (gpioSetAlertFunc(BUTTON, ISR_button) != 0) {
        std::cerr << "Failed to set ISR_button function!" << std::endl;
        gpioTerminate();
        exit(1);
    }
}

void waitForEncoder() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Let the ISR functions handle events
    }

    //gpioTerminate();
}

#endif //ENCODER_H
