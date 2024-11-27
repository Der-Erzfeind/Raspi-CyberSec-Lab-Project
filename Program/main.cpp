#include "Menu.h"
#include <memory>
#include <iostream>

std::string scriptPath(std::string script){
    std::string path = "~/BA/Skripte/" + script + ".sh";
    return path;
}

std::string newPassword(std::string network){
    std::string command = "echo " + network + " | " + scriptPath("wifiNewPassword");
    return command;
}

std::string wifiMonitor(std::string state){
    std::string command = "echo " + state + " | " + scriptPath("wifiMonitor");
    return command;
}

std::string wifiActivate(std::string connection){
    std::string command = "echo " + connection + " | " + scriptPath("wifiActivate");
    return command;
}

std::string wifiStatus(){
	std::string command = scriptPath("wifiStatus") + " &";
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
    Menu wifiStatusMenu("Wifi Status");
    Menu juiceShopMenu("Juice Shop Menu");

    mainMenu.addOption("Wifi", [&wifiMenu]() {wifiMenu.navigate();});
    mainMenu.addOption("Bluetooth", [&bluetoothMenu]() {bluetoothMenu.navigate();});
    mainMenu.addOption("Webapp", [&webappMenu]() {webappMenu.navigate();});
    mainMenu.addOption("Exit");

    wifiMenu.addOption("activate", [&wifiActivateMenu](){wifiActivateMenu.navigate();});
    wifiMenu.addOption("deactivate", [](){system(scriptPath("wifiReset").c_str());});
    wifiMenu.addOption("monitor", [&wifiMonitorMenu](){system(wifiMonitor("on").c_str()); wifiMonitorMenu.navigate();});
    wifiMenu.addOption("configure", [&wifiConfigureMenu](){wifiConfigureMenu.navigate();});
    wifiMenu.addOption("status", [&wifiStatusMenu](){system(wifiStatus().c_str()); wifiStatusMenu.navigate();});
    wifiMenu.addOption("Back");

    bluetoothMenu.addOption("Pommes");
    bluetoothMenu.addOption("Back");

    webappMenu.addOption("Juice Shop", [&juiceShopMenu](){juiceShopMenu.navigate();});
    webappMenu.addOption("Back");

    wifiActivateMenu.addOption("WEP", [](){system(wifiActivate("WEP").c_str());});
    wifiActivateMenu.addOption("WPA", [](){system(wifiActivate("WPA").c_str());});
    wifiActivateMenu.addOption("WPA2", [](){system(wifiActivate("WPA2").c_str());});
    wifiActivateMenu.addOption("WPA3", [](){system(wifiActivate("WPA3").c_str());});
    wifiActivateMenu.addOption("Back");

    wifiConfigureMenu.addOption("WEP", [](){system(newPassword("WEP").c_str());});
    wifiConfigureMenu.addOption("WPA", [](){system(newPassword("WPA").c_str());});
    wifiConfigureMenu.addOption("WPA2", [](){system(newPassword("WPA2").c_str());});
    wifiConfigureMenu.addOption("WPA3", [](){system(newPassword("WPA3").c_str());});
    wifiConfigureMenu.addOption("Back");

    wifiMonitorMenu.addOption("Back", [](){system(wifiMonitor("off").c_str());});

    wifiStatusMenu.addOption("Back");

    juiceShopMenu.addOption("start", [](){system(scriptPath("juiceShopStart").c_str());});
    juiceShopMenu.addOption("stop", [](){system(scriptPath("juiceShopStop").c_str());});
    juiceShopMenu.addOption("Back");
    

    mainMenu.navigate();

    std::cout << "\nExiting application. Goodbye!\n";
    system(scriptPath("shutdown").c_str());
    return 0;
}
