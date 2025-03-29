#include<stdio.h>
#include<conio.h>
#include<time.h>
#include <unistd.h>
#include<stdlib.h>
#include <windows.h>

#define ESC 27 //For ESC keyboard key
#define firstPlayer 0 //Flag for first player
#define secondPlayer 1 //Flag for second player
int human,computer; //Variable to identify human or computer

#include "gotoxy.h"
#include "ticTacToe.h"
#include "drawBoard.h"
#include "players.h"


void initGame(int choice);
void gameMenu();
void startGame();
int getPlayerInput();
int getHumanInput();
int getComputerInput();

//Function to hide mouse cursor
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
//function to delay
void delay(unsigned int msec){
    //clock_t goal = msec + clock();
    //while (goal > clock());
    usleep(msec*1000);
}

int main(){
    hidecursor();
    gameMenu();
    return 0;
}

void initGame(int choice){

    initBoard();
    if(choice == 1){
        human = firstPlayer;
        computer = secondPlayer;
    } else if(choice == 2){
        human = secondPlayer;
        computer = firstPlayer;
    }
    initPlayer(firstPlayer,secondPlayer);
    //getch();
}

void gameMenu()
{
    int choice;
    system("cls");
    printf("\n--------MENU--------");
    printf("\n1 : Play first with X");
    printf("\n2 : Play second with O");
    printf("\n3 : Exit");
    printf("\nEnter your choice:>");
    scanf("%d",&choice);

    switch (choice)
    {
    case 1:
    case 2:
        initGame(choice);
        drawBoard();
        startGame();
        break;
    case 3:
        exit(1);
    default:
        gameMenu();
    }
}

void startGame(){

    int playerInput;
    int gameStaus=0;

    do{
        playerInput = getPlayerInput();
        drawTicTac(p.currentPlayer,playerInput);
        setBox(playerInput,p.currentPlayer);

        if(checkWinner()==1){
            gameStaus=1;
        } else {
            setNextPlayer(playerInput,p.currentPlayer);
        }

        if(p.numOfTurn>=9)
            gameStaus=2;

    }while(gameStaus==0);

    if(gameStaus==2)
        displayMessage(p.currentPlayer,2);
    else
        displayMessage(p.currentPlayer,1);

    if(getch()!=ESC)
        gameMenu();
}

int getPlayerInput(){

    if(p.currentPlayer == human)
        return getHumanInput();
    else if(p.currentPlayer == computer)
        return getComputerInput();

    return -1;
}

int getHumanInput(){

    char choice;
    int boxNum;

    displayMessage(p.currentPlayer,0);

    choice = getch();
    boxNum = choice - 49;
    while (boxNum<0 || boxNum >8 || isBoxEmpty(boxNum)!=0){
        displayMessage(p.currentPlayer,3);
        choice = getch();
        boxNum = choice - 49;
    }
    return boxNum;
}

int getComputerInput(){

    int boxNum;

    displayMessage(p.currentPlayer,0);

    delay(1000);

    boxNum = getNextMove();

    return boxNum;
}

