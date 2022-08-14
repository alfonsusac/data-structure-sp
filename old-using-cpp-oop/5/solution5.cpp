#include <iostream>
#include <string>

// ?? =======================================
// ?? Alfon's Helper Method

namespace U
{
    static void clrscr()
    {
        std::cout << std::basic_string(255, '\n');
    }
    // Padded String
    //-------------------------
    static std::string pstr(std::string c, size_t pad, bool leftAligned = true, char space = ' ')
    {
        std::string res = "";
        if (pad <= c.length())
        {
            res = c;
            res = res.substr(pad);
        }
        else
        {
            std::string pads = std::basic_string(pad - c.length(), space);
            if (leftAligned)
            {
                res = c + pads;
            }
            else
            {
                res = pads + c;
            }
        }
        return res;
    }

    // Fast Print
    //-------------------------
    static void p(std::string c)
    {
        std::cout << c;
    }

    // Ask for Input (String)
    //-------------------------
    static std::string promptInput(std::string prompt)
    {
        std::cout << prompt;
        std::string str = "";
        getline(std::cin, str);
        return str;
    }
    // Ask for Input (Integer)
    //-------------------------
    static int promptInteger(std::string prompt)
    {
        do
        {
            std::cout << prompt;
            std::string str = "";
            getline(std::cin, str);
            bool accepted = true;
            int res = 0;
            try
            {
                res = stoi(str);
            }
            catch (const std::exception &e)
            {
                accepted = false;
            }
            if (accepted)
            {
                return res;
            }
        } while (1);
    }

    // Ask for Enter Key
    //-------------------------
    static void promptAny(std::string prompt)
    {
        std::cout << prompt;
        getchar();
    }

    // Ask for Choice
    //-------------------------
    static std::string promptChoice(std::string choice[], size_t choice_count, std::string promptWithoutChoice)
    {
        if(choice_count < 2)
            throw std::invalid_argument("choice must have more than 1 choices");

        std::string options = "["+choice[0];
        for (size_t i = 1; i < choice_count; i++)
        {
            options = options + "|" + choice[i];
        }
        options += "]";

        do
        {
            std::string input = U::promptInput(promptWithoutChoice + options + ": ");
            for (size_t i = 0; i < choice_count; i++)
            {
                if (input == choice[i]) 
                {
                    return input;
                }
            }
            
        } while (1);
        return "";
    }
}

// ?? End of Helper Method
// ?? ________________________________________

void printMenu()
{
    std::cout << "Bluejack\n";
    std::cout << "=================\n";
    std::cout << "1. Process Order\n";
    std::cout << "2. View All Customer\n";
    std::cout << "3. Remove Customer\n";
    std::cout << "4. Exit\n";
}

class Customer
{
private:
    std::string _name;
    std::string _phonenum;
    std::string _email;
    int _points;

public:
    Customer *left, *right;
    Customer(std::string pname, std::string pphone, std::string pemail, int ppoint)
    {
        _name = pname;
        _phonenum = pphone;
        _email = pemail;
        _points = ppoint;
        left = right = 0;
    }
    Customer() : Customer("", "", "", 0)
    {
    }
    std::string name() { return _name; }
    std::string phone() { return _phonenum; }
    std::string email() { return _email; }
    int points() { return _points; }

    bool set_name(std::string n_name)
    {
        if (n_name.starts_with("Mr. ") || n_name.starts_with("Mrs. "))
            if (n_name.length() >= 5 && n_name.length() <= 25)
            {
                _name = n_name;
                return true;
            }

        return false;
    }

    bool set_phone(std::string n_phone)
    {
        if (n_phone.length() >= 10 && n_phone.length() <= 13)
        {
            _phonenum = n_phone;
            return true;
        }
        return false;
    }

    bool set_email(std::string n_email)
    {
        int state = 0;
        for(auto c : n_email)
            if(c == '@' && state == 0)
                state++;
        if (state == 0)
            return false;
        else if (state == 1 && (n_email.ends_with(".com") || n_email.ends_with(".co.id")))
            if (n_email.length() >= 10 && n_email.length() <= 20)
            {
                _email = n_email;
                return true;
            }
        return false;
    }
    
    bool set_points(int n_points)
    {
        if(n_points >= 0)
        {
            _points = n_points;
            return true;
        }
        return false;
    }

    void assign(Customer *n_cust)
    {
        _name = n_cust->name();
        _phonenum = n_cust->phone();
        _email = n_cust->email();
        _points = n_cust->points();
    }
    void add_points(int n)
    {
        _points += n;
    }
};

class BST
{
public:
    Customer *root;

private:
    int count;
    Customer *_insert(Customer *_root,Customer *new_node)
    {
        if (_root == 0)
        {
            return new_node;
        }

        if ( new_node->phone() < _root->phone())
        {
            _root->left = _insert(_root->left, new_node);
        }
        else if (new_node->phone() > _root->phone())
        {
            _root->right = _insert(_root->right, new_node);
        }
        else
        {
            throw std::invalid_argument("Customer Already Exist!");
        }
        return _root;
    }

