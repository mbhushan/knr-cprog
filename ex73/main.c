/* Revise minprintf to handle more of the other facilities of printf */

#include <stdarg.h>
#include <stdio.h>

/* minprintf: minimal printf with variable arguments lists */

void minprintf(char *fmt, ...);

int main() {
    minprintf("%d %c: %s\n", 93, 'A', "Hello, World!\n");
    return 0;
}

void minprintf(char *fmt, ...) {
    va_list ap; /* points to each variable argument in turn */
    char *p, *sval;
    int ival;
    double dval;
    unsigned uval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p=fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'c':
                uval = va_arg(ap, unsigned int);
                putchar(uval);
                break;
            case 'f':
            case 'g':
                dval = va_arg(ap, double );
                printf("%f", dval);
                break;
            case 'x':
            case 'X':
                uval = va_arg(ap, unsigned int);
                printf("%x", uval);
                break;
            case 's':
                for (sval= va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap); /* cleanup when done! */
}
