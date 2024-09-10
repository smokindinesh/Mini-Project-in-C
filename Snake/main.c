#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>
#include "gotoxy.h"
#include "snake.h"
#include "drawFrame.h"

#define TOP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27

void delay(unsigned int msec){
    //clock_t goal = msec + clock();
    //while (goal > clock());
    usleep(msec*1000);
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

unsigned int r;
unsigned int dirIndex;

void gameMain();
void gameInit();
int gameStart();

int score;

int main()
{
    srand(time(NULL));
    hidecursor();

    gameMain();

    return 0;
}

void gameMain(){

    system("cls");

    int gameStatus;
    char ch;

    r = rand() % sSize;

    dirIndex=RT;

    gameInit();
    drawFood(food[r].x,food[r].y);

    gameStatus = gameStart(r);

    if(gameStatus == 1){
        gotoxy(55,6);
        printf("Game Over!! Please press any key to re-start.");
        gotoxy(55,7);
        printf("or press ESC to exit!");
    } else if (gameStatus == 2){
        gotoxy(55,9);
        printf("Congratulation! You have reached maximum length.");
        gotoxy(55,10);
        printf("Please press any key to re-start or press ESC to exit!");
    }

    ch = getch();

    if(ch!=ESC)
        gameMain();
}

void gameInit(){

    initDir();
    initFood();
    initSnake();
    drawWindow();
    drawSnake();
}

int gameStart(int r){

    int input;
    int exitFlag=0;

    do{
        delay(150);
        //sleep(1);

        if(buildSnake(food[r],dir[dirIndex])==1){
            r = rand() % sSize;
            drawFood(food[r].x,food[r].y);
        }
        gotoxy(55,4);
        score = s.length * 10 - startLen * 10;
        printf("Snake Length: %d Score: %d ",s.length,score);
        exitFlag = checkCollision();
        if(exitFlag==1){
            break;
        }
        drawHeadTail();
    } while(!kbhit());


    input = getch();

    if(input==TOP){
        dirIndex = UP;
    } else if(input==DOWN){
        dirIndex = DW;
    } else if(input==LEFT){
        dirIndex = LT;
    } else if(input==RIGHT){
        dirIndex = RT;
    } else if(input==ESC){
        exit(0);
    }

    if(exitFlag==0){
        gameStart(r);
    }

    return exitFlag;

}
