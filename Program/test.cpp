#include <iostream>
#include <vector>
#include <termios.h>
#include <unistd.h>

// Function prototypes
void displayMenu(const std::vector<std::string>& options, int selectedOption);
void clearScreen();
void handleSelection(int selectedOption);
int getch();

int main() {
    std::vector<std::string> options = {
        "WIFI",
        "Bluetooth",
        "Webapps",
        "Power Off"
    };
    
    int selectedOption = 0; // Tracks the currently selected option
    const int numOptions = options.size();

    while (true) {
        clearScreen();
        displayMenu(options, selectedOption);

        int key = getch();

        if (key == 27) { // Escape sequence for arrow keys starts with 27
            if (getch() == 91) { // '[' after the escape sequence
                switch (getch()) {
                    case 'A': // Up arrow
                        selectedOption = (selectedOption - 1 + numOptions) % numOptions;
                        break;
                    case 'B': // Down arrow
                        selectedOption = (selectedOption + 1) % numOptions;
                        break;
                }
            }
        } else if (key == 10) { // Enter key (ASCII code 10)
            handleSelection(selectedOption);
            if (selectedOption == numOptions - 1) {
                // Exit if the last option is selected
                break;
            }
        }
    }

    std::cout << "Exiting application. Goodbye!" << std::endl;
    return 0;
}

// Function to display the menu with the current selection highlighted
void displayMenu(const std::vector<std::string>& options, int selectedOption) {
    std::cout << "\n=== Menu ===\n";
    for (int i = 0; i < options.size(); i++) {
        if (i == selectedOption) {
            // Highlight the selected option with background color (yellow, bold text)
            std::cout << "\033[43;1m" << options[i] << "\033[0m" << std::endl; // 43 = yellow background, 1 = bold
        } else {
            // Normal option display
            std::cout << options[i] << std::endl;
        }
    }
}

// Function to handle the selected option
void handleSelection(int selectedOption) {
    switch (selectedOption) {
        case 0:
            std::cout << "Option One selected!" << std::endl;
            break;
        case 1:
            std::cout << "Option Two selected!" << std::endl;
            break;
        case 2:
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

