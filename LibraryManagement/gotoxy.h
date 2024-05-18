
#include<windows.h>

COORD coord= {0,0}; // this is global variable
//Function declaration
void gotoxy(int x,int y);

//function declaration
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
