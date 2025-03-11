.PHONY:main
main: main.cpp
	g++ main.cpp -O2 -Wall -Wextra -o main.out -lpigpio

.PHONY: mqtt
mqtt: mqtt.cpp
	g++ mqtt.cpp -O2 -Wall -Wextra -o mqtt.out -lmosquitto

.PHONY: encoder
encoder: encoder.cpp
	g++ encoder.cpp -O2 -Wall -Wextra -lpigpio -o encoder.out 

.PHONY:test
test: test.cpp
	g++ test.cpp -O2 -Wall -Wextra -o test.out 

.PHONY:all
all: main encoder mqtt

.PHONY: clean
clean:
	rm a.out
