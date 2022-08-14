#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define get(PROMPT,FORMAT,...) {    while(1){        printf(PROMPT);        fflush(stdin);        if (scanf(FORMAT,##__VA_ARGS__) > 0){        fflush(stdin);            break;        }    }}
#define getenter(...) printf(__VA_ARGS__); getchar();
#define put printf
#define is ==
#define clr() printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
#define _range1(end)            int i = 0; i < end; i++
#define _range2(start,end)      int i = start; i < end; i++
#define _range3(start,end,hop)  int i = start; i < end; i = i+hop
#define range_get_macro(_1, _2, _3, name, ...) name
#define range(...) range_get_macro(__VA_ARGS__, _range3, _range2, _range1)(__VA_ARGS__)
#define between(what,from,to)   what > from && what < to
#define betweeni(what,from,to)  what >= from && what <= to

typedef struct Student{
    char nim[50];
    char name[50];
    int  umur;
} Student;

int main(){
    Student list[3] = {
        {"2301900555", "Alfonsus Ardani", 21},
        {"2301900556", "A Ardani", 22},
        {"2301900216", "Alfonsus A", 23}
    };
    for(range(0,3)){
        printf("%s %s (%d)\n", list[i].nim, list[i].name, list[i].umur);
    }
    return 0;
}