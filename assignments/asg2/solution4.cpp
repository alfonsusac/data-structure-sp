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
}

// ?? End of Helper Method
// ?? ________________________________________

void printMenu()
{
    std::cout << "Bluejack Library\n";
    std::cout << "=================\n";
    std::cout << "1. View Book\n";
    std::cout << "2. Insert Book\n";
    std::cout << "3. Remove Book\n";
    std::cout << "4. Exit\n";
}

class Book
{
private:
    static int last_id;

    std::string _id;
    std::string _title;
    std::string _author;
    std::string _isbn;
    int _pagenum;

public:
    Book(std::string ptitle, std::string pauthor, std::string pisbn, int ppagenum)
    {
        _title = ptitle;
        _author = pauthor;
        _isbn = pisbn;
        _pagenum = ppagenum;

        set_id();
    }
    Book()
    {
        Book("", "", "", 0);
    }

    void set_id()
    {
        if (_id != "") return;
        if (_author == "") return;
        if (_isbn == "") return;
        if (_author == "") return;

        last_id += 1;
        _id = "B" + U::pstr(std::to_string(last_id), 5, false, '0') + "-" + _isbn + "-" + _author[0] + _title[0];
        std::cout << "New Book ID : " << _id << '\n';
    }

    std::string id() { return _id; }
    std::string title() { return _title; }
    std::string author() { return _author; }
    std::string isbn() { return _isbn; }
    int pagenum() { return _pagenum; }

    bool set_title(std::string new_title)
    {
        if (new_title.length() <= 50 && new_title.length() >= 5)
        {
            _title = new_title;
            return true;
        }
        return false;
    }

    bool set_author(std::string new_author)
    {
        if ((new_author.starts_with("Mr. ") || new_author.starts_with("Mrs. ")) && new_author.length() >= 3 && new_author.length() <= 25)
        {
            _author = new_author;
            return true;
        }
        return false;
    }

    bool set_isbn(std::string new_isbn)
    {
        if(new_isbn.length() >= 10 && new_isbn.length() <= 13)
        {
            for (char i : new_isbn)
            {
                if (!isdigit(i))
                    return false;
            }
            _isbn = new_isbn;
            return true;
        }
        return false;
    }

    bool set_pagenum(int new_pagenum)
    {
        if (new_pagenum >= 16)
        {
            _pagenum = new_pagenum;
            return true;
        }
        return false;
    }

    bool hashKeyGenerated;
    int hashKey(int size)
    {
        if (_id == "") throw std::logic_error("ID is not yet set");
        
        int sum = 0;
        for(char i : _id)
        {
            sum += i;
        }
        std::cout << "HashKey = " << sum % size << '\n';
        return sum % size;
    }
};
int Book::last_id = 0; // Initializing

class Node
{
public:
    Book *data;
    Node *next;

    Node(Book* b)
    {
        data = b;
        next = 0;
    }
};

class HashTable
{
public: 
    const static int SIZE = 1007;

private:
    
    Node *head[SIZE];
    Node *tail[SIZE];

public:
    bool insert(Book* b)
    {
        b->set_id();
        int index = b->hashKey(SIZE);
        Node *n_node = new Node(b);
        if(head[index] == NULL)
        {
            head[index] = tail[index] = n_node;
            return true;
        }
        else
        {
            Node *rover = head[index];

            // has to be unique
            while(rover != 0)
            {
                if(rover->data->title() == b->title())
                    return false;
                rover = rover->next;
            }

            tail[index]->next = n_node;
            tail[index] = n_node;
            return true;
        }
        return false;
    }
    bool remove(Book* b)
    {
        int key = b->hashKey(SIZE);
        free(b);
        if (tail[key] == head[key])                 // * If hashmap has single element
        {
            tail[key] = 0;                              // Set head and tail back to null
            head[key] = 0;
        } 
        else                                        //  * If Multiple Elemennt
        {
            if (b == head[key]->data)                   // * If at head.
            {
                head[key] = head[key]->next;                // Set Head Key as next node.
            }
            else                                        // * If not at head
            {
                Node *rover = head[key]->next;
                while(rover->next != 0)                     // * Loop until found
                {
                    if (rover->next->data == b)                 // * If found
                    {
                        if (rover->next->next != 0)                 // * If in the middle,
                        {
                            rover->next = rover->next->next;            // Set the previous node to link to next node
                            return true;
                        }
                        else                                        // * If at the end
                        {
                            rover->next = 0;                            // Set the next node of prev node as null.
                            tail[key] = rover;                          // Mark current node as the previous node.
                            return true;
                        }
                    }
                    rover = rover->next;                    // Move rover to next node
                }
            }
        }
        return false;
    }

