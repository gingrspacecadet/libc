#include <chartype.h>

bool isdigit(char c) {
    if (c >= '0' && c <= '9') return true;
    else return false;
}

bool isspace(char c) {
    switch (c) {
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            return true;
        default:
            return false;
    }
}

bool isalpha(char c) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return true;
    else return false;
}

bool isalnum(char c) {
    return isalpha(c) || isdigit(c);
}