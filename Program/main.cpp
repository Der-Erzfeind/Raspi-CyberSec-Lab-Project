#include "Menu.h"
#include <memory>
#include <iostream>

std::string scriptPath(std::string script){
    std::string path = "~/BA/Skripte/" + script + ".sh";
    return path;
}
std::string newPassword(std::string network){
    std::string command = "echo " + network + " | " + scriptPath("newPassword");
    return command;
}

void test(){}
auto testptr = test;

int main() {
    Menu mainMenu("Main Menu");
    Menu wifiMenu("Wifi Menu");
    Menu bluetoothMenu("Bluetooth Menu");
    Menu webappMenu("Webapp Menu");
    Menu wepMenu("WEP Menu");
    Menu wpaMenu("WPA Menu");
    Menu wpa2Menu("WPA2 Menu");
    Menu wpa3Menu("WPA3 Menu");
    Menu juiceShopMenu("Juice Shop Menu");

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

    webappMenu.addOption("Juice Shop", [&juiceShopMenu](){juiceShopMenu.navigate();});
    webappMenu.addOption("Back");

    wepMenu.addOption("activate", [](){system(scriptPath("WEP").c_str());});
    wepMenu.addOption("deactivate", [](){system(scriptPath("resetWifi").c_str());});
    wepMenu.addOption("monitor", testptr);
    wepMenu.addOption("configure", [](){system(newPassword("WEP").c_str());});
    wepMenu.addOption("status", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wepMenu.addOption("Back");

    wpaMenu.addOption("activate", [](){system(scriptPath("WPA").c_str());});
    wpaMenu.addOption("deactivate", [](){system(scriptPath("resetWifi").c_str());});
    wpaMenu.addOption("monitor");
    wpaMenu.addOption("configure", [](){system(newPassword("WPA").c_str());});
    wpaMenu.addOption("status", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpaMenu.addOption("Back");

    wpa2Menu.addOption("activate", [](){system(scriptPath("WPA2").c_str());});
    wpa2Menu.addOption("deactivate", [](){system(scriptPath("resetWifi").c_str());});
    wpa2Menu.addOption("monitor");
    wpa2Menu.addOption("configure", [](){system(newPassword("WPA2").c_str());});
    wpa2Menu.addOption("status", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpa2Menu.addOption("Back");

    wpa3Menu.addOption("activate", [](){system(scriptPath("WPA3").c_str());});
    wpa3Menu.addOption("deactivate", [](){system(scriptPath("resetWifi").c_str());});
    wpa3Menu.addOption("monitor");
    wpa3Menu.addOption("configure", [](){system(newPassword("WPA3").c_str());});
    wpa3Menu.addOption("status", [](){system("~/Bachelorarbeit/Program/test.sh");});
    wpa3Menu.addOption("Back");

    juiceShopMenu.addOption("start", [](){system(scriptPath("juiceShopStart").c_str());});
    juiceShopMenu.addOption("stop", [](){system(scriptPath("juiceShopStop").c_str());});
    juiceShopMenu.addOption("Back");
    

    mainMenu.navigate();

    std::cout << "\nExiting application. Goodbye!\n";
    return 0;
}
