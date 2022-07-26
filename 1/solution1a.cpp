#include<iostream>
#include<string>
#include<limits>
using namespace std;

struct cake{
    string  code;
    string  name;
    int     stock;
    int     price;
};

cake cakelist[] = {
    {"CK001", "Blueberry Cake",        13,  25000},
    {"CK009", "Chocochip Cake",         5,  20000},
    {"CK017", "Mayonaise Cake",        24,  30000},
    {"CK023", "Strawberry ShortCake",   7,  17500}};
int listcount = 4;

int findCakeInList(string _cakeid){
    for (int i = 0; i < listcount; i++)
        if(_cakeid == cakelist[i].code)
            return i;
    return -1;
}

int askForCakeCodeFromList(){
    string i_cakecode = "";
    int t_index = -1;
    while(1){
        cout << "Input Cake Code [5 chars]: "; // Ask user input     
        getline(cin, i_cakecode);
        t_index = findCakeInList(i_cakecode);

        if( i_cakecode.length() == 5  && t_index != -1 )    // Validation
            return t_index;
        else{
            cout << "--- The Cake Code doesn’t exist ---\n";
            getchar();
        }
    }
}

int askForQtyWithinLimit(int limit, string err){
    int t_qty = 0;
    while(1){
        string i_qty; // Ask user input
        cout << "Input Quantity [0.." << limit << "]:";
        getline(cin, i_qty);

        t_qty = stoi(i_qty); // Convert string to integer

        if( t_qty >= 0 && t_qty <= limit ) // Validation
            return t_qty;
        else{
            cout << err << "\n";
            getchar();
        }
    }
}

string displayMenuandAskInput(){
    string temp;

    // * Prints the menu
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << " BLUE CAKE SHOP CASHIER\n";
    cout << " ======================\n\n";
    cout << " No. | Cake Code | Cake Name            | Available | Price\n";
    cout << " ---------------------------------------------------------------\n";
    for (int i = 0; i < listcount; i++){

        string d_code = cakelist[i].code;
        d_code.append(9 - d_code.length(), ' ');
        string d_num = to_string(i + 1);
        d_num.insert(d_num.begin(), 2 - d_num.length(), '0');
        d_num.append(".");
        string d_name = cakelist[i].name;
        d_name.append(20 - d_name.length(), ' ');
        string d_stock = to_string(cakelist[i].stock);
        d_stock.insert(d_stock.begin(), 9 - d_stock.length(), ' ');
        cout << " " << d_num << " | " << d_code << " | " << d_name << " | " << d_stock << " | Rp. " << cakelist[i].price << ",-\n";
    }
    cout << " ---------------------------------------------------------------\n\n";
    cout << " Menu :\n 1. Sell\n 2. Add Stock\n 3. Exit\n Input choice : ";

    // * Asks for input
    cin >> temp;
    getchar();

    // * Return Input
    return temp;
}

int main(){
    string input = "";

    // Repeat Menu when not exit
    while (input != "3"){
        // Asks for input
        input = displayMenuandAskInput();

        // > User inputted 1 -> sell cake
        if(input == "1"){
            // * Asking for cake code
            int index = askForCakeCodeFromList();

            // * Asking for quantity
            int cakestock = cakelist[index].stock;
            int v_qty = askForQtyWithinLimit(
                cakestock,
                "...The quantity of cake is not enough...");

            // * Calculate total price
            int totalprice = cakelist[index].price * v_qty;

            // * Print total price
            cout <<  "Total Price is : Rp" << totalprice << ",-\n";

            // * Subtract available cakes
            cakelist[index].stock -= v_qty;
            cout << "\n\n--- Thank You ---\n";
        }
        // > User inputted 2 -> add stock
        else if(input == "2")
        {
            // * Asking for cake code
            int index = askForCakeCodeFromList();

            // * Asking for quantity
            int cakestock = cakelist[index].stock;
            int v_qty = askForQtyWithinLimit(
                10,
                "");

            // * Adding quantity to array
            cakelist[index].stock += v_qty;
            cout << "\n\n--- Adding Stock Success ---\n";
        }
    }
    return 1;
}