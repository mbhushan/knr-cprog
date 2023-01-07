/* Write a private version of scanf analogous to minprintf from the previous section. */

#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...);

int main() {
    int i;
    char s[100];
    double d = 0.0;
    minscanf("%d %g %s", &i, &d, s);

    printf("\n%d %g %s\n", i, d, s);

    return 0;
}

/* minscanf: minimal scanf with variable argument list - only scans integers */
void minscanf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int *ival;
    double *dval;
    unsigned *uval;

    va_start(ap, fmt);

    for (p=fmt; *p; p++) {
        /* skips chars that aint format conversions */
        if (*p != '%')
            continue;

        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int *);
                scanf("%d", ival);
                break;
            case 'u':
                uval = va_arg(ap, unsigned *);
                scanf("%u", uval);
                break;
            case 'g':
                dval = va_arg(ap, double *);
                scanf("%g", dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                scanf("%s", sval);
                break;
            default:
                getchar();
                break;
        }
    }
}
