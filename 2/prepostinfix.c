#include<stdio.h>
#include<string.h>

int main()
{
    char infix[] = "a+b";
    printf("%s", infix);
    for (int i = 0; infix[i] != '\0'; i++)
    {
        putchar(infix[i]);
    }
}