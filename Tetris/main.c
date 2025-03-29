#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#include "gotoxy.h"
#include "Tetris.h"
#include "shapes.h"

#define TOP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ESC 27

#define LOW 200
#define MEDIUM 150
#define HIGH 125




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


//Index for current tetrimino
int rand_c;

//Index for next tetrimino
int rand_n;

//Total number of tetrimino
int total_t = 7;

//i and j index of tetrisBoard
int curr_inx_i_y;
int curr_inx_j_x;

//Flag to identify key press, 0 = No, 1= Yes
int keyHitFlag = 0;

//Flag to identify rotation angle, 0=clockwise, 1=anticlockwise
int rotate = -1;


void startGamePlay();
int gameStart();

int test_x = 10;
int test_y = 12;

int main()
{

    startGamePlay();

    return 0;
}

void startGamePlay(){
    system("cls");
    //int x_coord = x;
    //int y_coord = y;
    int status = 0;
    char ch;

    //Generate random number for current and next tetrimino block
    srand(time(0));
    rand_c = rand() % 7;
    rand_n = rand() % 7;

    //Hide mouse cursor
    hidecursor();

    initShapes();
    drawWindow();
    resetTranslateVec();
    score = 0;

    setCurrentNextTetrimino(rand_c,rand_n);
    status = gameStart();
    if(status > 1){
        gotoxy(11,8);
        printf("Game Over! Press any key to Continue");
        gotoxy(11,7);
        printf("Or Press ESC to Exit");
    }

    ch = getch();

    if(ch!=ESC)
        startGamePlay();

}

int gameStart(){

    int gameStatus = 0;
    int keyInput = -1;
    int endOfMove = 0;

    drawNextTetrimino(next_T);

    while(!kbhit()){

        gotoxy(12, 10);
        printf("Row: %d Score: %d",score,score*10);

        if(keyHitFlag==0){
            unitVecDir = 1;
        }

        //Update translation vector as per Tetrimino direction
        updTranslateVec();

        //rotateTetrimino(rand_c,r_clk);
        endOfMove = translateTetrimino(rand_c,rotate);
        drawTetrimino(current_T);


        keyHitFlag=0;
        rotate = -1;

        if(endOfMove==0){

            if(score < 10)
                delay(LOW);
            else if (score >= 10 && score < 25 )
                delay(MEDIUM);
            else
                delay(HIGH);

            removeTetrimino(current_T);
        } else if(endOfMove==1){
            revertTranslateVec();
            removeTetrimino(current_T);
        } else if(endOfMove==2 || endOfMove==3){
            setTetrisBoard();
            removeNextTetrimino(next_T);
            rand_c = rand_n;
            rand_n = rand() % 7;
            getNextTetrimino(rand_n);
            resetTranslateVec();
            drawNextTetrimino(next_T);
            checkRowAndRedrawBoard();
        }else if(endOfMove==4){
            removeNextTetrimino(next_T);
            return endOfMove;
        }
    }

    keyInput = getch();

    if(keyInput==TOP){
        //Rotate Clock wise
        //rotateTetrimino(rand_c,currRotationVec[0]);
        rotate=0;

    } else if(keyInput==DOWN){
        //Rotate anti-clock wise
        //rotateTetrimino(rand_c,currRotationVec[1]);
        rotate=1;

    } else if(keyInput==LEFT){
        //Translate toward negative x-axis
        unitVecDir = 3;
        keyHitFlag=1;

    } else if(keyInput==RIGHT){
        //Translate toward positive x-axis
        unitVecDir = 2;
        keyHitFlag=1;

    } else if(keyInput==ESC){
        exit(0);
    }

    gameStart();

    return gameStatus;
}


