#include "Menu.h"
#include "actions.h"
#include <memory>

// Function prototypes for actions
void optionOneAction();
void optionTwoAction();
void optionThreeAction();
void submenuAction();

int main() {
    // Create the main menu
    Menu mainMenu("Main Menu");

    // Create submenus
    Menu wifiMenu("Wifi Menu", &mainMenu);
    wifiMenu.addOption("WEP", [](){
        system("~/Bachelorarbeit/Program/test.sh");
    });
    wifiMenu.addOption("WPA", [](){
        system("~/Bachelorarbeit/Program/test2.sh");
    });
    wifiMenu.addOption("Back");

    // Add options to the main menu
    mainMenu.addOption("Option One", optionOneAction);
    mainMenu.addOption("Option Two", optionTwoAction);
    mainMenu.addOption("Option Three", optionThreeAction);
    mainMenu.addOption("Wifi", [&wifiMenu]() {
        wifiMenu.navigate();
    });
    mainMenu.addOption("Exit");

    // Start navigating the main menu
    mainMenu.navigate();

    std::cout << "\nExiting application. Goodbye!\n";
    return 0;
}

// Definitions of action functions
void optionOneAction() {
    std::cout << "Option One selected!";
}

void optionTwoAction() {
    std::cout << "Option Two selected!";
}

void optionThreeAction() {
    std::cout << "Option Three selected!";
}
