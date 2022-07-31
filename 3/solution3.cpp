#include<iostream>
#include<string>

// ?? =======================================
// ?? Alfon's Helper Method

// Clear Screen
//-------------------------
void clrscr()
{
    std::cout << std::basic_string(255, '\n');
}

// Padded String
//-------------------------
std::string pstr(std::string c, size_t pad, bool leftAligned = true)
{
    std::string res = "";
    if (pad <= c.length())
    {
        res = c;
        res = res.substr(pad);
    }else
    {
        std::string pads = std::basic_string( pad - c.length() , ' ');
        if (leftAligned)
        {
            res = c + pads;
        }else{
            res = pads + c;
        }
    }
    return res;
}

// Fast Print
//-------------------------
void p(std::string c){
    std::cout << c;
}

// Ask for Input (String)
//-------------------------
std::string promptInput(std::string prompt)
{
    std::cout << prompt;
    std::string str = "";
    getline(std::cin, str);
    return str;
}

// Ask for Input (Integer)
//-------------------------
int promptInteger(std::string prompt)
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
        catch(const std::exception& e)
        {
            accepted = false;
        }
        if (accepted)
        {
            break;
        }
    } while (1);
}

// Ask for Enter Key
//-------------------------
void promptAny(std::string prompt)
{
    std::cout << prompt;
    getchar();
}

// ?? End of Helper Method
// ?? ________________________________________

void printHeader()
{
    clrscr();
    std::cout << "Bluejack Hospital\n";
    std::cout << "=================\n";
    std::cout << "1. Insert\n";
    std::cout << "2. View\n";
    std::cout << "3. Next Queue\n";
    std::cout << "4. Exit\n";
}

class Node
{
private:
    std::string _name;
    int _age;
    std::string _desc;
    int _color;
    const std::string colors[3] = {"Green", "Yellow", "Red"};

public:
    std::string name() { return _name; }
    int age() { return _age; }
    std::string desc() { return _desc; }
    std::string colorstr() { return colors[_color-1]; }
    int color() { return _color; }
    Node *next;

    Node()
    {
        Node("unset", -1, "unset", -1);
    }

    Node(std::string pname, int page, std::string pdesc, int color)
    {
        _name = pname;
        _age = page;
        _desc = pdesc;
        _color = color;
        next = 0;
    }


    bool set_name(std::string val)
    {
        if(val.length() >= 4 && val.length() <= 25)
        {
            _name = val;
            return true;
        }
        return false;
    }


    bool set_age(int val)
    {
        if (val >= 0)
        {
            _age = val;
            return true;
        }
        return false;
    }

    bool set_desc(std::string str)
    {
        if (str.length() >= 6)
        {
            _desc = str;
            return true;
        }
        return false;
    }

    bool set_color(std::string str)
    {
        if (str == "Red" || str == "Yellow" || str == "Green"){
            if(str == "Red") _color = 3;
            if(str == "Yellow") _color = 2;
            if(str == "Green") _color = 1;
            return true;
        }
        return false;
    }
};

class GroupedLinkedList
{
private:
    Node *head;
    int _count;

public:
    GroupedLinkedList()
    {
        head = 0;
        _count = 0;
    }
    Node *peek() { return head; }
    int count() 
    {
        // std::cout << _count;
        return _count;
    }
    Node *pop() 
    {
        Node *temp = head;
        head = head->next;
        _count--;
        return temp;
    }

    void queue(Node *n)
    {
        if (n->color() == -1 || n->age() == -1 || n->name() == "unset" || n->desc() == "unset"){
            std::cout << n->color() << " " << n->age() << " " << n->name() << " " << n->desc() << "\n";
            std::cout << "what.";
            return;
        }

        if(!head){
            head = n;
        }else{
            if(n->color() > head->color())
            {
                n->next = head;
                head = n;
            }
            else
            {
                Node *curr = head;
                if(curr->next == NULL)
                {
                    curr->next = n;
                }else
                {
                    while (curr->next->color() > n->color() - 1)
                    {
                        curr = curr->next;

                        if(curr->next == NULL)
                            break;
                    }
                    n->next = curr->next;
                    curr->next = n;
                }
                
            }
        }
        _count++;
    }
};

main()
{

    GroupedLinkedList* db = new GroupedLinkedList();

    db->queue(new Node("Mr. Budi", 34, "Serious injury from car accident", 3));
    db->queue(new Node("Mr. John", 45, "GERD", 2));
    db->queue(new Node("Mrs. Carolina", 28, "Nausea, vomiting, sweating, and difficulties walking", 2));
    db->queue(new Node("Mr. Doe", 23, "Cough and fever", 1));

    std::string i_menu;
    do
    {
        printHeader();

        i_menu = promptInput("> ");

        if (i_menu == "1")
        {
            clrscr();
            Node *n = new Node();
            
            do
            {
                std::string name = promptInput("Input patient name[4-25]: ");
                if (n->set_name(name)) {
                    break;
                }
            } while (1);
            
            do
            {
                std::string i_age = promptInput("Input patient age[>= 0]: ");
                int age = -1;
                if(i_age[0] >= '0' && i_age[0] <= '9')
                {
                    age = std::stoi(i_age);
                    if (n->set_age(age))
                    {
                        break;
                    }
                }
            } while (1);
            
            do
            {
                std::string i_desc = promptInput("Input description[>= 6 characters]: ");
                if (n->set_desc(i_desc))
                {
                    break;
                }
                
            } while (1);
            
            do
            {
                std::string i_code = promptInput("Input code[Red|Yellow|Green]: ");
                if (n->set_color(i_code))
                {
                    break;
                }
                
            } while (1);

            db->queue(n);

            promptAny("Insert Success !");
        }
        else if (i_menu == "2")
        {
            clrscr();
            // std::cout << db->count() << " <- HERE!\n";
            if(db->count() == 0)
            {
                p("There is no queue yet !\n");

                promptAny("Press Enter to continue ...");
            }else
            {
                p("Patient List: \n");
                p("-------------------------------------------------------------------------------------------------------------\n");
                p("|No  | Name                      | Age  | Description                                             | Code    |\n");
                p("-------------------------------------------------------------------------------------------------------------\n");

                Node *rover = db->peek();
                int idx = 0;
                while(rover)
                {
                    idx++;
                    p("|" + pstr(std::to_string(idx), 4) + "| " + pstr(rover->name(), 26) + "| " + pstr(std::to_string(rover->age()), 5) + "| " + pstr(rover->desc(), 56) + "| " + pstr(rover->colorstr(), 8) + "|\n");
                    rover = rover->next;
                }
                p("-------------------------------------------------------------------------------------------------------------\n\n");

                promptAny("Press Enter to continue ...");
            }
            
            /* code */
        }
        else if (i_menu == "3")
        {
            clrscr();
            if(db->count() == 0)
            {
                p("There is no queue yet !\n\n");

                promptAny("Press Enter to continue ...");
            }else
            {
                Node *next_queue = db->pop();

                p("The next patient is:\n");
                p("" + pstr("Name", 15) + ": " + next_queue->name() + "\n");
                p("" + pstr("Age", 15) + ": " + std::to_string(next_queue->age()) + "\n");
                p("" + pstr("Description", 15) + ": " + next_queue->desc() + "\n");
                p("" + pstr("Code", 15) + ": " + next_queue->colorstr() + "\n");
                p("\n");
                promptAny("Press Enter to continue ...");

                free(next_queue);
            }
        }

    } while (i_menu != "4");

    return 0;
}

