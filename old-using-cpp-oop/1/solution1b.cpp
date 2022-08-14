#include <string>
#include <iostream>
using namespace std;

struct Student
{
    string nim;
    string name;
    int umur;
};

#define MAXLIST 50
Student stdlist[MAXLIST];
int stdlistcount = 0;

void newStudent(string nim, string name, int umur){
    stdlist[stdlistcount].name = name;
    stdlist[stdlistcount].nim = nim;
    stdlist[stdlistcount].umur = umur;
    stdlistcount++;
}

int main()
{
    newStudent("2301900555", "Alfonsus Ardani", 21);
    newStudent("2301900556", "A Ardani", 22);
    newStudent("2301900216", "Alfonsus A", 23);
    for (int i = 0; i < stdlistcount; i++)
    {
        cout << stdlist[i].nim << " " << stdlist[i].name << " " << stdlist[i].umur << "\n";
    }
    return 0;
}