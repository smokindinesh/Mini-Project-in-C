
// Define C standard headers
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<time.h>

// Define Constant Variables
#define ESC 27
#define REF_SZ 10
#define DATE_SZ 64
#define MIN_TEXT_SZ 50
#define MAX_TEST_SZ 500
#define READ_ARRAY_SZ 15
#define DATA_FILE "dataFile.dat"
#define TEMP_FILE "tempFile.dat"

//Define data structure

struct data{
    char refNum[REF_SZ];
    char noteDate[DATE_SZ];
    char eventDate[DATE_SZ];
    char location[MIN_TEXT_SZ];
    char eventDesc[MIN_TEXT_SZ];
    char notes[MAX_TEST_SZ];
};

//Declare custom headers

#include "gotoxy.h"
#include "file_operation.h"

// Declare functions
struct data readData(int flag, char defChar[]);
void mainMenu();
void viewItems();
void addItems();
void updateItems();
void deleteItems();

int nextRefNum=0;
char defChar[2] = {'N','A'};

// C main function
int main(){

    nextRefNum = getNextRef();

    mainMenu();

    return 0;
}

//Start function definitions

//Display user menu
void mainMenu(){


    char choice;

    system("cls");

    gotoxy(35,6);
    printf("----Welcome to Personal Diary Management System----");
    gotoxy(35,8);
    printf("Please select the any option v, a, u, d, e or ESC");
    gotoxy(35,10);
    printf("V) View All Records");
    gotoxy(35,12);
    printf("A) Add Records");
    gotoxy(35,14);
    printf("U) Update Records");
    gotoxy(35,16);
    printf("D) Delete Records");
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
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("----Welcome to Personal Diary Management System----");

    printf("\nThe number of notes are %d\n\n",data_sz);

    for (int i=0;i<data_sz;i++){
        printf("\n|     Reference No: %s",c[i].refNum);
        printf("\n| Added/Updated On: %s",c[i].noteDate);
        printf("\n|       Event Date: %s",c[i].eventDate);
        printf("\n|   Event Location: %s",c[i].location);
        printf("\n|Event Description: %s",c[i].eventDesc);
        printf("\n|            Notes: %s\n\n",c[i].notes);
    }


    printf("\n\n\nPlease enter ESC key to go back.");
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
    printf("----Welcome to Personal Diary Management System----");
    gotoxy(35,8);
    printf("Please enter details:");

    c = readData(0,defChar);
    if(searchByNum(c.refNum)==2){
        gotoxy(35,16);
        printf("Reference number is empty. Record can't be saved.");
    } else if(searchByNum(c.refNum)==1){
        gotoxy(35,16);
        printf("Reference number %s exist. Please go back to update.",c.refNum);
    } else {
        add(c);
        gotoxy(35,25);
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

    char pNum[REF_SZ];
    struct data c;
    system("cls");
    gotoxy(35,6);
    printf("----Welcome to Personal Diary Management System----");
    gotoxy(35,7);
    printf("Please enter the Reference Number that you want to update details");
    gotoxy(35,9);
    printf("Enter Reference Number:");
    getString(pNum,sizeof(pNum));

    if(searchByNum(pNum)==1){
        gotoxy(35,10);
        printf("Reference Number %s exist. Please enter new details.",pNum);
        c=readData(1,pNum);
        update(c,pNum);
    } else {
        gotoxy(35,11);
        printf("Reference Number %s do not exist.",pNum);
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

    char pNum[REF_SZ];
    char choice;
    system("cls");
    gotoxy(35,6);
    printf("----Welcome to Personal Diary Management System----");
    gotoxy(35,7);
    printf("Please enter the Reference Number that you want to delete");
    gotoxy(35,9);
    printf("Enter Reference Number:");
    getString(pNum,sizeof(pNum));

    if(searchByNum(pNum)==1){
        gotoxy(35,12);
        printf("Reference Number %s exist. Do you want to delete it?.",pNum);
        gotoxy(35,14);
        printf("Please press y to delete or any key to skip.");
        choice=tolower(getch());
        if(choice=='y'){
            del(pNum);
            gotoxy(35,16);
            printf("Reference Number successfully deleted.");
        }

    } else {
        gotoxy(35,12);
        printf("Reference Number %s do not exist.",pNum);
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
struct data readData(int flag,char ref[] ){

    struct data c;

    if(flag==0){
        nextRefNum++;
        calRefNum(c.refNum,nextRefNum);

    } else {
        strcpy(c.refNum,ref);
    }



    time_t t;
    time(&t);

    strcpy(c.noteDate,ctime(&t));
    //remove newline character from the end
    c.noteDate[strlen(c.noteDate)-1]='\0';

    gotoxy(35,11);
    printf("Unique Reference ID: %s",c.refNum);
    //getString(c.fName,sizeof(c.fName));

    gotoxy(35,12);
    printf("Added/Updated On: %s",c.noteDate);
    //getString(c.lName,sizeof(c.lName));

    gotoxy(35,13);
    printf("Enter Event Date: ");
    getString(c.eventDate,sizeof(c.eventDate));

    gotoxy(35,14);
    printf("Enter Event Location: ");
    getString(c.location,sizeof(c.location));

    gotoxy(35,15);
    printf("Enter Event Short Description: ");
    getString(c.eventDesc,sizeof(c.eventDesc));

    gotoxy(35,16);
    printf("Enter Detail Event Notes (Max 500): ");
    getString(c.notes,sizeof(c.notes));

    return c;
};
