/*
 * serial_usb_simple - Demo that communicates over USB using serial I/O
 * from a Raspberry Pi to an Arduino.
 *
 * To show that it work, this writes a '1' to the Arduino which then 
 * blinks the builtin LED on and off. The Arduino also sends back an 'A'
 * to acknowledge that it got the message. This does a read() to get
 * the 'A', demonstrating that reading also works. Two seconds later,
 * this writes a '0' to the Arduino which then stops the blinking.
 * The Arduino again sends back an 'A' to acknowledge that it got the
 * message and this reads the 'A'.
 *
 * This was tested between a Raspberry Pi 3B (running Raspbian) and
 * an Arduino Mega 2560 and also between an NVIDIA Jetson TX1 (running 
 * Ubuntu) and the same Arduino.
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for the serial I/O
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <linux/serial.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

int open_serial_port(char *name)
{
	int fd, bits;
	struct termios term;
	struct serial_struct kernel_serial_settings;

	if ((fd = open(name, O_RDWR | O_NONBLOCK | O_NOCTTY )) == -1) {
		fprintf(stderr, "open(%s) failed: %s\n", name, strerror(errno));
		return -1;
	}

	/* 
	 * Reset the Arduino's line. This is key to getting the write to work.
	 * Without it, the first few writes don't work.
	 * Clear DTR, wait one second, flush input, then set DTR.
	 * Without this, the first write fails.
 	*/
	if (ioctl(fd, TIOCMGET, &bits) < 0) {
		close(fd);
		perror("ioctl(TCIOMGET)");
		return -1;
	}
	bits &= ~(TIOCM_DTR | TIOCM_RTS);
	if (ioctl(fd, TIOCMSET, &bits) < 0) {
		close(fd);
		perror("ioctl(TIOCMSET)");
		return -1;
	}
	sleep(1);
	tcflush(fd, TCIFLUSH);
	bits &= TIOCM_DTR;
	if (ioctl(fd, TIOCMSET, &bits) < 0) {
		close(fd);
		perror("ioctl(TIOCMSET)");
		return -1;
	}

	memset(&term, 0, sizeof(term));
	term.c_iflag = IGNBRK | IGNPAR;
	term.c_cflag = CS8 | CREAD | HUPCL | CLOCAL;
	cfsetospeed(&term, B115200);
	cfsetispeed(&term, B115200);
	if (tcsetattr(fd, TCSANOW, &term) < 0) {
		perror("tcsetattr()");
		return -1;
	}
	if (ioctl(fd, TIOCGSERIAL, &kernel_serial_settings) == 0) {
		kernel_serial_settings.flags |= ASYNC_LOW_LATENCY;
		ioctl(fd, TIOCSSERIAL, &kernel_serial_settings);
	}
	tcflush(fd, TCIFLUSH);

	return fd;
}

int read_from_serial(int fd, char *buf)
{
	int n;

	while (1) {
		if ((n = read(fd, buf, 1)) == -1) {
			if (errno != EAGAIN) {
				fprintf(stderr, "read() failed: (%d) %s\n", errno, strerror(errno));
				return -1;
			}
			// errno == EAGAIN, loop around and read again
		} else {
			if (n == 1) {
				return n; // stop reading
			}
			// read 0 bytes, loop around an read again
		}
	}
}

int main(int argc, char **argv)
{
	int fd;
	ssize_t n;
	char buf[10];

	if ((fd = open_serial_port("/dev/ttyACM0")) == -1) {
		exit(EXIT_FAILURE);
	}

	while (1) {

		printf("Telling the Arduino to start blinking...\n");

		if ((n = write(fd, "1", 1)) == -1) {
			fprintf(stderr, "write() failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		// read to get the acknowledgement from the Arduino

		if (read_from_serial(fd, buf) == -1) {
			exit(EXIT_FAILURE);
		}
		buf[1] = '\0';
		printf("Arduino sent back '%s'\n", buf);

		sleep(2);

		printf("Telling the Arduino to stop blinking...\n");

		if ((n = write(fd, "0", 1)) == -1) {
			fprintf(stderr, "write() failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		// read to get the acknowledgement from the Arduino

		if (read_from_serial(fd, buf) == -1) {
			exit(EXIT_FAILURE);
		}
		buf[1] = '\0';
		printf("Arduino sent back '%s'\n", buf);

		sleep(2);
	}

	return EXIT_SUCCESS;
}
