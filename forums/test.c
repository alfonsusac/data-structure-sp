#include<stdio.h>
#include "util.h"



int main(){
    // Source: https://stackoverflow.com/questions/5820810/case-insensitive-string-comparison-in-c
    char str1[255] = "Yes";
    char *str2 = "Yes";

    const unsigned char *us1 = (const unsigned char*)str1;
    const unsigned char *us2 = (const unsigned char *)str2;

    while( tolower(*us1) == tolower(*us2++) ){
        if( *us1++ == '\0' ){
            printf("True!!");
            return 0;
        }
    }

    printf("%d", tolower(*us1) - tolower(*--us2));
}