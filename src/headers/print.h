#ifndef PRINT_H

typedef struct{
	int x,y;
}Cursor;

extern Cursor curs;

int print_cursor(Cursor curs);
int print_tilde();
int print_text( char *text, int startLine );
int refresh_screen();

#endif
