#ifndef __FORMAT_H
#define __FORMAT_H

#include <varargs.h>
#include <generic.h>
#include <string.h>
#include <cstring.h>

#define format(fmt, ...) generic((fmt), \
    string: format_string, \
    cstring: format_cstring, \
    default: format_cstring \
)(fmt, __VA_ARGS__)

string format_string(string fmt, ...);
cstring format_cstring(cstring fmt, ...);

#endif