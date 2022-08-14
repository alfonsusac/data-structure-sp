#include "util.h"

CONST_STRING_ARRAY(
    genre_names, genre_name_count, 
    4, "Action", "RPG", "Adventure", "Card Game");

STRUCT AVL_Node{
    // Struct Properties
    char title[MAX_STR_LENGTH];
    int genre_id, stock;
    // Data Structure Properties
    int height;
    struct AVL_Node *left, *right;
}Game;
STRUCT GameInput{
    char title[MAX_STR_LENGTH];
    int genre_id;
    int stock;
}GameInput;

Game* create_game(GameInput input){
    new_struct(Game, game);
    strcpy(game->title, input.title);
    game->genre_id = input.genre_id;
    game->stock = input.stock;

    game->height = 1;
    game->left = game->right = NULL;
    return game;
}
void copy_game(Game *to, Game *from){
    strcpy(to->title, from->title);
    to->genre_id = from->genre_id;
    to->stock = from->stock;
}

STRUCT AVL_Tree{
    Game *head;
}AVLTree;


// todo ?? whats this for
int height(Game* node){
    if( node isempty ) return 0;
    return node->height;
}

int update_height(Game* node){
    return max(height(node->left), height(node->right));
}

int get_balance(Game* curr){
    if( curr isempty ) return 0;
    return height(curr->left) - height(curr->right);
}

Game* right_rotate(Game* root){
    printf("DEBUG:::: Right Rotate\n");
    Game *lt = root->left;

    // root becomes right of lt, left right subtree of root becomes right left subtree of root
    Game *tmp = lt->right;
    lt->right = root;
    root->left = tmp;

    root->height = update_height(root) + 1;
    lt->height   = update_height(lt)   + 1;
    return lt; // new root
}
Game* left_rotate(Game* root){
    printf("DEBUG:::: Left Rotate\n");
    Game *rt = root->right;

    // root becomes left of rt, right left subtree of root becomes left right subtree of root
    Game *tmp = rt->left;
    rt->left = root; // Make rt as new root. // Move root to lt of new root
    root->right = tmp; // Move the previous lt of rt becoming rt of old root

    root->height = update_height(root) + 1;
    rt->height = update_height(rt)     + 1;
    return rt; // new root
}



Game* insert(Game* curr, GameInput input){
    if( curr isempty ) return create_game(input);

    if( scmp(input.title, <, curr->title) ) 
        curr->left = insert(curr->left, input);
    else 
    if( scmp(input.title, >, curr->title) ) 
        curr->right = insert(curr->right, input);
    else 
    if( seq(input.title, curr->title) ) {
        putl("ERR: Key Already Exists!!");
        return curr; // Same Existed (?)
    }
    curr->height = 1 + update_height(curr);
    int balance = get_balance(curr); // Assuming the balance of the subtrees are already calculated except the root.
    if( balance > 1 ){                  // Left Skew
        if( scmp(input.title, <, curr->left->title) ){                // New Node is Left Child of Left Skew
            return right_rotate(curr);
        }else 
        if( scmp(input.title, >, curr->left->title) ){          // New NOde is Right CHild of Left Skew
            curr->left = left_rotate(curr->left);
            return right_rotate(curr);
        }
    }else if( balance < -1 ){           // Right Skew
        if( scmp(input.title, >, curr->right->title) ){              // New Node is Right CHild of Right Skew
            return left_rotate(curr);
        }else 
        if( scmp(input.title, <, curr->right->title) ){         // New Node is Left Child of Right Skew
            curr->right = right_rotate(curr->right);
            return left_rotate(curr);
        }
    }
    return curr;
}

Game *search(Game *curr, char *input){
    if( curr isempty ) return 0;
    if( scmp(input, <, curr->title) ) 
        return search(curr->left, input); // Traverse Left
    else 
    if( scmp(input, >, curr->title) ) 
        return search(curr->right, input); // Traverse Right
    // else 
    // if( seq(input, curr->title) ) 
    return curr; // Same Existed
}

Game *predecessor(Game* root){
    if( root->left ){
        Game *c = root->left;
        while( c->right )
            c = c->right;
        return c;
    }
    else put("ERR: Root doesnt have left subtree");
    return 0;
}

