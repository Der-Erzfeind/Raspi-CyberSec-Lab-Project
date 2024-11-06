#include "Menu.h"
#include "actions.h"
#include <memory>
#include <iostream>

std::string scriptPath(std::string script){
    std::string path = "~/Bachelorarbeit/Program/" + script + ".sh";
    return path;
}

int main() {
    Menu mainMenu("Main Menu");
    Menu wifiMenu("Wifi Menu", &mainMenu);
    Menu bluetoothMenu("Bluetooth Menu", &mainMenu);
    Menu webappMenu("Webapp Menu", &mainMenu);
    Menu wepMenu("WEP Menu", &wifiMenu);
    Menu wpaMenu("WPA Menu", &wifiMenu);
    Menu wpa2Menu("WPA2 Menu", &wifiMenu);
    Menu wpa3Menu("WPA3 Menu", &wifiMenu);

    mainMenu.addOption("Wifi", [&wifiMenu]() {wifiMenu.navigate();});
    mainMenu.addOption("Bluetooth", [&bluetoothMenu]() {bluetoothMenu.navigate();});
    mainMenu.addOption("Webapp", [&webappMenu]() {webappMenu.navigate();});
    mainMenu.addOption("Exit");

    wifiMenu.addOption("WEP", [&wepMenu](){wepMenu.navigate();});
    wifiMenu.addOption("WPA", [&wpaMenu](){wpaMenu.navigate();});
    wifiMenu.addOption("WPA2",[&wpa2Menu](){wpa2Menu.navigate();});
    wifiMenu.addOption("WPA3",[&wpa3Menu](){wpa3Menu.navigate();});
    wifiMenu.addOption("Back");

    bluetoothMenu.addOption("Pommes");
    bluetoothMenu.addOption("Back");

    webappMenu.addOption("Juice Shop");
    webappMenu.addOption("Back");

    wepMenu.addOption("activate", [](){system(scriptPath("WEP").c_str());});
    wepMenu.addOption("deactivate", [](){system("~/Bachelorarbeit/Program/test.sh");sleep(1);});
    wepMenu.addOption("monitor");
    wepMenu.addOption("configure", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wepMenu.addOption("status", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wepMenu.addOption("Back");

    wpaMenu.addOption("activate", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpaMenu.addOption("deactivate", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpaMenu.addOption("monitor");
    wpaMenu.addOption("configure", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpaMenu.addOption("status", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpaMenu.addOption("Back");

    wpa2Menu.addOption("activate", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpa2Menu.addOption("deactivate", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpa2Menu.addOption("monitor");
    wpa2Menu.addOption("configure", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpa2Menu.addOption("status", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpa2Menu.addOption("Back");

    wpa3Menu.addOption("activate", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpa3Menu.addOption("deactivate", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpa3Menu.addOption("monitor");
    wpa3Menu.addOption("configure", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpa3Menu.addOption("status", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpa3Menu.addOption("Back");


    mainMenu.navigate();

    std::cout << "\nExiting application. Goodbye!\n";
    return 0;
}