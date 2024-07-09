#include <stdio.h>
#include <unistd.h>

#include "headers/main.h"
#include "headers/term.h"
#include "headers/print.h"

//Cursor curs={100,100};

size_t textLen;
int lineCount;

int print_cursor(Cursor curs){
	char buf[20];
	if (isEdit==0) {
		char escCode[]="\033[0 q";
		write(STDOUT_FILENO, escCode, strlen(escCode));
	}else {
		char escCode[]="\033[6 q";
		write(STDOUT_FILENO, escCode, strlen(escCode));
	}
	int len = snprintf(buf, sizeof(buf), "\033[%d;%dH", curs.y, curs.x);
	write(STDOUT_FILENO, buf, len);
	return 0;
}

int print_tilde(){
	for (int i=0; i<w.ws_col; i++) {
		write(fileno(stdout), "~\r\n", 3);
	}
	return 0;
}

int print_text( char *text, int startLine ){
	int screenW=w.ws_row-1;
	int lc=0;
	write(STDOUT_FILENO, "\033[0;0H", sizeof("\033[0;0H"));
	if (textLen==lineCount) return 0;
	for (size_t i=0; i<=textLen; i++) {
		if (textFile[i]=='\n' || textFile[i]=='\0') {
			lc++;
		}
		if (lc>=startLine && lc<=screenW+startLine) {
			switch (text[i]) {
				case '\n':
					write(STDOUT_FILENO, "\r\n\33[2K\r", 7);
					break;
				default:
					write(STDOUT_FILENO, &text[i], sizeof(char));
					break;
			}
		}
	}
	return 0;
}

int refresh_screen(){
	write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);
	return 0;
}
