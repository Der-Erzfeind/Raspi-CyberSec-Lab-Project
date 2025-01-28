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
        if (clk == 0) {
            std::cout << "\033[A" << std::flush; 	//Arrow Down
            //std::cout << "down";	//Arrow Down
        } else {
            //std::cout << "up";		//Arrow Up
            std::cout << "\033[B" << std::flush; 	//Arrow Up
        }
    }
}

void ISR_button(int gpio, int level, uint32_t tick) {
    	if (level == PI_LOW) {
    	    //std::cout << "enter" << std::endl; //Enter
            std::cout << std::endl; 	//Enter
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

void readEncoder() {
	gpioInit();
    	while (true) {
    	    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Let the ISR functions handle events
    	}

    //gpioTerminate();
}
#endif //ENCODER_H
