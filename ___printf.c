#include <stdio.h>
#include <stdarg.h>

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int length = vsnprintf(NULL, 0, format, args);
    char buffer[length + 1];
    vsnprintf(buffer, length + 1, format, args);

    int count = 0;
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '%') {
            i++;
            switch (buffer[i]) {
                case 'c':
                    count += putchar(va_arg(args, int));
                    break;
                case 's':
                    count += printf("%s", va_arg(args, char *));
                    break;
                case '%':
                    count += putchar('%');
                    break;
                default:
                    putchar('%');
                    putchar(buffer[i]);
                    count += 2;
                    break;
            }
        }
        else {
            putchar(buffer[i]);
            count++;
        }
    }

    va_end(args);
    return count;
}

