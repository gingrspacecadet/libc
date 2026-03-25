#include <array.h>
#include <io.h>

ARRAY_DECLARE(char)

int main(void) {
    char_array arr = char_array_init();
    char_array_push(&arr, 'a');
    char_array_push(&arr, 'b');
    char_array_push(&arr, 'c');
    char_array_push(&arr, '\n');
    char_array_push(&arr, '\0');

    io_print(arr.data);
}