    Customer *_predecessor(Customer* _root)
    {
        if (_root->left)
        {
            Customer *tmp = _root->left;
            while (tmp->right)
                tmp = tmp->right;
            return tmp;
        }
        throw std::invalid_argument("Invalid Arguments: Root!\n");
        return 0;
    }

    Customer *_remove(Customer* _root, std::string phone_num)
    {
        if (_root == 0) return _root;
        if (phone_num < _root->phone())
        {
            _root->left = _remove(_root->left, phone_num);
        }
        else if (phone_num > _root->phone())
        {
            _root->right = _remove(_root->right, phone_num);
        }
        else if (phone_num == _root->phone())
        {
            if (_root->left == 0) // Right Child or no child only
            {
                Customer *tmp = _root->right;
                free(_root);
                return tmp;
            }
            else if (_root->right == 0) // Left Child only
            {
                Customer *tmp = _root->left;
                free(_root);
                return tmp;
            }
            else // has both child
            {
                Customer *tmp = _predecessor(_root);
                _root->assign(tmp);
                _root->left = _remove(_root->left, tmp->phone());
            }
        }
        else
        {
            throw std::invalid_argument("Phone Number Not Found");
        }
        return _root;
    }
    Customer* _search(Customer* _root, std::string phone_num)
    {
        if (_root == 0 ){
            return 0;
        }
        if (phone_num < _root->phone())
        {
            return _search(_root->left, phone_num);
        }
        else if (phone_num > _root->phone())
        {
            return _search(_root->right, phone_num);
        }
        else if (phone_num == _root->phone())
        {
            return _root;
        }
        return 0; // not found
    }
    Customer* _clear(Customer* _root)
    {
        if (_root == 0) 
        {
            return 0;
        }
        if (_root->left)
        {
            _root->left = _clear(root->left);

        }
        if (_root->right)
        {
            _root->right = _clear(root->right);
        }
        delete _root;
        return 0;
    }

public:
    BST()
    {
        root = 0;
    }
    int Count() { return count; }
    void insert(Customer *n)
    {
        root = _insert(root, n);
    }
    void remove(std::string phone_num)
    {
        root = _remove(root, phone_num);
    }
    Customer* search(std::string phone_num)
    {
        return _search(root, phone_num);
    }
    void clear()
    {
        root = _clear(root);
    }
};

class OrderDetail
{
private:
    std::string _drink_name;
    int _qty;
    int _subtotal;
    bool _pointApplied;

public:
    static size_t drink_names_counts;
    static std::string drink_names[];

    OrderDetail *next;
    std::string drink_name() { return _drink_name; }
    int qty() { return _qty; }
    int subtotal() { return _subtotal; }

    bool set_drink_name(std::string n_name)
    {
        for (size_t i = 0; i < drink_names_counts; i++)
        {
            if (drink_names[i] == n_name)
            {
                _drink_name = n_name;
                return true;
            }
        }
        return false;
    }
    bool set_qty(int n_qty)
    {
        if (n_qty >= 1)
        {
            _qty = n_qty;
            _subtotal = _qty * 30000;
            return true;
        }
        return false;
    }
    void apply_points(int *points)
    {
        if (*points >= _qty)
        {
            _subtotal = 0;
            *points = *points - _qty;
        }
        else if (*points < _qty)
        {
            _subtotal -= (*points * 30000);
            *points = 0;
        }
    }
};

size_t OrderDetail::drink_names_counts = 4;
std::string OrderDetail::drink_names[] =
    {
        "Cafe Latte",
        "Caramel Macchiato",
        "Cappuccino",
        "Cafe Mocha"};

class Order
{
private:
    Customer *cust;
    OrderDetail *head;
    OrderDetail *tail;
    int total;
    int points_obtained;

public:
    Order(Customer* _cust)
    {
        cust = _cust;
        head = tail = 0;
        total = points_obtained = 0;
    }
    void Insert(OrderDetail* _order_detail)
    {
        if (_order_detail->qty() == 0 || _order_detail->drink_name() == "")
        {
            throw std::invalid_argument("OrderDetail is not initialized!");
        }
        if (head == 0)
        {
            head = _order_detail;
            tail = _order_detail;
        }
        else
        {
            tail->next = _order_detail;
            tail = _order_detail;
        }

        total += _order_detail->subtotal();
    }

    void FinalizeOrder()
    {
        U::p("Order summary:\n");

        for (OrderDetail *rover = head; rover != 0;)
        {
            OrderDetail *tmp = rover;
            U::p(U::pstr(rover->drink_name(), 18)+"-"+U::pstr(std::to_string(rover->qty()),3,false)+"x = "+U::pstr(std::to_string(rover->subtotal()),6,false)+'\n');
            rover = rover->next;
            delete tmp;
        }
        U::p("Total: " + std::to_string(total));

        points_obtained = (total / 50000) * 3;
        cust->set_points(points_obtained);
    }
};

