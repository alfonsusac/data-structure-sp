//
// Created by Hanry Ham on 2020-05-24.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Employee{
    char name[20];
    char jobPos[15];
    int grade;
    int age;
    Employee *next;
}*head = NULL, *tail = NULL;

bool isValid(char *name, char *jobPos, int grade, int age){
    // [15%] (1) INSERT YOUR CODE HERE
    Employee *rover = head;
    while (rover != NULL)
    {
        if (strcmp(name,rover->name) == 0
        && strcmp(jobPos, rover->jobPos) == 0
        && grade == rover->grade
        && age == rover->age)
        {
            return true;
        }
        rover = rover->next;
    }
    return false;
}

void push(char *name, char *jobPos, int grade, int age){
    struct Employee *curr = (struct Employee *) malloc(sizeof(Employee));
    // [10%] (2) INSERT YOUR CODE HERE
    if( !isValid(name, jobPos, grade, age) ){
        
        strcpy(curr->name, name);
        strcpy(curr->jobPos, jobPos);
        curr->age = age;
        curr->grade = grade;

        curr->next = head;
        if (tail == NULL)
        {
            tail = curr;
        }
        head = curr;

    }else{
        printf("\n\nThe inputted data is duplicated!\n\n");
    }
}

void pop(){
    struct Employee * curr = head;
    // [15%] (3) INSERT YOUR CODE HERE
    if (head == tail && head != NULL)
    {
        head = NULL;
        tail = NULL;
        free(curr);
    }else if (head != NULL)
        while (curr->next != NULL){
            if (curr->next->next == NULL)
            {
                free(curr->next);
                curr->next = NULL;
                tail = curr;
            }
            if (curr->next == NULL)
                break;
            curr = curr->next;
        }
    else
        printf("The List is Empty!\n\n");
}

void printAll(){
    printf("\n\n");
    struct Employee * curr = head;
    int empCtr = 0;
    if(!curr){
        printf("the list is empty!");
    }else{
        // [10%] (4) INSERT YOUR CODE HERE
        printf("=======================================================\n");
        printf("|               Name|       Job Position| Grade|   Age|\n");
        printf("=======================================================\n");
        while (curr!=NULL)
        {
            empCtr++;
            printf("|%19s|%19s|%6d|%6d|\n", curr->name, curr->jobPos, curr->grade, curr->age);
            curr = curr->next;
        }
        printf("=======================================================\n");
        printf("Total Employee : %d\n", empCtr);
        printf("=======================================================\n");
    }
}

int main(){
    pop();
    printAll();
    push("Hanry", "Supervisor", 12, 27);
    push("Yen", "Manager", 13, 40);
    pop();
    push("Derwin", "Manager", 15, 31);
    push("Andry", "Manager", 15, 30);
    pop();
    push("Saka", "Manager", 15, 32);
    pop();
    push("Afan", "Manager", 16, 35);
    push("Fredy", "Senior Manager", 18, 45);
    pop();
    printAll();
    return 0;
}
