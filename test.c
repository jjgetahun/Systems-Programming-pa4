#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

    char str1[10] = "example0";
    char str2[10] = "example00";

    int num = strcmp(str1, str2);

    if (num > 0) {
        printf("%s\n", str2);
        printf("%s\n", str1);
    }
    else if (num < 0) {
        printf("%s\n", str1);
        printf("%s\n", str2);
    }
    else {
        printf("%s\n", str1);
        printf("%s\n", str2);
    }

}
