#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h> // https://stackoverflow.com/questions/30033582/what-is-the-symbol-for-whitespace-in-c/30033598#30033598

// ************************ LINES SHORTCUT: INPUT AND OUTPUT
#define clr() printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
#define get(PROMPT, FORMAT, ...)                  \
    {                                             \
        while (1)                                 \
        {                                         \
            printf(PROMPT);                       \
            fflush(stdin);                        \
            if (scanf(FORMAT, ##__VA_ARGS__) > 0) \
            {                                     \
                fflush(stdin);                    \
                break;                            \
            }                                     \
        }                                         \
    }
#define getline(PROMPT, OUTPUT)                    \
    {                                              \
        while (1)                                  \
        {                                          \
            printf(PROMPT);                        \
            fflush(stdin);                         \
            if (scanf("%255[^\n]%*c", OUTPUT) > 0) \
            {                                      \
                fflush(stdin);                     \
                break;                             \
            }                                      \
        }                                          \
    }
#define getint(PROMPT, OUTPUT)            \
    {                                     \
        while (1)                         \
        {                                 \
            printf(PROMPT);               \
            fflush(stdin);                \
            if (scanf("%d", &OUTPUT) > 0) \
            {                             \
                fflush(stdin);            \
                getchar();\
break;                    \
            }                             \
        }                                 \
    }
#define validate(GET, MUST_BE) \
    do                         \
    {                          \
        GET;                   \
    } while (!(MUST_BE))
#define validate_catch(GET, MUST_BE, CATCH) \
    while (1)                               \
    {                                       \
        GET;                                \
        if (MUST_BE)                        \
        {                                   \
            break;                          \
        }                                   \
        else                                \
        {                                   \
            CATCH;                          \
        }                                   \
    }

int strcasecmpnew(const char *s1, const char *s2)
{
    // Copy first to make it non destructive
    const unsigned char *us1 = (const unsigned char *)s1,
                        *us2 = (const unsigned char *)s2;

    // Lower it
    while (tolower(*us1) == tolower(*us2++))
        if (*us1++ == '\0')
            return (0);
    return (tolower(*us1) - tolower(*--us2));
}

#define validate_int_from_choices(PROMPT, OUTPUT, NUM_OF_CHOICE, ...) \
    {                                                                 \
        OUTPUT = -1;                                                  \
        char input_choice[256];                                       \
        const char *__choices[] = {__VA_ARGS__};                      \
        do                                                            \
        {                                                             \
            get(PROMPT, "%255[^\n]%*c", input_choice);                \
            for (range(NUM_OF_CHOICE))                                \
            {                                                         \
                if (strcmp(input_choice, __choices[i]) == 0)          \
                {                                                     \
                    OUTPUT = i;                                       \
                    break;                                            \
                }                                                     \
            }                                                         \
        } while (OUTPUT == -1);                                       \
    }
#define scmp_case(OUTPUT, STR1, STR2)                           \
    {                                                           \
        const unsigned char *us1 = (const unsigned char *)STR1; \
        const unsigned char *us2 = (const unsigned char *)STR2; \
        while (tolower(*us1) == tolower(*us2++))                \
        {                                                       \
            if (*us1++ == '\0')                                 \
            {                                                   \
                OUTPUT = 0;                                     \
                break;                                          \
            }                                                   \
        }                                                       \
        OUTPUT = tolower(*us1) - tolower(*--us2);               \
    }
#define validate_int_from_choices_case(PROMPT, OUTPUT, NUM_OF_CHOICE, ...) \
    {                                                                      \
        OUTPUT = -1;                                                       \
        char input_choice[256];                                            \
        const char *__choices[] = {__VA_ARGS__};                           \
        do                                                                 \
        {                                                                  \
            get(PROMPT, "%255[^\n]%*c", input_choice);                     \
            for (range(NUM_OF_CHOICE))                                     \
            {                                                              \
                int cmp;                                                   \
                scmp_case(cmp, input_choice, __choices[i]);                \
                if (cmp == 0)                                              \
                {                                                          \
                    OUTPUT = i;                                            \
                    break;                                                 \
                }                                                          \
            }                                                              \
        } while (OUTPUT == -1);                                            \
    }
#define validate_int_from_array(PROMPT, OUTPUT, CHOICE_COUNT, CHOICE_ARRAY) \
    { /**C     C     C                  ARRAY **/                           \
        char input_choice[256];                                             \
        OUTPUT = -1;                                                        \
        do                                                                  \
        {                                                                   \
            get(PROMPT, "%255[^\n]%*c", input_choice);                      \
            for (range(CHOICE_COUNT))                                       \
            {                                                               \
                if (strcmp(input_choice, CHOICE_ARRAY[i]) == 0)             \
                {                                                           \
                    OUTPUT = i;                                             \
                    break;                                                  \
                }                                                           \
            }                                                               \
        } while (OUTPUT == -1);                                             \
    }

#define validate_str_from_choices(PROMPT, OUTPUT, NUM_OF_CHOICE, ...) \
    {                                                                 \
        const char *__choices[] = {__VA_ARGS__};                      \
        do                                                            \
        {                                                             \
            get(PROMPT, "%255[^\n]%*c", OUTPUT);                      \
            for (range(NUM_OF_CHOICE))                                \
            {                                                         \
                if (strcmp(OUTPUT, __choices[i]) == 0)                \
                {                                                     \
                    break;                                            \
                }                                                     \
            }                                                         \
        } while (1);                                                  \
    }
#define validate_yn(PROMPT, OUTPUT_BOOL, ...)       \
    {                                               \
        char input_choice[256];                     \
        do                                          \
        {                                           \
            put(PROMPT __VA_OPT__(, ) __VA_ARGS__); \
            get(" ", "%3[^\n]%*c", input_choice);   \
            if (len(input_choice) == 1)             \
            {                                       \
                if (input_choice[0] == 'n')         \
                {                                   \
                    OUTPUT_BOOL = false;            \
                    break;                          \
                }                                   \
                else if (input_choice[0] == 'y')    \
                {                                   \
                    OUTPUT_BOOL = true;             \
                    break;                          \
                }                                   \
            }                                       \
        } while (1);                                \
    }
#define getenter(...)    \
    printf(__VA_ARGS__); \
    getchar();
#define putl(...)        \
    printf(__VA_ARGS__); \
    printf("\n");

// ************************ LINES SHORTCUT: OTHERS
#define len(STR) strlen(STR)
#define new_struct(TYPE, NAME) TYPE *NAME = (TYPE *)malloc(sizeof(TYPE))
#define memalloc(TYPE) (TYPE *)malloc(sizeof(TYPE))
#define break_if_numeric(STR) \
    int len = strlen(STR);    \
    for (range(len))          \
        if (!isdigit(STR[i])) \
            continue;         \
    break;
#define loop(DOWHAT) \
    while (true)     \
    {                \
        DOWHAT       \
    }
#define CONST_STRING_ARRAY(NAME, COUNTNAME, NUM, ...) \
    const int COUNTNAME = NUM;                        \
    const char *const NAME[] = {__VA_ARGS__};

// ************************ ALIASES
#define put printf
#define is ==
#define isnot !=
#define and &&
#define or ||
#define STRUCT typedef struct
#define exists isnot NULL
#define isempty is NULL

// ************************ EXPRESSIONS
#define _range1(end) \
    int i = 0;       \
    i < end;         \
    i++
#define _range2(start, end) \
    int i = start;          \
    i < end;                \
    i++
#define _range3(start, end, hop) \
    int i = start;               \
    i < end;                     \
    i = i + hop
#define range_get_macro(_1, _2, _3, name, ...) name
#define range(...) range_get_macro(__VA_ARGS__, _range3, _range2, _range1)(__VA_ARGS__)
#define seq(A, B) strcmp(A, B) == 0
#define scmp(A, B, C) strcmp(A, C) B 0
#define between(what, from, to) what >= from &&what <= to
#define traverse(what, to) what = what->to
#define starts_with(INPUT, STARTS_WITH) strncmp(STARTS_WITH, INPUT, strlen(STARTS_WITH)) == 0
#define ends_with(INPUT, ENDS_WITH) strlen(INPUT) > strlen(ENDS_WITH) && !strcmp(INPUT + strlen(INPUT) - strlen(ENDS_WITH), ENDS_WITH)
#define betweenstr(STRING, FROM, TO) between(strlen(STRING), FROM, TO)
#define max(A, B) A > B ? A : B

// ******************************** PERSONAL LIMITS
#define MAX_STR_LENGTH 256

// ************************************************************

STRUCT NODE{
    char name[MAX_STR_LENGTH];
    int code; // only "1"  or  "2"
    struct NODE *next;
} Node;


//  code = 2, code = 1
// { Class 1, Class 2 }

Node* new_patient(Node tmp){
    if( tmp.code > 2 || tmp.code < 1 ){
        put("ERROR: codeid doesnt exists");
        return 0;
    }
    new_struct(Node, node);
    strcpy(node->name, tmp.name);
    node->code = tmp.code;
    return node;
}

STRUCT LinkedList{
    Node    *head;
    int     count;
}LinkedList;

bool is_empty(LinkedList *list) {
    return list->head ? false : true;
}

void push_to_priority_queue(LinkedList *list, Node tmp){
    // https://www.javatpoint.com/priority-queue-using-linked-list
    Node *new_node = new_patient(tmp);

    if( is_empty(list) or new_node->code < list->head->code ){
        new_node->next = list->head; // Push head
        list->head     = new_node;
    }else{
        Node *curr     = list->head;
        // 3 3 3 3 3  2 2 2 2  1 1 1 1
        while( curr->next isnot NULL && curr->next->code <= new_node->code )
            curr = curr->next;
        new_node->next = curr->next;
        curr->next     = new_node;
    }
}

Node* pop_priority_queue(LinkedList *list){
    if( is_empty(list) ) {
        return 0;
    }else{
        Node *tmp = list->head;
        list->head = list->head->next;
        return tmp;
    }
    return 0;
}

void display_queue_content(LinkedList list){
    int first = 1;
    if( is_empty(&list) ){
        put("There is no queue yet !\n");
    }else{
        put("Queue content: ");
        Node *curr = list.head;
        while( curr ){
            if( first ){
                put("%s %d", curr->name, curr->code);
                first = 0;
            }else{
                put(" - %s %d", curr->name, curr->code);
            }
            curr = curr->next;
        }
        put("\n");
    }
}

STRUCT INPUT{
    char name[MAX_STR_LENGTH];
    int class;
    char service[MAX_STR_LENGTH];
}Input;

int main(){
    LinkedList pqlist = {0, 0};

    bool isRunning = true;
    do{
        Node input;
        validate(
            getline("Patient Arrice (Name)[>2 and <255]: ", input.name),
            betweenstr(input.name,3,254));
        if( seq(input.name, "End") ){
            isRunning = false;
            break;
        }else{
            validate(
                getint("Nature of Emergency[1|2]:", input.code), 
                between(input.code,1,2));
            //
            push_to_priority_queue(&pqlist, input);
            display_queue_content(pqlist);
            int do_service;
            validate_int_from_choices("Service? [Y|N] ", do_service, 2, "N", "Y");
            if (do_service)
            {
                pop_priority_queue(&pqlist);
                display_queue_content(pqlist);
            }
        }
    } while( isRunning == true );
}


