void drawBoard(){
    system("cls");
    int x_coord;
    int y_coord;

    for(int i=0; i<=numDiv; i++){
        for(int j=0;j<=boardSize_X;j++){
            x_coord =boardStart_X + j;
            y_coord =boardStart_Y + initBoxSize_Y * i;
            gotoxy(x_coord,y_coord);
            printf("*");
        }

        for(int j=0;j<=boardSize_Y;j++){
            x_coord =boardStart_X + initBoxSize_X * i;
            y_coord =boardStart_Y + j;
            gotoxy(x_coord,y_coord);
            printf("*");
        }
    }

    gotoxy(msgStart_X,msgStart_Y);
    printf("Please enter the value 1,2..9,");
    gotoxy(msgStart_X,msgStart_Y + 1);
    printf("as a box number starting from");
    gotoxy(msgStart_X,msgStart_Y + 2);
    printf("top left to right bottom corner");

}

void displayMessage(int player, int msgType){

    if(msgType==0){
        gotoxy(msgStart_X,msgStart_Y + 5);
        if(player==human)
            printf("Hey! Human, its your turn!       ");
        else
            printf("Hey! Computer, its your turn!    ");

    } else if(msgType==1){
        gotoxy(msgStart_X,msgStart_Y + 5);
        if(player==human)
            printf("Congratulation! You have won the game.");
        else
            printf("Ops! Computer has won the game.       ");
    } else if(msgType==2){
        gotoxy(msgStart_X,msgStart_Y + 5);
        printf("The game is Draw!                      ");
    }

    if(msgType==3){
        gotoxy(msgStart_X,msgStart_Y + 7);
        printf("Wrong Number! Or Not empty box!");
        gotoxy(msgStart_X,msgStart_Y + 9);
        printf("Please Enter next value!");
    } else if (msgType==1 || msgType==2) {
        gotoxy(msgStart_X,msgStart_Y + 7);
        printf("Press any key to Continue or ESC to exit.");
        gotoxy(msgStart_X,msgStart_Y + 9);
        printf("                                 ");
    } else {
        if(msgType==0 && player==computer){
            gotoxy(msgStart_X,msgStart_Y + 7);
            printf("...Computer is thinking...      ");
        } else {
            gotoxy(msgStart_X,msgStart_Y + 7);
            printf("                                 ");
        }
        gotoxy(msgStart_X,msgStart_Y + 9);
        printf("                                 ");
    }
}

void draw_X(int i){
    gotoxy(box[i].center.x + boardStart_X,box[i].center.y + boardStart_Y);
    printf("X");
}

void draw_O(int i){
    gotoxy(box[i].center.x + boardStart_X,box[i].center.y + boardStart_Y);
    printf("O");
}

void drawTicTac(int player, int pos){
    if(player == firstPlayer)
        draw_X(pos);
    else if (player == secondPlayer)
        draw_O(pos);
}