void ProcessOrder(BST * db)
{

    int free_drinks = 0;
    Customer *customer = new Customer();
    std::string q_phone = "";
    do
    {
        q_phone = U::promptInput("Input phone number[10-13][numeric]: ");
    } while (!customer->set_phone(q_phone));

    Customer *existing = db->search(q_phone);
    if (existing && existing->points() >= 25)
    {
        customer = existing;
        std::string use_points;
        do {
            use_points = U::promptInput("Do you want to use your points[You have " + std::to_string(customer->points()) + "[y|n]: ");
        } while (use_points != "y" && use_points != "n");
        if (use_points == "y")
        {
            int how_many_points = 0;
            do
            {
                how_many_points = U::promptInteger("How much[" + std::to_string(customer->points()) + " left]: ");
            } while (how_many_points % 25 != 0 && how_many_points < 25);
            free_drinks += (how_many_points / 25);
        }
    }
    else
    {
        do { } while (!customer->set_name(U::promptInput("Input name[5-25][Mr. |Mrs. ]: ")));
        do { } while (!customer->set_email(U::promptInput("Input email[10-20][email format]: ")));

        customer->set_points(10);
        db->insert(customer);
    }

    Order order = Order(customer);
    U::p("\nYou have " + std::to_string(free_drinks) + " free drink(s) left.\n\n");
    std::string order_more = "";
    do
    {
        OrderDetail *n_drink = new OrderDetail();
        do { } while (!n_drink->set_drink_name(U::promptInput("Input drink[Cafe Latte|Caramel Macchiato|Cappuccino|Cafe Mocha]: ")));
        do { } while (!n_drink->set_qty(U::promptInteger("Input drink quantity[>=1]: ")));
        n_drink->apply_points(&free_drinks);
        order.Insert(n_drink);

        order_more = U::promptInput("Do you want to order more?[y|n]: ");
        if(order_more == "n")
        {
            break;
        }

    } while (order_more == "y" && order_more != "n");

    order.FinalizeOrder();
    U::promptAny("");

}

void printCustomer(Customer* root)
{
    if (root == 0)
        return;

    if (root->left)
        printCustomer(root->left);

    U::p("| " +U::pstr(root->name(),26)+"| " +U::pstr(root->phone(),14)+"| " +U::pstr(root->email(),21)+"| " +U::pstr(std::to_string(root->points()),7)+"|\n");
    U::p(std::basic_string(77, '-') + '\n');

    if (root->right)
        printCustomer(root->right);

    return;
}

void ViewAllCustomer(BST *db)
{
    if (db->root == 0)
    {
        U::p("There is no data!\n");
    }
    else
    {
        U::p(std::basic_string(77, '-')+'\n');
        U::p("| Name                      | Phone Number  | Email                | Points |\n");
        U::p(std::basic_string(77, '-')+'\n');
        printCustomer(db->root);
    }

    U::promptAny("\nPress Enter to continue...");

    // -----------------------------------------------------------------------------
    // | Name                      | Phone Number  | Email                | Points |
    // -----------------------------------------------------------------------------
    // | Douglas                   | 081299123118  | douglas@gmail.com    | 14     |
    // -----------------------------------------------------------------------------
    // | Ryan                      | 081288246117  | ryan@yahoo.co.id     | 28     |
    // -----------------------------------------------------------------------------
}
void RemoveCustomer(BST *db)
{
    if (db->root == 0)
    {
        U::p("There is no data !\n\n");
        U::promptAny("Press Enter to continue ...\n");
    } 
    else
    {        
        Customer *tmp = new Customer();
        do { } while (!tmp->set_phone(U::promptInput("Input phone number: ")));
        Customer *r_cust = db->search(tmp->phone());
        if (r_cust)
        {
            db->remove(r_cust->phone());
            U::promptAny("Delete success !\n\n");
        }
        else
        {
            U::promptAny("Data invalid !\n\n");
        }
    }
}
void ExitProgram(BST *db)
{
    db->clear();
}

int main()
{
    BST *db = new BST();
    db->insert(new Customer("Douglas", "081299123118", "douglas@gmail.com", 55));
    db->insert(new Customer("Ryan", "081288246117", "ryan@yahoo.co.id", 28));

    std::string i_menu = "";
    do
    {
        U::clrscr();
        printMenu();
        
        i_menu = U::promptInput(">> ");
        if (i_menu == "1")
        {
            U::clrscr();
            ProcessOrder(db);
        }
        else if (i_menu == "2")
        {
            U::clrscr();
            ViewAllCustomer(db);
        }
        else if (i_menu == "3")
        {
            U::clrscr();
            RemoveCustomer(db);
        }
        else if (i_menu == "4")
        {
            U::clrscr();
            ExitProgram(db);
            return 1;
        }
    } while (1);
}



