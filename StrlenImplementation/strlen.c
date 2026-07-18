#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int my_strlen(const char *str){

    int len = 0;

    while (*str != '\0')
    {
        len++;
        str++;
    }
    return len;
}

int main(){

    char str[100];

    printf("Enter a string: ");
    scanf("%99s", str);

    int length = my_strlen(str);
    printf("Length of the string: %d\n", length);

    return 0;
}