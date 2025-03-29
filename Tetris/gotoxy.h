    //  header file for gotoxy
COORD coord= {0,0}; // this is global variable
int center_x = 36;
int center_y = 12;
void gotoxy(int x,int y)
{
    coord.X= x + center_x;
    coord.Y= (y * -1) + center_y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
