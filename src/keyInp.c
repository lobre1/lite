#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "headers/keyInp.h"
#include "headers/main.h"
#include "headers/print.h"
#include "headers/term.h"

int textSize;

int process_key(){
	char c=read_key();
	if (isEdit==0) {
		switch (c) {
			case 'q':
				end();
				cook();
				exit(0);
				break;
			case 'i':
				isEdit=1; 
				return 0;
				break;
			case 'j':
				if (curs.y==w.ws_row) {scrollNum++;}
				else {curs.y++;}
				break;
			case 'k':
				if (curs.y==0) {
					if (scrollNum==0) break;
					scrollNum--;
				}
				else {curs.y--;}
				break;
		}
	}
	if (isEdit==1) {
		switch (c) {
			case 27:isEdit=0; break;
			default:
				textFile=realloc(textFile, textSize+=sizeof(char));
				strcat(textFile, &c);
				write(STDOUT_FILENO, &c, sizeof(char));
				break;
		}
	}
	return 0;
}

int read_key(){
  char c;
  while (read(STDIN_FILENO, &c, 1) != 1);
	return c;
}
