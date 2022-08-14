#include "util.h"

STRUCT BTNode{
    char name[MAX_STR_LENGTH], phone[MAX_STR_LENGTH], email[MAX_STR_LENGTH];
    int points;
    struct BTNode *left, *right;
}Customer;
Customer *head = 0; // ! Global Variable
STRUCT Input{
    char name[MAX_STR_LENGTH], phone[MAX_STR_LENGTH], email[MAX_STR_LENGTH];
}Input;
Customer* new_customer(Input n, int points){
    new_struct(Customer, node);
    strcpy(node->name, n.name);
    strcpy(node->phone, n.phone);
    strcpy(node->email, n.email);
    node->points = points ? points : 10;
    node->left = node->right = 0;
    return node;
}
void copy_customer(Customer* to, Customer* from){
    strcpy(to->name, from->name);
    strcpy(to->phone, from->phone);
    strcpy(to->email, from->email);
    to->points = from->points;
}
Customer *_insert(Customer *root, Customer *new_node){
    if( root == 0 ) return new_node;
    if( scmp(new_node->phone, <, root->phone))
        root->left = _insert(root->left, new_node);
    else 
    if( scmp(new_node->phone, >, root->phone) )
        root->right = _insert(root->right, new_node);
    else put("ERR: Customer Already Exists!\n");
    return root;
}
Customer *predecessor(Customer* root){
    if( root->left ){
        Customer *c = root->left;
        while( c->right )
            c = c->right;
        return c;
    }
    else put("ERR: Root doesnt have left subtree");
    return 0;
}
Customer *_search(Customer *root, char* phone){
    if( root is 0 ) return root; // not found!!
    if( scmp(phone, <, root->phone) )
        return _search(root->left, phone);
    else
    if( scmp(phone, >, root->phone) )
        return _search(root->right, phone);
    else
    if( scmp(phone, == ,root->phone ) ){
        return root; // found!!
    }
    return 0; //unreachable
}

Customer *_remove(Customer *root, Customer* cust){
    if( root is 0 ) return root;
    if( scmp(cust->phone, <, root->phone) )
        root->left = _remove(root->left, cust);
    else
    if( scmp(cust->phone, >, root->phone) )
        root->right = _remove(root->right, cust);
    else
    if( root == cust ){
        Customer *tmp;
        if( root->left is 0 ){          // Right Child or No Child
            tmp = root->right;
            free(root);
            return tmp;
        }else if( root->right is 0 ){   // Left Child Only
            tmp = root->left;
            free(root);
            return tmp;
        }else{                          // Has Both Child
            tmp = predecessor(root);
            copy_customer(root, tmp);
            root->left = _remove(root->left, tmp);
        }
    }else
        put("ERR: Phone Number Not Found!");
    return root;
}
Customer* _clear(Customer *root){
    if( root is NULL) return 0;
    if( root->left ) root->left = _clear(root->left);
    if( root->right )root->right= _clear(root->right);
    free(root);
    return NULL;
}
void insert_customer(Customer *new_node) { 
    head = _insert(head, new_node);  
}
void remove_cust(Customer *cust) {
    head = _remove(head, cust);  
}
Customer* search(char *phone) {
    return _search(head, phone);
}
void clear() {
    _clear(head);
}


const int drink_names_count = 4;
const char* const drink_name[] = {
    "Cafe Latte",
    "Caramel Macchiato",
    "Cappuccino",
    "Cafe Mocha"};
STRUCT LLNode{
    int  drink_id;
    int  qty;
    int  subtotal;
    bool points_applied;
    struct LLNode *next;
}Order;

STRUCT OrderInput{
    int  drink_id;
    int  qty;
    int  subtotal;
}OrderInput;

bool is_email(char *str){
    int len = strlen(str);
    int state = 0;
    const int BEFOREAT = 1;
    const int ATSYMBOL = 2;
    const int AFTERAT = 3;
    for( range(len) ){
        if( !state and isalpha(str[i]) ){
            state = BEFOREAT;
        }
        if( state is BEFOREAT and str[i] == '@' ){
            state = ATSYMBOL;
        }
        if( state is ATSYMBOL and isalpha(str[i]) ){
            state = AFTERAT;
        }
        // Not the best solution
        if( state is AFTERAT and len >= 6 ){
            if( str[len - 4] == '.' 
            and str[len - 3] == 'c'
            and str[len - 2] == 'o'
            and str[len - 1] == 'm' ){
                return true;
            }
            if( str[len  - 6] == '.' 
            and str[len - 5] == 'c'
            and str[len - 4] == 'o'
            and str[len - 3] == '.'
            and str[len - 2] == 'i'
            and str[len - 1] == 'd'){
                return true;
            }
        }
    }
    return false;
}

