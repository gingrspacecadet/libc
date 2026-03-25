#include <format.h>
#include <io.h>

int main() {
    cstring name = "World";
    cstring greeting = format("Hello, %s!", name);
    io_print(greeting);
    return 0;
}