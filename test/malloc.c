#include <malloc.h>
#include <io.h>

int main(void) {
    char *data = malloc(5);
    data[0] = 'a';
    data[1] = 'b';
    data[2] = 'c';
    data[3] = '\n';
    data[4] = 0;

    io_print(data);
}