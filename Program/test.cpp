#include <iostream>
#include <mosquitto.h>
#include <fstream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <vector>

const char* BROKER_ADDRESS = "localhost";
const int BROKER_PORT = 1883;
const char* TOPIC = "topsecret";
const char * MESSAGE = "test";
const int QOS = 1;
const char * USERNAME = "test";
const char * PASSWORD = "test";
std::vector<std::string> alan;
std::string buffer = "";
int lines, c=0;

void on_message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* message) {
    std::cout << "Received message on topic " << message->topic << ": " << static_cast<char*>(message->payload) << std::endl;
    	sleep(5); 
    	mosquitto_publish(mosq, nullptr, TOPIC, strlen(alan[c].c_str()), alan[c].c_str(), QOS, false);

    if(c < (lines-1))
	c++;
    else
	c=0;
}

int main() {
    std::ofstream file("../mqtt/Alan.txt", std::ios::in);
	if(!file.is_open()){
		std::cerr << std::endl << "error opening file" << std::endl;
		return 1;
	}
	else{
		while(1){
			std::getline(file, buffer);
			if(buffer != EOF)
				alan.push_back(buffer);	
			else
				break;
		}
		lines = alan.size();
    		file.close();
	}

    mosquitto_lib_init();

    mosquitto* mosq = mosquitto_new("subscriber-client", true, nullptr);
    if (!mosq) {
        std::cerr << "Failed to create Mosquitto client!" << std::endl;
        return 1;
    }

    if (mosquitto_username_pw_set(mosq, USERNAME, PASSWORD) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to set username and password!" << std::endl;
        mosquitto_destroy(mosq);
        return 1;
    }

    mosquitto_message_callback_set(mosq, on_message);

    if (mosquitto_connect(mosq, BROKER_ADDRESS, BROKER_PORT, 60) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to connect to broker!" << std::endl;
        mosquitto_destroy(mosq);
        return 1;
    }

    mosquitto_subscribe(mosq, nullptr, TOPIC, 1);
    std::cout << "Subscribed to topic: " << TOPIC << std::endl;

    mosquitto_publish(mosq, nullptr, TOPIC, strlen(MESSAGE), MESSAGE, QOS, false);

    mosquitto_loop_forever(mosq, -1, 1);  // Keep the client running

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}