    Book* search(std::string n_name)
    {
        for (size_t i = 0; i < SIZE; i++)
        {
            if (head[i] != 0)
            {
                Node *rover = head[i];
                while(rover != 0)
                {
                    if(rover->data->title() == n_name)
                        return rover->data;
                }
            }
        }
        return 0;
    }

    void view()
    {
        U::p(std::basic_string(139, '-') + '\n');
        U::p("| " + U::pstr("Book ID", 24) + "| " + U::pstr("Book Title", 51) + "| " + U::pstr("Book Author", 26) + "| " + U::pstr("ISBN", 15) + "| " + U::pstr("Page Number", 16) + "|\n");
        U::p(std::basic_string(139, '-') + '\n');
        for (int i = 0; i < SIZE; i++)
        {
            if(head[i] != 0)
            {
                Node *rover = head[i];
                while (rover != 0)
                {
                    U::p(
                        "| " + U::pstr(rover->data->id(), 24) 
                        + "| " + U::pstr(rover->data->title(), 51) 
                        + "| " + U::pstr(rover->data->author(), 26) 
                        + "| " + U::pstr(rover->data->isbn(), 15) 
                        + "| " + U::pstr(std::to_string(rover->data->pagenum()), 16) + "|\n");
                    U::p(std::basic_string(139, '-') + '\n');
                    rover = rover->next;
                }
            }
        }
    }
};

int main()
{
    HashTable *db = new HashTable();
    db->insert(new Book("Don't Make Me Think", "Mr. Krug S.", "9780321344755", 106));
    db->insert(new Book("Agile Project Management With Scrum", "Mr. Ken Schwaber", "9780735619937", 192));

    std::string i_menu = "";

    do
    {
        U::clrscr();

        printMenu();

        i_menu = U::promptInput(">> ");

        if (i_menu == "1")
        {
            U::clrscr();
            // Print Table Here
            db->view();

            U::promptAny("Press Enter to continue ...\n");
        }
        else if (i_menu == "2")
        {
            U::clrscr();
            Book* n_book = new Book();

            do
            {
                std::string str = U::promptInput("Input book title[5-50][unique]: ");
                if (db->search(str))
                {
                    U::p("The book title is already exists !\n");
                    continue;
                }
                if (n_book->set_title(str))
                {
                    break;
                }
            } while (1);

            do
            {
            } while (n_book->set_author(U::promptInput("Input author name[3-25][Mr. |Mrs. ]: ")));
            
            do
            {
            } while (n_book->set_isbn(U::promptInput("Input ISBN[10-13][numeric]")));

            do
            {
            } while (n_book->set_pagenum(U::promptInteger("Input page number[>= 16]: ")));

            db->insert(n_book);

            U::promptAny("Insert success !\n\n");
        }
        else if (i_menu == "3")
        {
            U::clrscr();
            std::string name_to_remove = U::promptInput("Input book id to delete: ");
            Book *s_book = db->search(name_to_remove);
            if(s_book)
            {
                U::p("Book Id: " + s_book->id());
                U::p("Book Title: " + s_book->title());
                U::p("Book Author: " + s_book->author());
                U::p("Book ISBN: " + s_book->isbn());
                U::p("Page Number: " + s_book->pagenum());

                std::string confirmation = "";
                do
                {
                    confirmation = U::promptInput("Are you sure [y|n]? ");
                } while (confirmation != "y" && confirmation != "n");

                if (confirmation == "y")
                {
                    db->remove(s_book);
                    U::p("Delete success !");
                }
                
                

            }
            else
            {
                U::promptAny("\nBook not found !");
            }
        }
        
        
        

        /* code */
    } while (i_menu != "4");
}