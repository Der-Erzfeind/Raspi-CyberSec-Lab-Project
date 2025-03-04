#include <memory>
#include <iostream>
#include <filesystem>
#include "encoder.h"
#include "Menu.h"

//std::filesystem::path p = "main.cpp";
std::string scriptPath(std::string script){
    //std::string path = std::filesystem::absolute(p).parent_path().parent_path();
    std::string path = "/home/pi/Raspi-CyberSec-Lab-Project";
    std::string scriptpath = path + "/Skripte/" + script + ".sh";
    return scriptpath;
}

std::string newPassword(std::string network){
    std::string command = "echo " + network + " | " + scriptPath("wifiNewPassword");
    return command;
}

std::string wifiMonitor(std::string state){
    std::string command = "echo " + state + " | " + scriptPath("wifiMonitor");
    return command;
}

std::string wifiLog(){
	std::string command = scriptPath("wifiLog") + " &";
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

std::string juiceShopStartStop(std::string cmd){
    std::string command = "echo " + cmd + " | " + scriptPath("juiceShop");
    return command;
}

std::string mqttStart(){
    std::string command = scriptPath("mqtt");
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
    	Menu wifiLogMenu("Wifi Log");
	Menu mqttMenu("MQTT Menu");
	Menu developmentMenu("Development Menu");

    	mainMenu.addOption("wifi", [&wifiMenu]() {wifiMenu.navigate();});
    	mainMenu.addOption("bluetooth", [&bluetoothMenu]() {bluetoothMenu.navigate();});
    	mainMenu.addOption("webapp", [&webappMenu]() {webappMenu.navigate();});
	mainMenu.addOption("development", [&developmentMenu]() {developmentMenu.navigate();});
    	mainMenu.addOption("power off");

    	wifiMenu.addOption("activate", [&wifiActivateMenu](){wifiActivateMenu.navigate();});
    	wifiMenu.addOption("deactivate", [](){system(scriptPath("wifiReset").c_str());});
    	wifiMenu.addOption("monitor", [&wifiMonitorMenu](){wifiMonitorMenu.navigate();});
    	wifiMenu.addOption("configure", [&wifiConfigureMenu](){wifiConfigureMenu.navigate();});
    	wifiMenu.addOption("status", [&wifiStatusMenu](){system(wifiStatus().c_str()); wifiStatusMenu.navigate();});
    	wifiMenu.addOption("back");

    	bluetoothMenu.addOption("Pommes");
    	bluetoothMenu.addOption("back");

    	webappMenu.addOption("Juice Shop", [&juiceShopMenu](){juiceShopMenu.navigate();});
	webappMenu.addOption("MQTT", [&mqttMenu](){mqttMenu.navigate();});
    	webappMenu.addOption("back");

	developmentMenu.addOption("SSH Hotspot", [](){system("sudo nmcli connection up SSH");});
	developmentMenu.addOption("Handy", [](){system("sudo nmcli connection up Handy");});
	developmentMenu.addOption("service restart", [](){system("sudo systemctl daemon-reload; sudo systemctl restart PiSecLab.service");});
	developmentMenu.addOption("reboot", [](){system("sudo reboot");});
	developmentMenu.addOption("back");

    	wifiActivateMenu.addOption("WEP", [](){system(wifiActivate("WEP").c_str());});
    	wifiActivateMenu.addOption("WPA", [](){system(wifiActivate("WPA").c_str());});
    	wifiActivateMenu.addOption("WPA2", [](){system(wifiActivate("WPA2").c_str());});
    	wifiActivateMenu.addOption("WPA3", [](){system(wifiActivate("WPA3").c_str());});
    	wifiActivateMenu.addOption("back");

    	wifiConfigureMenu.addOption("WEP", [](){system(newPassword("WEP").c_str());});
    	wifiConfigureMenu.addOption("WPA", [](){system(newPassword("WPA").c_str());});
    	wifiConfigureMenu.addOption("WPA2", [](){system(newPassword("WPA2").c_str());});
    	wifiConfigureMenu.addOption("WPA3", [](){system(newPassword("WPA3").c_str());});
    	wifiConfigureMenu.addOption("back");

	wifiMonitorMenu.addOption("on", [](){system(wifiMonitor("on").c_str());});
	wifiMonitorMenu.addOption("off", [](){system(wifiMonitor("off").c_str());});
	wifiMonitorMenu.addOption("view log", [&wifiLogMenu](){system(wifiLog().c_str()); wifiLogMenu.navigate();});
	wifiMonitorMenu.addOption("delete log", [](){system(wifiMonitor("del").c_str());});
    	wifiMonitorMenu.addOption("back");

	wifiLogMenu.addOption("back");
    	wifiStatusMenu.addOption("back");

    	juiceShopMenu.addOption("start", [](){system(juiceShopStartStop("on").c_str());});
    	juiceShopMenu.addOption("stop", [](){system(juiceShopStartStop("off").c_str());});
    	juiceShopMenu.addOption("back");

	mqttMenu.addOption("start conversation", [](){system(mqttStart().c_str());});
	mqttMenu.addOption("back");
    	
    	mainMenu.navigate();

    	std::cout << "\nExiting application. Goodbye!\n";
	sleep(1);
    	system(scriptPath("shutdown").c_str());
    	return 0;
}
