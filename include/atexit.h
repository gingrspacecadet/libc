#ifndef __ATEXIT_H
#define __ATEXIT_H

int atexit_reg(void (*func)(void));
void atexit(void);

#endif