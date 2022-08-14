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

typedef struct Cake{
    char code[50];
    char name[50];
    int  stock;
    int  price;
} Cake;
#define cakelist_count 4

int find_cake(Cake list[cakelist_count], char *code){
    for(range(cakelist_count))
        if( strcmp(code, list[i].code) == 0 )
            return i;
    return -1;
}

void put_cake_list(Cake list[cakelist_count]);
void put_main_menu();
void sell_menu();
void add_stock_menu();

int main(){
    // Initialization
    Cake cakelist[cakelist_count] = {
        {"CK001", "Blueberry Cake",        13,  25000},
        {"CK009", "Chocochip Cake",         5,  20000},
        {"CK017", "Mayonaise Cake",        24,  30000},
        {"CK023", "Strawberry ShortCake",   7,  17500}
    };

    // Execution
    bool running = true;
    while (running){

        clr();
        put(" BLUE CAKE SHOP CASHIER\n");
        put(" ======================\n");
        put(" \n");
        put_cake_list(cakelist);
        put(" \n");
        put_main_menu();

        int input = 0;
        get(" Input Choice: ", "%d", &input);

        if (input is 1) sell_menu(&cakelist);
        if (input is 2) add_stock_menu(&cakelist);
        if (input is 3) running = false;
        
    }
    return 0;
}

void put_cake_list(Cake list[cakelist_count]){
    put(" %-3s | %-9s | %-20s | %9s | %s\n", "No.", "Cake Code", "Cake Name", "Available", "Price");
    put(" ---------------------------------------------------------------\n");
    for( range(cakelist_count) ){
        put(" %02d. | %-9s | %-20s | %9d | Rp.%6d,-\n", 
        i, list[i].code, list[i].name, list[i].stock, list[i].price);
    }
    put(" ---------------------------------------------------------------\n");
}

void put_main_menu(){
    put(" Menu :\n");
    put(" 1. Sell\n");
    put(" 2. Add Stock\n");
    put(" 3. Exit\n");
}

void sell_menu(Cake list[cakelist_count]){

    char input_code[50];
    int  cake_idx;
    Cake *cake;
    int  input_qty;

    while (1) {
        do { 
            get(" Input Cake Code [5 chars]: ","%6s",input_code);
        } while (strlen(input_code) != 5);
        cake_idx = find_cake(list, input_code);

        if ( cake_idx != -1 )   // sucecss
            break;
        else{                   // fail
            getenter("\n --- The Cake Code doesn't exist ---\n");
        }
    }

    cake = &list[cake_idx];
    while (1) {
        put(" Input Quantity [0..%d", cake->stock); get("]: ", "%d", &input_qty);
        
        if ( betweeni(input_qty, 0, cake->stock) )
            break;
        else{
            getenter("\n ...The quantity of cake is not enough...");
        }
    }

    put("\n");
    put("\n");

    int total_price = cake->price * input_qty;
    cake->stock -= input_qty;
    put(" Total Price is : Rp %d,- x %d = Rp %d,-\n",cake->price, input_qty, total_price);
    put("\n");
    getenter(" --- Thank You ---\n");
}

void add_stock_menu(Cake list[cakelist_count]){

    char input_code[50];
    int  cake_idx;
    int  input_qty;

    // ask user input CAKE CODE to add to list
    while (1) {
        do { 
            get(" Input Cake Code [5 chars]: ","%6s",input_code);
        } while (strlen(input_code) != 5);
        cake_idx = find_cake(list, input_code);

        if ( cake_idx != -1 )   // sucecss
            break;
        else{                   // fail
            getenter("\n --- The Cake Code doesn't exist ---\n");
        }
    }

    // if valid, ask to input QUANTITY  
    while (1) {
        get(" Input Quantity [1..10]: ", "%d", &input_qty);
        
        if ( betweeni(input_qty, 1, 10) )
            break;
    }

    put("\n");
    put("\n");

    list[cake_idx].stock += input_qty;
    getenter(" --- Adding Stock Success ---\n");
}
