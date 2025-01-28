.PHONY:main
main: main.cpp
	g++ main.cpp -O2 -Wall -Wextra -o main.out
	./main.out

.PHONY: uart
uart: uart.cpp
	g++ uart.cpp -O2 -Wall -Wextra uart.out
	./uart.out

.PHONY: encoder
encoder: encoder.cpp
	g++ encoder.cpp -O2 -Wall -Wextra -lpigpio -o encoder.out 
	./encoder.out

.PHONY:test
test: test.cpp
	g++ test.cpp -O2 -Wall -Wextra -lpigpio -o test.out
	./test.out

.PHONY: clean
clean:
	rm a.out
