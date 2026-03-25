#include <format.h>

#include <array.h>

string format_string(string fmt, ...) {
    string out = {0};

    while (1) {
        
    }
}

cstring format_cstring(cstring fmt, ...) {
    if (!fmt) {
        return NULL;
    }

    cstring out = NULL;
    cstring p = fmt;

    while (*p) {
        if (*p == '%') {
            p++;
            if (*p == 's') {
                va_list args;
                va_start(args, fmt);
                cstring str_arg = va_arg(args, cstring);
                va_end(args);

                cstring_append(&out, str_arg);
            } else if (*p == 'd') {
                va_list args;
                va_start(args, fmt);
                int int_arg = va_arg(args, int);
                va_end(args);

                while (int_arg > 0) {
                    char digit = '0' + (int_arg % 10);
                    cstring_append(&out, (cstring)&digit);
                    int_arg /= 10;
                }
            } else {
                cstring_append(&out, "%");
                cstring_append(&out, p);
            }
        } else {
            cstring_append(&out, p);
        }
        p++;
    }
    return out;
}