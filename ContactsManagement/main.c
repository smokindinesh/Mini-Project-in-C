// Define C standard headers
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>

// Define Constant Variables
#define ESC 27
#define MAX_NAME_SZ 10
#define MAX_NUM_SZ 20
#define READ_ARRAY_SZ 15
#define DATA_FILE "dataFile.dat"
#define TEMP_FILE "tempFile.dat"

//Define data structure

struct data{
    char fName[MAX_NAME_SZ];
    char lName[MAX_NAME_SZ];
    char mPhone[MAX_NUM_SZ];
    char wPhone[MAX_NUM_SZ];
    char hPhone[MAX_NUM_SZ];
};

//Declare custom headers

#include "gotoxy.h"
#include "file_operation.h"

// Declare functions
struct data readData();
void mainMenu();
void viewItems();
void addItems();
void updateItems();
void deleteItems();

// C main function
int main(){
    mainMenu();
    return 0;
}

//Start function definitions

//Display user menu
void mainMenu(){


    char choice;

    system("cls");

    gotoxy(35,6);
    printf("----Welcome to Contact Management System----");
    gotoxy(35,8);
    printf("Please select the any option v, a, u, d, e or ESC");
    gotoxy(35,10);
    printf("V) View All Contact");
    gotoxy(35,12);
    printf("A) Add Contact");
    gotoxy(35,14);
    printf("U) Update Contact");
    gotoxy(35,16);
    printf("D) Delete Contact");
    gotoxy(35,18);
    printf("E) Exit application");
    gotoxy(35,20);
    printf("Please enter ESC to exit application");

    choice=tolower(getch());

    switch(choice){
        case 'v':
            viewItems();
            break;
        case 'a':
            addItems();
            break;
        case 'u':
            updateItems();
            break;
        case 'd':
            deleteItems();
            break;
        case 'e':
            exit(0);
        case ESC:
            exit(0);
        default:
            gotoxy(35,30);
            printf("Please enter options V, A, U, D, E or ESC");
            if(getch())
                mainMenu();
    }
}

//Display contacts only 15 items
void viewItems(){

    struct data c[READ_ARRAY_SZ];
    int data_sz=0;
    data_sz = view(c,READ_ARRAY_SZ);

    system("cls");
    gotoxy(35,6);
    printf("----Welcome to Contact Management System----");
    gotoxy(35,8);
    printf("View Contact function selected %d",data_sz);


    gotoxy(15,10);
    printf("First Name");
    gotoxy(35,10);
    printf("Last Name");
    gotoxy(55,10);
    printf("Mobile Number");
    gotoxy(70,10);
    printf("Work Number");
    gotoxy(85,10);
    printf("Home Number");
    for (int i=0;i<data_sz;i++){
        gotoxy(15,11 + i);
        printf("%s",c[i].fName);
        gotoxy(35,11 + i);
        printf("%s",c[i].lName);
        gotoxy(55,11 + i);
        printf("%s",c[i].mPhone);
        gotoxy(70,11 + i);
        printf("%s",c[i].wPhone);
        gotoxy(85,11 + i);
        printf("%s",c[i].hPhone);
    }

    gotoxy(35,27);
    printf("Please enter ESC key to go back.");
    if(getch()==ESC){
        mainMenu();
    } else {
        viewItems();
    }

}

//Add contacts
void addItems(){

    struct data c;

    system("cls");
    gotoxy(35,6);
    printf("----Welcome to Contact Management System----");
    gotoxy(35,8);
    printf("Please enter details:");

    c = readData();
    if(searchByNum(c.mPhone)==2){
        gotoxy(35,16);
        printf("Mobile number is empty. Record can't be saved.");
    } else if(searchByNum(c.mPhone)==1){
        gotoxy(35,16);
        printf("Mobile number %s exist. Please go back to update.",c.mPhone);
    } else {
        add(c);
        gotoxy(35,17);
        printf("Record Successfully Saved.");
    }
    gotoxy(35,27);
    printf("Please press any key to continue or enter ESC key to go back.");
    if(getch()==ESC){
        mainMenu();
    } else {
        addItems();
    }
}

//Update contact details
void updateItems(){

    char pNum[MAX_NUM_SZ];
    struct data c;
    system("cls");
    gotoxy(35,6);
    printf("----Welcome to Contact Management System----");
    gotoxy(35,7);
    printf("Please enter the Mobile Phone that you want to update details");
    gotoxy(35,9);
    printf("Enter Mobile Phone:");
    getString(pNum,sizeof(pNum));

    if(searchByNum(pNum)==1){
        gotoxy(35,10);
        printf("Mobile number %s exist. Please enter new details.",pNum);
        c=readData();
        update(c,pNum);
    } else {
        gotoxy(35,11);
        printf("Mobile number %s do not exist.",pNum);
    }
    gotoxy(35,27);
    printf("Please enter any key to continue or enter ESC key to go back.");
    if(getch()==ESC){
        mainMenu();
    } else {
        updateItems();
    }
}

//Delete contacts details
void deleteItems(){

    char pNum[MAX_NUM_SZ];
    char choice;
    system("cls");
    gotoxy(35,6);
    printf("----Welcome to Contact Management System----");
    gotoxy(35,7);
    printf("Please enter the Mobile Phone that you want to delete");
    gotoxy(35,9);
    printf("Enter Mobile Phone:");
    getString(pNum,sizeof(pNum));

    if(searchByNum(pNum)==1){
        gotoxy(35,12);
        printf("Mobile number %s exist. Do you want to delete it?.",pNum);
        gotoxy(35,14);
        printf("Please press y to delete or any key to skip.");
        choice=tolower(getch());
        if(choice=='y'){
            del(pNum);
            gotoxy(35,16);
            printf("Phone number successfully deleted.");
        }

    } else {
        gotoxy(35,12);
        printf("Mobile number %s do not exist.",pNum);
    }

    gotoxy(35,27);
    printf("Please enter any key to continue or enter ESC key to go back.");

    if(getch()==ESC){
        mainMenu();
    } else {
        deleteItems();
    }
}

//Function to read contact data
struct data readData(){
    struct data c;

    gotoxy(35,11);
    printf("Enter first name: ");
    getString(c.fName,sizeof(c.fName));

    gotoxy(35,12);
    printf("Enter last name: ");
    getString(c.lName,sizeof(c.lName));

    gotoxy(35,13);
    printf("Enter mobile phone: ");
    getString(c.mPhone,sizeof(c.mPhone));

    gotoxy(35,14);
    printf("Enter work phone: ");
    getString(c.wPhone,sizeof(c.wPhone));

    gotoxy(35,15);
    printf("Enter home phone: ");
    getString(c.hPhone,sizeof(c.hPhone));

    return c;
};



