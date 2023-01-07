/**
 Exercise 2-3. Write the function htoi(s), which converts a string of hexadecimal digits
 (including an optional 0x or 0X) into its equivalent integer value.
 The allowable digits are 0 through 9, a through f, and A through F.
 */

#include <stdio.h>
#include <math.h>

int hexalpha_to_int(int ch) {
    char hexalpha[] = "aAbBcCdDeEfF";
    int i=0, ans=0;
    for (i=0; ans==0 && hexalpha[i] != '\0'; i++) {
        if (hexalpha[i] == ch) ans = 10 + i/2;
    }
    return ans;
}

unsigned int htoi(const char s[]) {
    unsigned int ans = 0;
    int i=0, j=0, valid=1, hexit=0, len=0;

    if (s[i] == '0') {
        ++i;
        if (s[i] == 'x' || s[i] == 'X') ++i;
    }
    j = i;
    while (s[j++] != '\0') ++len;

    while (valid && s[i] != '\0') {
        if (s[i] >= '0' && s[i] <= '9') {
            ans = ans + (s[i] - '0') * (int)pow(16, len-1);
        } else {
            hexit = hexalpha_to_int(s[i]);
            if (hexit == 0) valid = 0;
            else ans = ans + hexit * (int)pow(16, len-1);
        }
        ++i;
        --len;
    }
    if (!valid) ans = 0;

    return ans;
}

int main() {

    char *hvalues[] = {
            "0xF00", //3840
            "F00", //3840
            "1DA6", //7590
            "0X1DA6", //7590
            "0xE8B", //3723
            "E8B" //3723
    };
    int n = 6, i=0;
    for (i=0; i<n; i++) {
        char* s = hvalues[i];
        int ans = htoi(s);
        printf("%s => %d\n", s, ans);

    }

    return 0;
}
