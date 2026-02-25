#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static bool print(const char* data, size_t length)
{
    for (size_t i = 0; i < length; i++) {
        if (putchar(data[i]) == EOF)
            return false;
    }
    return true;
}

int printf(const char* restrict format, ...)
{
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {

        size_t maxrem = INT_MAX - written;

        /* ---------- NORMAL CHARACTER ---------- */
        if (*format != '%') {

            if (!maxrem)
                return -1;

            if (!print(format, 1))
                return -1;

            written++;
            format++;
            continue;
        }

        /* ---------- FORMAT SPECIFIER ---------- */
        // if it is %s, the format currently points t0 '%' and then using ++ it now points to 's'
        format++;  // skip '%'

        //if %\0 (eg:"hello%")
        if (*format == '\0')
            break;

        /* ---------- ESCAPED PERCENT ---------- */
        if (*format == '%') {

            if (!maxrem)
                return -1;

            if (!print("%", 1))
                return -1;

            written++;
            format++;
        }

        /* ---------- %c ---------- */
        else if (*format == 'c') {

            format++;

            char c = (char) va_arg(parameters, int);

            if (!maxrem)
                return -1;

            if (!print(&c, 1))
                return -1;

            written++;
        }

        /* ---------- %s ---------- */
        else if (*format == 's') {

            format++;

            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);

            if (maxrem < len)
                return -1;

            if (!print(str, len))
                return -1;

            written += len;
        }

        /* ---------- %d ---------- */
        else if (*format == 'd') {

            format++;

            int value = va_arg(parameters, int);
            unsigned int uvalue;

            if (value < 0) {
                if (!print("-", 1))
                    return -1;
                written++;
                uvalue = -(unsigned int)value;  // safe for INT_MIN
            } else {
                uvalue = value;
            }

            char buffer[12];
            size_t i = 0;

            if (uvalue == 0) {
                buffer[i++] = '0';
            } else {
                while (uvalue > 0) {
                    buffer[i++] = '0' + (uvalue % 10);
                    uvalue /= 10;
                }
            }

            if (maxrem < i)
                return -1;

            while (i > 0) {
                if (!print(&buffer[--i], 1))
                    return -1;
                written++;
            }
        }

        /* ---------- UNKNOWN SPECIFIER ---------- */
        else {
            // Print it literally: %x becomes %x
            if (!maxrem)
                return -1;

            if (!print("%", 1))
                return -1;

            written++;
        }
    }

    va_end(parameters);
    return written;
}