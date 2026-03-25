#ifndef __IO_H
#define __IO_H

#include <types.h>
#include <string.h>
#include <cstring.h>
#include <generic.h>

#define io_print(x) generic((x), \
    hexulong: io_print_hexulong, \
    string: io_print_string, \
    cstring: io_print_cstring, \
    default: io_print_cstring \
)(x)

int io_print_string(string str);
int io_print_cstring(cstring str);
int io_print_hexulong(hexulong num);

#endif
