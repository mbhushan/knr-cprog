#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float FtoC(float f);

int main() {
    float f,c;
    for (f=LOWER; f<=UPPER; f+=STEP) {
        c = FtoC(f);
        printf("%.2f F = %.2f C\n", f, c);
    }`
    return 0;
}

/** converts fahrenheit to celsius */

float FtoC(float f) {
    float c;
    c = (5.0/9.0) * (f-32);
    return c;
}
