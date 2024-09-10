
void drawWindow(){

    for(int i = wX1; i<=winBorderX; i++){
        for(int j=wY1; j<=winBorderY; j++){
            if(i==wX1 || i==wX3){
                gotoxy(i,j);
                printf("*");
            } else if (j==wY1 || j==wY3){
                gotoxy(i,j);
                printf("*");
            }

        }
    }
}

void drawSnake(){

    for(int i=0;i<s.length;i++){
        gotoxy(s.body[i].x,s.body[i].y);
        printf("*");
    }

}

void drawHeadTail(){

    gotoxy(s.tail.x,s.tail.y);
    printf(" ");
    gotoxy(s.head.x,s.head.y);
    printf("*");

}

void drawFood(int x, int y){
    gotoxy(x,y);
    printf("0");

}
