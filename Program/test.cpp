#include <iostream>
#include <mosquitto.h>

const char* BROKER_ADDRESS = "localhost";
const int BROKER_PORT = 1883;
const char* TOPIC = "topsecret";

void on_message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* message) {
    std::cout << "Received message on topic " << message->topic << ": " << static_cast<char*>(message->payload) << std::endl;
    
    mosquitto_publish(mosq, nullptr, TOPIC, strlen(MESSAGE), MESSAGE, QOS, false);
     
}

int main() {
    mosquitto_lib_init();

    mosquitto* mosq = mosquitto_new("subscriber-client", true, nullptr);
    if (!mosq) {
        std::cerr << "Failed to create Mosquitto client!" << std::endl;
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

    const char * MESSAGE = "test";
    mosquitto_publish(mosq, nullptr, TOPIC, strlen(MESSAGE), MESSAGE, QOS, false);

    mosquitto_loop_forever(mosq, -1, 1);  // Keep the client running

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}

