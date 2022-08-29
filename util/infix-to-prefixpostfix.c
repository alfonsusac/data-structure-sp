// Made by Alfonsus Ardani
// Last accessed 8/24/2022, 21:26:25 
// Made for Data Struct SP Course

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define printn(code, len) for (int _i = 0; _i < len; _i++){printf("%c",code);}
#define print1(code) printf("%c", code);
#define printTopRow() print1(218);printn(196,len+2);print1(194);printn(196,len/2+3);print1(194);printn(196,len+3);print1(191);printf("\n");
#define printPostRow() int halfwidth = len / 2; int width = len; int inputleft = strlen(inputPostfix.data + i); print1(179);  printf(" "); for( int _i = 0; _i<width-inputleft; _i++ ){printf(" "); } printf(inputPostfix.data + i)  ; printf(" ");print1(179); printf(" ");printf(stack.data); for( int _i = 0;_i < halfwidth - stack.curr + 1; _i++ ){printf(" "); } print1(179);printf(" ");printf(postfix.data); for( int _i = 0;_i < width - postfix.curr + 1; _i++ ){ printf(" "); } print1(179); printf("\n");
#define printPreRow() int halfwidth = len / 2; int width = len; int inputleft = strlen(inputPrefix.data + i); print1(179);  printf(" "); for( int _i = 0; _i<width-inputleft; _i++ ){printf(" "); } printf(inputPrefix.data + i)  ; printf(" ");print1(179); printf(" ");printf(stack.data); for( int _i = 0;_i < halfwidth - stack.curr + 1; _i++ ){printf(" "); } print1(179);printf(" "); for( int _i = 0;_i < width - prefix.curr; _i++ ){ printf(" "); } printf(prefix.data); printf(" "); print1(179); printf("\n");
#define printBottomRow() print1(192); printn(196,len+2);print1(193);printn(196,len/2+3);print1(193); printn(196,len+3);print1(217); printf("\n");


#define MAXLEN 255
typedef struct string{
    char data[MAXLEN];
} Str;

typedef struct Stack{
    char data[MAXLEN];
    int curr;
} Stack;

#define newStack(name) Stack name = {"", -1};
#define push(stack, b)      \
    stack.curr++;\
    stack.data[stack.curr] = b
#define peek(stack) stack.data[stack.curr]
#define pop(stack)                 \
    stack.data[stack.curr] = '\0'; \
    stack.curr--





int prec(char i){
    if( i == '%' || i == '/' || i == '*' ){
        return 2;
    }else if( i == '+' || i == '-' ){
        return 1;
    }else{
        return 0;
    }
}

int isOPERAND = 1;
int isOPERATOR = 2;
int isOPEN_BRACKET = 3;
int isCLOSE_BRACKET = 4;

int token(char i, int type){
    if( i == '%' || i == '/' || i == '*' || i == '+' || i == '-'){
        return type == isOPERATOR ? 1 : 0;
    }else if (i == '(' ){
        return type == isOPEN_BRACKET ? 1 : 0;
    }else if( i == ')' ){
        return type == isCLOSE_BRACKET ? 1 : 0;
    }else if( type == isOPERAND ){
        return 1;
    }
    return 0;
}

int main(){

    // Input
    // Str raw_input = {"(A-B)/C*D+(E-F)"};
    printf("  Program made offline by Alfonsus\n");
    Str raw_input = {"(A-B)/C*D+(E-F)"};
    int len = strlen(raw_input.data);
    printf("  Input: %s %d Letters\n", raw_input.data, len);

    // Enclose with bracket
    Str inputPostfix;
    Str inputPrefix;
    inputPostfix.data[0] = '(';
    inputPrefix.data[0] = '(';
    int i;
    for( i = 0; i < len; i++ ){
        inputPostfix.data[i + 1] = raw_input.data[i];
        inputPrefix.data[i + 1] = raw_input.data[len - i - 1];
        if( raw_input.data[len-i-1] == '(' ){
            inputPrefix.data[i + 1] = ')';
        }else if( raw_input.data[len-i-1] == ')' ){
            inputPrefix.data[i + 1] = '(';
        }
    }
    inputPostfix.data[i+1] = ')';
    inputPrefix.data[i+1] = ')';
    inputPrefix.data[i+2] = inputPostfix.data[i+2] = '\0';

    printf("  Query Postfix: %s %d Letters\n", inputPostfix.data, (int)strlen(inputPostfix.data));
    printf("  Query Prefix: %s %d Letters\n", inputPrefix.data, (int)strlen(inputPrefix.data));

    len = len + 2;

    // Postfix
    newStack(stack);
    newStack(postfix);

    printf("\n  input | stack | postfix \n");
    printTopRow();

    for (i = 0; i < len; i++) {
        char currChar = inputPostfix.data[i];


        if( token(currChar, isOPEN_BRACKET) ){
            push(stack, '(');
        }else if( token(currChar, isOPERAND) ){
            push(postfix, currChar);
        }else if( token(currChar, isOPERATOR) ){
            if( token( peek(stack), isOPERATOR) ){
                // printf("%c %d | %c %d\n", currChar, prec(currChar), peek(stack), prec(peek(stack)));
                if( prec(currChar) <= prec(peek(stack)) ){
                    while( token( peek(stack), isOPERATOR) &&
                        prec(currChar) <= prec(peek(stack)) ){
                        push(postfix, peek(stack));
                        pop(stack);
                    }
                    push(stack, currChar);
                }else{
                    push(stack, currChar);
                }
            }else{
                push(stack, currChar);
            }
        }else if( token( currChar, isCLOSE_BRACKET) ) {
            while( token(peek(stack), isOPERATOR) ){
                push(postfix, peek(stack));
                pop(stack);
            }
            pop(stack); // open bracket
        }


        printPostRow();
    }
    printBottomRow();

    // Prefix
    stack = (Stack){"", -1};
    newStack(prefix);

    printf("\n  input | stack | postfix \n");
    printTopRow();
    for( i = 0; i < len; i++ ){
        char currChar = inputPrefix.data[i];
        
        if( token(currChar, isOPEN_BRACKET) ){
            push(stack, '(');
        }else if( token(currChar, isOPERAND) ){
            push(prefix, currChar);
        }else if( token(currChar, isOPERATOR) ){
            if( token( peek(stack), isOPERATOR) ){
                // printf("%c %d | %c %d\n", currChar, prec(currChar), peek(stack), prec(peek(stack)));
                if( prec(currChar) < prec(peek(stack)) ){
                    while( token( peek(stack), isOPERATOR) &&
                        prec(currChar) < prec(peek(stack)) ){
                        push(prefix, peek(stack));
                        pop(stack);
                    }
                    push(stack, currChar);
                }else{
                    push(stack, currChar);
                }
            }else{
                push(stack, currChar);
            }
        }else if( token( currChar, isCLOSE_BRACKET) ) {
            while( token(peek(stack), isOPERATOR) ){
                push(prefix, peek(stack));
                pop(stack);
            }
            pop(stack); // open bracket
        }

        printPreRow();
    }
    printBottomRow();

    // reverse
    strrev(prefix.data);

    printf(" Resulting Postfix: %s\n", postfix.data);
    printf(" Resulting Prefix:  %s\n\n\n", prefix.data);
    return 0;
}