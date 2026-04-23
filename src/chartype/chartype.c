#include <chartype.h>

bool isdigit(char c) {
    return c >= '0' && c <= '9';
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
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isalnum(char c) {
    return isalpha(c) || isdigit(c);
}