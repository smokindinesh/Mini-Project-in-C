// Standard library files
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Custom header files
#include "gotoxy.h"
#include "utility.h"
#include "loadCsvData.h"
#include "access_operation.h"
#include "issueReturn_operation.h"


// Define Constant Variables
#define ESC 27 //ASCII value for key

//Function declaration
void mainMenu(); //Function to display the main menu
void admin_access(); //Function to handle admin access
void student_access(); //Function to handle student access
int checkFirstLogin(); //Function to check if it's the first login
void createAccount(); //Function to create a new account
void adminLogin(); //Function to handle admin login

#include "userMenu.h"

int main()
{

    mainMenu();

    return 0;
}

//Function definition
void mainMenu(){

    char choice;

    system("cls");

    gotoxy(35,6);
    printf("----Welcome to Library Management System----");
    gotoxy(35,8);
    printf("Please select the any option a, s or ESC");
    gotoxy(35,10);
    printf("A) Log in as Admin");
    gotoxy(35,12);
    printf("S) Log in as Student");
    gotoxy(35,16);
    printf("Please enter ESC to exit application");

    choice=tolower(getch());

    switch(choice){
        case 'a':
            admin_access();
            break;
        case 's':
            student_access();
            break;
        case ESC:
            exit(0);
        default:
            gotoxy(35,30);
            printf("Please enter options a, s or ESC");
            if(getch())
                mainMenu();
    }
}

void admin_access(){

    if(checkFirstLogin()==1){
        createAccount();
    } else {
        adminLogin();
    }
}

void student_access(){

    char stuId[MAX_ID];

    printWelcomeMsg();

    gotoxy(35,8);
    printf("Please Enter you Student ID: ");
    getString(stuId,MAX_ID);

    if(findStudentID(stuId)==1){
        studentMenu();
    } else {
        gotoxy(35,10);
        printf("Student ID does not exits. Please re-enter..");
        gotoxy(35,12);
        printf("Press any key to continue..");
        if(getch())
            student_access();
    }

}

int checkFirstLogin(){
    int flag=1;

    fa = fopen(DATA_FILE,"rb");

    if(fa!= NULL){
        flag= 0;
    }
    fclose(fa);

    return flag;

}

void createAccount(){

    char passV[MAX_PWD_SZ];
    struct password pd;

    printWelcomeMsg();

    gotoxy(35,8);
    printf("Please Enter New Username and Password.");
    gotoxy(35,10);
    printf("New User Name: ");
    getString(pd.userName,MAX_USR_SZ);
    gotoxy(35,11);
    printf("New Password: ");
    getPassword(pd.password,MAX_PWD_SZ);
    gotoxy(35,12);
    printf("Re-type Password: ");
    getPassword(passV,MAX_PWD_SZ);


    if(strcmp(passV,pd.password)==0){

        add(pd);

        printWelcomeMsg();

        gotoxy(35,8);
        printf("Congratulation! User account created.");
        gotoxy(35,10);
        printf("Please press any key to continue and log in.");
        if(getch()){
            adminLogin();
        }

    }
}

void adminLogin(){

    struct password pd;

    printWelcomeMsg();

    gotoxy(35,8);
    printf("Please Enter Username and Password.");
    gotoxy(35,10);
    printf("User Name: ");
    getString(pd.userName,MAX_USR_SZ);
    gotoxy(35,11);
    printf("Password: ");
    getPassword(pd.password,MAX_PWD_SZ);

    if(check(pd,0)==1){

        printWelcomeMsg();

        gotoxy(35,10);
        printf("Login Successfull.");
        gotoxy(35,13);
        printf("Please press any key to continue.");
        if(getch()){
            adminMenu();
        }
    } else {

        printWelcomeMsg();

        gotoxy(35,10);
        printf("Sorry! Username or Password do not match.");
        gotoxy(35,13);
        printf("Please press any key to re-login.");
        if(getch()){
            adminLogin();
        }
    }
}
