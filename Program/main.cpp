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
    Menu wifiActivateMenu("Activate Wifi");
    Menu wifiConfigureMenu("Configure Wifi");
    Menu wifiMonitorMenu("Wifi Monitor");
    Menu juiceShopMenu("Juice Shop Menu");

    mainMenu.addOption("Wifi", [&wifiMenu]() {wifiMenu.navigate();});
    mainMenu.addOption("Bluetooth", [&bluetoothMenu]() {bluetoothMenu.navigate();});
    mainMenu.addOption("Webapp", [&webappMenu]() {webappMenu.navigate();});
    mainMenu.addOption("Exit");

    wifiMenu.addOption("activate", [&wifiActivateMenu](){wifiActivateMenu.navigate();});
    wifiMenu.addOption("deactivate", [](){system(scriptPath("resetWifi").c_str());});
    wifiMenu.addOption("monitor", [&wifiMonitorMenu](){system("sudo iw dev wlan1 event -T -f"); wifiMonitorMenu.navigate();});
    wifiMenu.addOption("configure", [&wifiConfigureMenu](){wifiConfigureMenu.navigate();});
    wifiMenu.addOption("status", [](){system("sudo nmcli dev wifi show-password");});
    wifiMenu.addOption("Back");

    bluetoothMenu.addOption("Pommes");
    bluetoothMenu.addOption("Back");

    webappMenu.addOption("Juice Shop", [&juiceShopMenu](){juiceShopMenu.navigate();});
    webappMenu.addOption("Back");

    wifiActivateMenu.addOption("WEP", [](){system(scriptPath("WEP").c_str());});
    wifiActivateMenu.addOption("WPA", [](){system(scriptPath("WPA").c_str());});
    wifiActivateMenu.addOption("WPA2", [](){system(scriptPath("WPA2").c_str());});
    wifiActivateMenu.addOption("WPA3", [](){system(scriptPath("WPA3").c_str());});
    wifiActivateMenu.addOption("Back");

    wifiConfigureMenu.addOption("WEP", [](){system(newPassword("WEP").c_str());});
    wifiConfigureMenu.addOption("WPA", [](){system(newPassword("WPA").c_str());});
    wifiConfigureMenu.addOption("WPA2", [](){system(newPassword("WPA2").c_str());});
    wifiConfigureMenu.addOption("WPA3", [](){system(newPassword("WPA3").c_str());});
    wifiConfigureMenu.addOption("Back");

    wifiMonitorMenu.addOption("Stop", [](){system("sudo pgrep -f \"iw event -T\"");});
    wifiMonitorMenu.addOption("Back");

    juiceShopMenu.addOption("start", [](){system(scriptPath("juiceShopStart").c_str());});
    juiceShopMenu.addOption("stop", [](){system(scriptPath("juiceShopStop").c_str());});
    juiceShopMenu.addOption("Back");
    

    mainMenu.navigate();

    std::cout << "\nExiting application. Goodbye!\n";
    return 0;
}
