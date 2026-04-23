#include <atexit.h>

typedef void (*exit_func)(void);

#define MAX_EXIT_FUNCS  64

static exit_func exit_funcs[MAX_EXIT_FUNCS];
static int num_exit_funcs = 0;

int atexit_reg(exit_func func) {
    if (num_exit_funcs >= MAX_EXIT_FUNCS) return -1;
    num_exit_funcs++;
    exit_funcs[num_exit_funcs] = func;
    return 0;
}

void atexit(void) {
    for (int i = num_exit_funcs; i > 0; i--) {
        exit_funcs[i]();
    }
}