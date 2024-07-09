#ifndef TERM_H
#include <sys/ioctl.h>

void start_raw();
void cook();
void term_dimen();

extern struct winsize w;

#endif
