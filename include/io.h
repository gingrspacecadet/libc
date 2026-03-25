#ifndef __IO_H
#define __IO_H

#include <string.h>
#include <cstring.h>

#define io_print(x) _Generic((x), \
    string: io_print_string, \
    cstring: io_print_cstring, \
    default: io_print_cstring \
)(x)

int io_print_string(string str);
int io_print_cstring(cstring str);

#endif