void _menu_process_order(){
    Input input;
    loop(
        validate(getline("Input phone numer[10-13][numeric]: ", input.phone), between(strlen(input.phone), 10, 13));
        break_if_numeric(input.phone););
    Customer* customer = search(input.phone);
    int free_drinks = 0;

    if( customer is NULL ){
        validate(getline("Input name[5-25][Mr. |Mrs. ]: ", input.name),
                 betweenstr(input.name, 5, 25) and
                     (starts_with(input.name, "Mr. ") ||
                      starts_with(input.name, "Mrs. ")));
        validate(getline("Input email [10-20][email format]: ", input.email), betweenstr(input.email, 10, 20) and is_email(input.email));
        customer = new_customer(input,0);
        insert_customer(customer);
    }else if( customer isnot NULL and customer->points >= 25 ){
        bool use_points = 0;
        validate_yn("Do you want to use your points[You have %d]", use_points, customer->points);
        if( use_points ){
            int how_many = 0;
            validate(
                put("How much[%d left]:",customer->points);getint(" ", how_many);,
                how_many % 25 == 0 and how_many >= 25
            );
            free_drinks += how_many / 25;
        }
    }

    put("\n");
    put("You have %d free drink(s) left.\n",free_drinks);
    put("\n");
    

    Order order[MAX_STR_LENGTH];
    int curr_ord = 0;

    bool want_to_order_more = false;
    do{
        
        validate_int_from_array("Input drink[Cafe Latte|Caramel Macchiato|Cappuccino|Cafe Mocha]: ",
                                order[curr_ord].drink_id, drink_names_count, drink_name);

        validate(getint("Input drink quantity [>=1]: ", order[curr_ord].qty), order[curr_ord].qty >= 1);
        validate_yn("Do you want to order more?[y|n]: ", want_to_order_more);
        order[curr_ord].subtotal = order[curr_ord].qty * 30000;
        if (free_drinks >= order[curr_ord].qty){
            order[curr_ord].subtotal = 0;
            free_drinks = free_drinks - order[curr_ord].qty;
        }else if (free_drinks < order[curr_ord].qty){
            order[curr_ord].subtotal -= (free_drinks * 30000);
            free_drinks = 0;
        }
        curr_ord++;
    } while( want_to_order_more and curr_ord < MAX_STR_LENGTH);

    put("Order summary:\n");
    int total = 0;
    for( range(curr_ord) ){
        put("%-18s - %2dx = %d\n", drink_name[order[i].drink_id], order->qty, order->subtotal);
        total += order[i].subtotal;
    }
    put("Total: %d\n",total);

    int points_obtained = (total / 50000) * 3;
    customer->points += points_obtained;
    getenter("Points Obtained: %d", points_obtained);
}

void printCustomer(Customer* root){
    if( root is NULL ) return;
    if( root->left ) printCustomer(root->left);
    put("| %-25s | %-13s | %-20s | %-6d |\n", root->name, root->phone, root->email, root->points);
    put("-----------------------------------------------------------------------------\n");
    if( root->right ) printCustomer(root->right);
}

void _menu_view_all_customer(){
    if( head is NULL ){
        put("There is no data!\n");
        put("\n");
        getenter("Press Enter to continue ...\n");
    }else{
        put("-----------------------------------------------------------------------------\n");
        put("| Name                      | Phone Number  | Email                | Points |\n");
        put("-----------------------------------------------------------------------------\n");
        printCustomer(head);

        put("\n");
        getenter("Press Enter to continue ... \n");
    }
}
void _menu_remove_customer(){
    if( head is NULL ){
        put("There is no data!\n");
        put("\n");
        getenter("Press Enter to continue ...\n");
    }else{
        Input input;
        getline("Input phone number: ", input.phone);
        Customer *customer = search(input.phone);
        if( customer isnot NULL ){
            remove_cust(customer);
            put("Delete success !\n");
            put("\n");
            getenter("Press Enter to continue ...\n");
        }else{
            put("Data invalid !\n");
            put("\n");
            getenter("Press Enter to continue ...\n");
        }
    }
}
int main(){
    // Initialization
    insert_customer(new_customer((Input){"Douglas", "081299123118", "douglas@gmail.com"}, 55));
    insert_customer(new_customer((Input){"Ryan", "081288246117", "ryan@yahoo.co.id"}, 28));

    // Execution
    bool running = true;
    while( running ){

        clr();
        put("Bluejacks\n");
        put("==================\n");
        put("1. Process Order\n");
        put("2. View All Customer\n");
        put("3. Remove Customer\n");
        put("4. Exit\n");

        int choice = 0;
        getint(">> ", choice);

        clr();
        if( choice == 1 ) _menu_process_order();
        if( choice == 2 ) _menu_view_all_customer();
        if( choice == 3 ) _menu_remove_customer();
        if( choice == 4 ) running = false;

    }
}
