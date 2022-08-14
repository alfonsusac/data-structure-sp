#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h> // https://stackoverflow.com/questions/30033582/what-is-the-symbol-for-whitespace-in-c/30033598#30033598

#define clr()                                   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
#define get(PROMPT,FORMAT,...)                  {    while(1){        printf(PROMPT);        fflush(stdin);        if (scanf(FORMAT,##__VA_ARGS__) > 0){        fflush(stdin);            break;        }    }}
#define get_int_from_choices(PROMPT,OUTPUT,LEN,...) {    OUTPUT = -1;    char input_choice[256];    const char *__choices[] = {__VA_ARGS__};    do{        get(PROMPT, "%255[^\n]%*c", input_choice);        for ( range(LEN) ){            if ( strcmp(input_choice, __choices[i]) == 0 ){                OUTPUT = i;            }        }    } while (OUTPUT == -1);}
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
#define move_next(what)         what = what->next
#define STRUCT                  typedef struct
#define STRUCT(NAME, ...)       typedef struct NAME{__VA_ARGS__}NAME;

STRUCT(Node,
    char        data;
    struct Node *next;
)

Node* new_char(char c, Node* next){
    new_struct(new_node, Node);
    new_node->data = c;
    new_node->next = next;
    return new_node;
}

STRUCT(SinglyLinkedList,
    Node    *head;
    int     count;
)

void push_to_stack(SinglyLinkedList *stack, char c){
    stack->head = new_char(c, stack->head);
    stack->count++;
}

void pop_stack(SinglyLinkedList *stack){
    Node *tmp = stack->head;
    move_next(stack->head);
    free(tmp);
    stack->count--;
}

Node* peek_stack(SinglyLinkedList *stack){
    return stack->head;
}

bool is_empty(SinglyLinkedList *stack){
    return stack->head ? false : true;
}

#define MAX_STR_LENGTH 256
int word_count(char *sentence);

int main(){
    // Initialization
    SinglyLinkedList stack = {0, 0};

    // Execution
    int running = true;
    while (running)
    {
        put("Reverse Sentence\n");
        put("================\n");
        put("\n");

        char input_sentence[MAX_STR_LENGTH];
        do{
            get("Input sentence[minimum 5 words]:", "%255[^\n]%*c", input_sentence);
        } while (word_count(input_sentence) < 5);

        int input_length = strlen(input_sentence);
        for ( range( input_length ) ) {
            push_to_stack(&stack, input_sentence[i]);
        }

        put("\n");
        put("\n");

        put("The result is: ");
        while( !is_empty(&stack) ){
            put("%c", peek_stack(&stack)->data);
            pop_stack(&stack);
        } put("\n");

        put("\n");
        put("\n");

        int choice = -1;                                                 // 0      1
        get_int_from_choices("Do you want to continue [yes|no] ? ", choice, 2, "yes", "no");

        if (choice == 1)
            running = false;
    }
    return 0;
}

int word_count(char *sentence){
    int count = 0;
    int len = strlen(sentence);
    const int START  = 0;
    const int LETTER = 1;
    const int SPACE  = 2;
    int chartype = START;
    for( range(len) ){
        char c = sentence[i];
        if(chartype is START and c isnot ' ')
            chartype = LETTER;
        else if(isspace(c) and chartype is LETTER){
            chartype = SPACE;
            count++; // mark word
        }
        else if(!isspace(c) and chartype is SPACE)
            chartype = LETTER;
    }
    if(chartype is LETTER)
        count++; // mark word

    return count;
}

