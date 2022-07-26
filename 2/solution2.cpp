#include <string>
#include <iostream>
using namespace std;

int countWords(string str);
void printHeader();
string askSentence();
bool askToContinue();

class Node
{
    public:
        char data;
        Node *next;
        Node(char _data, Node* _next)
        {
            data = _data;
            next = _next;
        }
};

class LinkedList
{
    public:
        Node *head;
        LinkedList()
        {
            head = NULL;
        }
        void print()
        {
            cout << "The resultn is: ";
            Node *rover = head;
            while (rover != NULL)
            {
                cout << rover->data << ' ';
                rover = rover->next;
            }
            cout << "\n\n";
        }
        void pushHead(char data)
        {
            Node *n = new Node(data, head);
            head = n;
        }
        void clearll()
        {
            Node *rover = head;
            while (rover != NULL)
            {
                Node *tmp = rover;
                rover = rover->next;
                free(tmp);
            }
            head = NULL;
        }
};

// > MAIN CLASS

int main()
{
    LinkedList* list = new LinkedList();
    string input = "";

    do
    {
        list->clearll();

        printHeader();

        string i_sentence = "";
        do
        {
            i_sentence = askSentence();
        }
        while (countWords(i_sentence) < 5);

        for (char i : i_sentence)
        {
            list->pushHead(i);
        }

        list->print();

    } while (askToContinue());
}

bool askToContinue(){

    string str = "";
    do
    {
        cout << "Do you want to continue [yes|no] ? ";
        getline(cin, str);
    } while (str != "yes" && str != "no");
    
    if(str == "yes") return true;
    if(str == "no") return false;

    return false;
}

void printHeader(){
    cout << "\nReverse Sentence\n";
    cout << "================\n\n";
}

string askSentence(){
    cout << "Input sentence[minimum 5 words]:";

    string str = "";
    getline(cin, str);

    return str;
}

int countWords(string str)
{
    int chartype = -1;
    int words = 0;
    const int LETTER = 1;
    const int SPACE = 2;
    for (char i : str)
    {
        if(chartype == -1 && i != ' '){
            chartype = LETTER;
        }
        if(i == ' ' && chartype == LETTER){
            chartype = SPACE;
            words++; // mark word
        }
        if(i != ' ' && chartype == SPACE){
            chartype = LETTER;
        }
    }
    if(chartype == LETTER)
    {
        words++; // mark word
    }
    return words;
}