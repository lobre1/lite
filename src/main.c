#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "headers/main.h"
#include "headers/term.h"
#include "headers/print.h"
#include "headers/keyInp.h"

Cursor curs={0, 0};

char *textFile;

int isEdit=0;
int test=0;
int scrollNum; 	

int main( int argc, char *argv[] ){
	FILE *fp=fopen(argv[1], "r+");
	textFile=malloc(1);
	textFile[0]='\0';
	if (fp==NULL) {
		perror("Fopen");
		return 1;
	}
	int c;
	textLen=0;
	while ((c=getc(fp))!=EOF) {
		textFile[textLen]=c;
		if (c=='\n') {lineCount++;}
		textLen+=1;
		textFile=realloc(textFile, textLen+1);
	}
	textFile[textLen]='\0';
	fclose(fp);
	textLen=strlen(textFile);
	start_raw();
	while (1) {
		refresh_screen();
		print_tilde();
		print_text(textFile, scrollNum);
		print_cursor(curs);
		process_key();
		if (test<=0) {
			test=0;
		}
	}
	cook();
}


int end(){
	free(textFile);
	return 0;
}