Game* delete_node(Game* curr, Game* input){
    // Source: https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
    if( curr isempty ) return curr;
    if( scmp(input->title, <, curr->title) ) 
        curr->left = delete_node(curr->left, input);
    else 
    if( scmp(input->title, >, curr->title) ) 
        curr->right = delete_node(curr->right, input);
    else 
    if( seq(input->title, curr->title) ) {
        if( (curr->left isempty) or (curr->right isempty) ){
            Game *tmp = curr->left ? curr->left : curr->right;
            if( tmp isempty ){
                tmp = curr;
                curr = NULL;
            }else
            if( tmp exists ){
                *curr = *tmp;
            }
            free(tmp);
        }else{
            Game *tmp = predecessor(curr);
            copy_game(curr, tmp);
            curr->right = delete_node(curr->right, tmp);
        }
    }
    if( curr isempty ) return curr;
    curr->height = 1 + update_height(curr);
    int balance = get_balance(curr);    // The balance of the subtrees are not yet calculated.
    if( balance > 1 ){                  // Left Skew
        if( get_balance(curr->left) >= 0 ){             // New Node is Left Child of Left Skew
            return right_rotate(curr);
        }else 
        if( get_balance(curr->left) < 0 ){              // New NOde is Right CHild of Left Skew
            curr->left = left_rotate(curr->left);
            return right_rotate(curr);
        }
    }else if( balance < -1 ){           // Right Skew
        if( get_balance(curr->left) <= 0 ){             // New Node is Right CHild of Right Skew
            return left_rotate(curr);
        }else 
        if( get_balance(curr->left) > 0 ){              // New Node is Left Child of Right Skew
            curr->right = right_rotate(curr->right);
            return left_rotate(curr);
        }
    }
    return curr;
}

void _menu_insert_game(AVLTree* db){

    GameInput input;
    validate(getline("Input game title[5-25][unique]: ", input.title),
             betweenstr(input.title, 5, 25) 
             and search(db->head, input.title) isempty);
    validate_int_from_array("Input game type[Action|RPG|Adventure|Card Game]: ",
                            input.genre_id, genre_name_count, genre_names);
    validate(getint("Input game stock[>= 1]: ", input.stock), input.stock >= 1);
    db->head = insert(db->head, input);
    getenter("Insert success !");
}

void _display_in_order(Game* root){
    if( root isempty ) return;
    _display_in_order(root->left);
    putl("| %-25s | %-12s | %-10d |", root->title, genre_names[root->genre_id], root->stock);
    putl("---------------------------------------------------------");
    _display_in_order(root->right);
}
void _menu_view_game(AVLTree* db){
    if( db->head isempty ){
        putl("Ware house is empty !");
        putl(" ");
        getenter("Press enter to continue...");
    }else{
        putl("---------------------------------------------------------");
        putl("| Game Title                | Game Genre   | Game Stock |");
        putl("---------------------------------------------------------");
        _display_in_order(db->head);
        putl(" ");
        getenter("Press enter to continue...");
    }
}



void _menu_update_stock(AVLTree *db){
    GameInput input;
    validate(getline("Input game title[5-25][unique]: ", input.title),
             betweenstr(input.title, 5, 25));
    Game *game = search(db->head, input.title);
    if( game isempty ){
        putl("Data not found !");
        putl(" ");
        getenter("Press enter to continue...");
    }else{
        putl("Current stock: %d", game->stock);
        putl(" ");
        int add_or_remove;
        const int ADD = 0;
        const int REMOVE = 1;
        validate_int_from_choices_case(
            "Input udpate type[add|remove][canse insensitive]: ",
            add_or_remove,
            2, "add", "remove");
        if( add_or_remove == REMOVE ){
            int qty;
            validate(
                put("Input stock to remove[1-%d", game->stock);
                getint("]: ", qty),
                between(qty, 1, game->stock));
            game->stock -= qty;
            put("Data updated successfully !");
            if( game->stock == 0 ){
                putl("%s is removed from the warehouse !", game->title);
                db->head = delete_node(db->head, game);
            }
        }else if( add_or_remove == ADD ){
            int qty;
            validate(getint("Input stock to add[>=1]: ", qty), qty >= 1);
            game->stock += qty;
            putl("Data updated successfully !");
        }
        putl(" ");
        getenter("Press enter to continue...");
    }
}

int main()
{
    // Initialization
    AVLTree db= {0};
    db.head = insert(db.head, (GameInput){"Dota 4", 0, 50});
    db.head = insert(db.head, (GameInput){"Warcraft 4", 1, 75});
    db.head = insert(db.head, (GameInput){"Light of the Tomb Rider", 2, 27});
    db.head = insert(db.head, (GameInput){"Dota 1", 0, 50});
    db.head = insert(db.head, (GameInput){"Dota 2", 1, 50});
    db.head = insert(db.head, (GameInput){"Dota 10", 2, 50});
    db.head = insert(db.head, (GameInput){"Dota 3", 3, 50});
    db.head = insert(db.head, (GameInput){"Dota 8", 1, 50});
    db.head = insert(db.head, (GameInput){"Dota 6", 2, 50});

    // Execution
    bool running = true;
    while( running ){
        clr();
        putl("Bluejack GShop");
        putl("==============");
        putl("1. Insert Game");
        putl("2. View Game");
        putl("3. Update Stock");
        putl("4. Exit");
        
        int choice = 0;
        getint(">> ", choice);

        clr();
        if( choice == 1 ) _menu_insert_game(&db);
        if( choice == 2 ) _menu_view_game(&db);
        if( choice == 3 ) _menu_update_stock(&db);
        if( choice == 4 ) running = false;
    }
}