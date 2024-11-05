#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "menu.h"
#include "commands.h"

// Function prototypes
void displayMenu(Menu& menu);
void clearScreen();
void handleSelection(int selectedOption);
int getch();

Menu wifiMenu;

int main() {

    Menu wifiMenu = Menu("Wifi Menu", "WEP", "WPA", "WPA2", "WPA3", "back");
    Menu bluetoothMenu = Menu("Bluetooth Menu", "dummy traffic", "back", (&startBluetooth)(), (&setcurrentMenu)(mainMenu));
    Menu webappMenu = Menu ("Webapp Menu", "juice shop", "back", (&startJuiceShop)(), (&setcurrentMenu)(mainMenu));
    Menu mainMenu = Menu("Main Menu", "Wifi", "Bluetooth", "Webapp", "Power Off", (&setcurrentMenu)(wifiMenu), (&setcurrentMenu)(bluetoothMenu), (&setcurrentMenu)(webappMenu), (&shutdown)());


    // std::vector<bool*> wifiFunctions = {(&startWEP)(), (&startWPA)(), (&startWPA2)(), (&startWPA3)(), (&setcurrentMenu)(mainMenu)};

    std::vector<bool(*)(), bool(*)(Menu&)> wifiFunctions = {&startWEP, &startWPA, &startWPA2, &startWPA3, &setcurrentMenu};

    Menu* currentMenu = &mainMenu;

    while (true) {
        clearScreen();
        displayMenu(*currentMenu);

        int key = getch();

        if (key == 27) { // Escape sequence for arrow keys starts with 27
            if (getch() == 91) { // '[' after the escape sequence
                switch (getch()) {
                    case 'A': // Up arrow
                        // selectedOption = (selectedOption - 1 + numOptions) % numOptions;
                        currentMenu->setSelectedOption((currentMenu->getSelectedOption() - 1 + currentMenu->getNumOptions()) % currentMenu->getNumOptions());
                        break;
                    case 'B': // Down arrow
                        // selectedOption = (selectedOption + 1) % numOptions;
                        currentMenu->setSelectedOption((currentMenu->getSelectedOption() + 1) % currentMenu->getNumOptions());
                        break;
                }
            }
        } else if (key == 10) {                     // Enter key
            handleSelection(currentMenu->getSelectedOption());
            if (currentMenu->getSelectedOption() == currentMenu->getNumOptions() - 1) {
                // Exit if the last option is selected
                break;
            }
        }
    }

    std::cout << "Exiting application. Goodbye!" << std::endl;
    return 0;
}

// Function to display the menu with the current selection highlighted
void displayMenu(Menu& menu) {
    std::cout << "\n===" << menu.getName() << "===\n";
    for (int i = 0; i < menu.getNumOptions(); i++) {
        if (i == menu.getSelectedOption()) {
            // Highlight the selected option with background color (yellow, bold text)
            std::cout << "\033[43;1m" << menu.getOptions()[i] << "\033[0m" << std::endl; // 43 = yellow background, 1 = bold
        } else {
            // Normal option display
            std::cout << menu.getOptions()[i] << std::endl;
        }
    }
}

// Function to handle the selected option
void handleSelection(int selectedOption) {
    switch (selectedOption) {
        case 0:
            system("~/Bachelorarbeit/Program/test.sh");
            menuCounter = 1;
            std::cout << "Option One selected!" << std::endl;
            break;
        case 1:
            menuCounter = 2;
            std::cout << "Option Two selected!" << std::endl;
            break;
        case 2:
            menuCounter = 3;
            std::cout << "Option Three selected!" << std::endl;
            break;
        case 3:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            break;
    }
    sleep(1); // Pause for a second to show the result before clearing the screen
}

// Function to clear the screen
void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen and move the cursor to the top
}

// Function to get a single key press using termios (Linux/Mac)
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);            // Get current terminal attributes
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);          // Disable canonical mode (buffered I/O) and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);   // Set new terminal attributes
    ch = getchar();                            // Read one character from stdin
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);   // Restore old terminal attributes
    return ch;
}

