#include <stdlib.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>

#include "headers/term.h"

struct termios term;
struct termios oldterm;

struct winsize w;

void start_raw(){
	tcgetattr(fileno(stdin), &oldterm);
	system("clear");
	term.c_iflag |= IGNBRK;
	term.c_iflag &= ~(INLCR | ICRNL | IXON | IXOFF);
	term.c_lflag &= ~(ICANON | ECHO | ECHOK | ECHOE | ECHONL | ISIG | IEXTEN);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(fileno(stdin), TCSANOW, &term);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
}

void cook(){
	tcsetattr(fileno(stdin), TCSANOW, &oldterm);
	system("clear");
}
