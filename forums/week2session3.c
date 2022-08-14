#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h> // https://stackoverflow.com/questions/30033582/what-is-the-symbol-for-whitespace-in-c/30033598#30033598

#define clr()                                   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
#define get(PROMPT,FORMAT,...)                  {    while(1){        printf(PROMPT);        fflush(stdin);        if (scanf(FORMAT,##__VA_ARGS__) > 0){        fflush(stdin);            break;        }    }}
#define getline(PROMPT,OUTPUT)                  {    while(1){        printf(PROMPT);        fflush(stdin);        if (scanf("%255[^\n]%*c",OUTPUT) > 0){        fflush(stdin);            break;        }    }}
#define getint(PROMPT,OUTPUT)                   {    while(1){        printf(PROMPT);        fflush(stdin);        if (scanf("%d",&OUTPUT) > 0){        fflush(stdin);            break;        }    }}
#define validate( GET, MUST_BE )                do{GET;}while( !(MUST_BE) )
#define validate_int_from_choices(PROMPT,OUTPUT,LEN,...) {    OUTPUT = -1;    char input_choice[256];    const char *__choices[] = {__VA_ARGS__};    do{        get(PROMPT, "%255[^\n]%*c", input_choice);        for ( range(LEN) ){            if ( strcmp(input_choice, __choices[i]) == 0 ){                OUTPUT = i;            }        }    } while (OUTPUT == -1);}
#define validate_str_from_choices(PROMPT,OUTPUT,LEN,...) {    const char *__choices[] = {__VA_ARGS__};    do{        get(PROMPT, "%255[^\n]%*c", OUTPUT);        for ( range(LEN) ){            if ( strcmp(OUTPUT, __choices[i]) == 0 ){                break;            }        }    } while (1);}
#define getenter(...)                           printf(__VA_ARGS__); getchar();
#define put printf
#define is ==
#define isnot !=
#define and &&
#define or ||
#define _range1(end)            int i = 0; i < end; i++
#define _range2(start,end)      int i = start; i < end; i++
#define _range3(start,end,hop)  int i = start; i < end; i = i+hop
#define range_get_macro(_1, _2, _3, name, ...) name
#define range(...) range_get_macro(__VA_ARGS__, _range3, _range2, _range1)(__VA_ARGS__)
#define between(what,from,to)   what > from && what < to
#define betweeni(what,from,to)  what >= from && what <= to
#define new_struct(NAME,TYPE)   TYPE *NAME = (TYPE *)malloc(sizeof(TYPE))
#define traverse(what,to)         what = what->to
#define STRUCT                  typedef struct
#define MAX_STR_LENGTH          256

STRUCT DLL_Node{
    char name[MAX_STR_LENGTH];
    int  age;
    char desc[MAX_STR_LENGTH];
    int  code; // Only "1", "2", "3"
    struct DLL_Node *next;
} Node;

//                         0        1         2
const char *code_id[3] = {"Green", "Yellow", "Red"};

Node *new_patient(Node tmp){
    new_struct(new_node, Node);
    strcpy(new_node->name, tmp.name);
    strcpy(new_node->desc, tmp.desc);
    if( tmp.code > 3 || tmp.code < 0 ){
        put("ERROR: codeid doesnt exists");
    }
    new_node->code = tmp.code;
    new_node->age = tmp.age;
    new_node->next = 0;
    return new_node;
}

STRUCT DoublyLinkedList{
    Node *head;
    int  count;
} DoublyLinkedList;

bool is_empty(DoublyLinkedList *list){
    return list->head ? false : true;
}

void push_to_priority_queue(DoublyLinkedList *list, Node tmp){
    // https://www.javatpoint.com/priority-queue-using-linked-list
    Node *new_node = new_patient(tmp);

    if( is_empty(list) or new_node->code > list->head->code ){
        new_node->next = list->head; // Push head
        list->head     = new_node;
    }else{
        Node *curr     = list->head;
        // 3 3 3 3 3  2 2 2 2  1 1 1 1
        while( curr->next isnot NULL && curr->next->code >= new_node->code )
            curr = curr->next;
        new_node->next = curr->next;
        curr->next     = new_node;
    }
}

Node* pop_priority_queue(DoublyLinkedList *list){

    if( is_empty(list) ){
        return 0;
    }else{
        Node *tmp = list->head;
        list->head = list->head->next;
        return tmp;
    }
    return 0;
}



void display_insert(DoublyLinkedList *list);
void display_view(DoublyLinkedList list);
void display_next_queue(DoublyLinkedList *list);

int main(){
    // Initialization
    DoublyLinkedList pqlist = {0, 0};
    push_to_priority_queue(&pqlist, (Node){"Mr. Doe",       23, "Cough and fever",                                      1});
    push_to_priority_queue(&pqlist, (Node){"Mr. John",      45, "GERD",                                                 2});
    push_to_priority_queue(&pqlist, (Node){"Mrs. Carolina", 28, "Nausea, vomiting, sweating, and difficulties walking", 2});
    push_to_priority_queue(&pqlist, (Node){"Mr. Budi",      34, "Serious injury from car accident",                     3});

    // Execution
    bool running = true;
    while( running ){

        clr();
        put("Bluejack Hospital\n");
        put("=================\n");
        put("1. Insert\n");
        put("2. View\n");
        put("3. Next Queue\n");
        put("4. Exit\n");

        int choice = 0;
        get(">> ", "%d", &choice);

        clr();
        if( choice == 1 ) display_insert(&pqlist);
        if( choice == 2 ) display_view(pqlist);
        if( choice == 3 ) display_next_queue(&pqlist);
        if( choice == 4 ) running = false;

    }
}

void display_insert(DoublyLinkedList *list){

    Node input;

    validate(getline("Input patient name[4-25]: ", input.name),             betweeni(strlen(input.name), 4, 25));
    validate(getint("Input patient age[>= 0]: ", input.age),                input.age >= 0);
    validate(getline("Input description[>= 6 characters]: ", input.desc),   strlen(input.desc) >= 6);
    validate_int_from_choices("Input code[Red|Yellow|Green]: ", input.code, 3, "Green", "Yellow", "Red");

    put("\n");

    input.code++;
    push_to_priority_queue(list, input);
    getenter("Insert success !\n");

}

void display_view(DoublyLinkedList list){

    if( is_empty(&list) ){
        put("There is no queue yet !\n");
        put("\n");
        getenter("Press Enter to continue ...\n");
    }else{
        put("Patient List:\n");
        put("-------------------------------------------------------------------------------------------------------------\n");
        put("|No  | Name                      | Age  | Description                                             | Code    |\n");
        put("-------------------------------------------------------------------------------------------------------------\n");

        Node *curr = list.head;
        int  idx = 0;
        while( curr ){
            idx++;
            put("|%-4d| %-25s | %-4d | %-55s | %-7s |\n",idx, curr->name, curr->age, curr->desc, code_id[curr->code-1] );
            curr = curr->next;
        }

        put("-------------------------------------------------------------------------------------------------------------\n");
        put("\n");
        getenter("Press Enter to continue ...\n");
    }

}

void display_next_queue(DoublyLinkedList *list){

    if( is_empty(list) ){
        put("There is no queue yet !\n");
        put("\n");
        getenter("Press Enter to continue ...\n");
    }else{
        put("The next patient is:\n");

        Node *top = pop_priority_queue(list);
        put("Name           : %s\n", top->name);
        put("Age            : %d\n", top->age);
        put("Description    : %s\n", top->desc);
        put("Code           : %s\n", code_id[top->code-1]);
        free(top);

        put("\n");
        getenter("Press Enter to continue ...\n");
    }

}