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
#define validate_catch( GET, MUST_BE, CATCH )   while(1){GET;if(MUST_BE){break;}else{CATCH;}}
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
#define streq(A,B)              strcmp(A,B) == 0
#define between(what,from,to)   what >= from && what <= to
#define new_struct(NAME,TYPE)   TYPE *NAME = (TYPE *)malloc(sizeof(TYPE))
#define traverse(what,to)         what = what->to
#define STRUCT                  typedef struct
#define MAX_STR_LENGTH          256


STRUCT DLL_Node{
    char id[MAX_STR_LENGTH];
    char title[MAX_STR_LENGTH];
    char author[MAX_STR_LENGTH];
    char isbn[MAX_STR_LENGTH];
    int  pagenum;

    int  key;
    struct DLL_Node *next;
}Node;
int last_id = 0;

void set_book_id(Node* node){
    if( node->title[0] == '\0' ) return;
    if( node->author[0] == '\0' ) return;
    if( node->isbn[0] == '\0' ) return;
    sprintf(node->id, "B%05d-%s-%c%c", ++last_id, node->isbn, node->author[0], node->title[0]);
}

int get_hash_key(Node node);

Node *create_node(Node tmp){
    new_struct(node, Node);
    strcpy(node->title, tmp.title);
    strcpy(node->author, tmp.author);
    strcpy(node->isbn, tmp.isbn);
    node->pagenum = tmp.pagenum;

    set_book_id(node);
    node->key = get_hash_key(*node);

    node->next = 0;

    return node;
}



#define SIZE 1007
STRUCT HashTable_Chaining{
    Node *row[SIZE];
}HashTable;

int get_hash_key(Node node){
    if( node.id[0] == '\0' ) return -1;
    int sum = 0;
    int len = strlen(node.id);
    for( range(len) ){
        sum += node.id[i];
    }
    return sum % SIZE;
}

bool search_hashTable_byName(HashTable *table, char* title){

    // Traverse through all row
    for( range(SIZE) ){
        if( table->row[i] isnot NULL ){
            Node *curr = table->row[i];
            while( curr isnot NULL ){
                if( seq(curr->title, title) ){
                    return true;
                }
                curr = curr->next;
            }
        }
    }
    return false;
}

Node* search_hashTable_byID(HashTable *table, char* id){

    // Traverse through all row
    for( range(SIZE) ){
        if( table->row[i] isnot NULL ){
            Node *curr = table->row[i];
            while( curr isnot NULL ){
                if( strcmp(curr->id, id) ){
                    return curr;
                }
                curr = curr->next;
            }
        }
    }
    return 0;
}

bool insert_to_hashTable_with_chaining(HashTable *table, Node tmp){

    Node *new_node  = create_node(tmp);
    int  hash_key   = new_node->key;
    
    if( !table->row[hash_key] ){
        table->row[hash_key] = new_node;
        return true;
    }else{
        Node *curr = table->row[hash_key];
        while( curr isnot NULL ){
            if( strcmp(curr->title, new_node->title) ){
                return false;
            }
            curr = curr->next;
        }
    }
    return false;
}

void remove_from_hashTable_by_node(HashTable *table, Node *tmp){

    int hash_key = tmp->key;
    Node *rem;

    if( table->row[hash_key] ){
        Node *head = table->row[hash_key];
        if( head is tmp ){
            rem = head;
            table->row[hash_key] = head->next;
            free(rem);
            return;
        }else{
            while( head->next isnot NULL){
                if( head->next is tmp ){
                    rem = head->next;
                    head->next = rem->next;
                    free(rem);
                    return;
                }
                head = head->next;
            }
        }
    }else{
        return;
    }
    return;
}

void menu_view_book(HashTable *table);
void menu_insert_book(HashTable *table);
void menu_remove_book(HashTable *table);

int main(){
    // Initialization
    HashTable table;
    for( range(SIZE) )
        table.row[i] = 0;

    insert_to_hashTable_with_chaining(&table,(Node){
        "", "Don't Make Me Think", "Mr. Krug S.", "9780321344755", 106, -1, 0
    });
    insert_to_hashTable_with_chaining(&table,(Node){
        "", "Agile Project Management With Scrum", "Mr. Ken Schwaber", "9780735619937", 192, -1, 0
    });
    
    // Execution
    int running = true;
    while( running ){
        
        clr();
        put("Bluejack Library \n");
        put("=================\n");
        put("1. View Book\n");
        put("2. Insert Book\n");
        put("3. Remove Book\n");
        put("4. Exit\n");

        int choice = 0;
        get(">> ", "%d", &choice);

        clr();
        if( choice == 1 ) menu_view_book(&table);
        if( choice == 2 ) menu_insert_book(&table);
        if( choice == 3 ) menu_remove_book(&table);
        if( choice == 4 ) running = false;

    }
}

void menu_view_book(HashTable *table){

    put("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    put("| Book ID                 | Book Title                                         | Book Author               | ISBN           | Page Number |\n");
    put("-------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    for ( range(SIZE) ){
        if( table->row[i] isnot NULL ){
            Node *curr = table->row[i];
            while( curr isnot NULL ){
                put("| %-23s | %-50s | %-25s | %-14s | %-11d |\n",
                    curr->id, curr->title, curr->author, curr->isbn, curr->pagenum);
                put("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                curr = curr->next;
            }
        }
    }
    put("\n");
    getenter("Press Enter to continue ...");
}

bool is_all_numeric(char* str){
    int len = strlen(str);
    for( range(len) )
        if( !isdigit(str[i]) )
            return false;
    return true;
}

void menu_insert_book(HashTable *table){

    Node input;

    validate_catch(validate(getline("Input book title[5-50][unique]: ", input.title), between(strlen(input.title), 5, 50)),
                   search_hashTable_byName(table, input.title) isnot true,
                   put("The book title is already exists !\n"));

    validate(getline("Input author name[3-25][Mr. |Mrs. ]: ", input.author),
             between(strlen(input.author), 3, 25) &&
                 (strncmp("Mr. ", input.author, 3) == 0 ||
                 strncmp("Mrs. ", input.author, 4) == 0));

    validate(getline("Input ISBN[10-13][numeric]: ", input.isbn),
             between(strlen(input.isbn), 10, 13) &&
                 is_all_numeric(input.isbn));
                 
    validate(getint("Input page number [>= 16]: ", input.pagenum), input.pagenum >= 16);

    put("\n");

    insert_to_hashTable_with_chaining(table, input);
    getenter("Insert success !\n");

}

void menu_remove_book(HashTable *table){

    Node input;

    getline("Input book id to delete: ", input.id);

    Node* search = search_hashTable_byID(table, input.id);

    if( search is 0 ){
        getenter("\n Book not found !\n");
        return;
    }else{
        put("\n");
        put("\n");
        put("Book Id: %s\n", search->id);
        put("Book Title: %s\n", search->title);
        put("Book Author: %s\n", search->author);
        put("Book ISBN: %s\n", search->isbn);
        put("Page Number: %d\n", search->pagenum);

        int confirm;
        validate_int_from_choices("Are you sure [y|n]? ", confirm, 2, "n", "y");

        if( confirm ){
            remove_from_hashTable_by_node(table, search);
            puts("\n");
            getenter("Delete success !\n");
        }

        return;
    }
}

// -------------------
// | B00001-9780321344755-DM | Don't Make Me Think                                | Mr. Krug S.               | 9780321344755  | 106         |
// -------------------------------------------------------------------------------------------------------------------------------------------
// | B00002-9780735619937-AM | A