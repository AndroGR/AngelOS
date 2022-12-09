#include <String.h>

size_t strlen(const char *data) {
        size_t len = 0;
        while (*data != '\0') len++;
        return len;
}