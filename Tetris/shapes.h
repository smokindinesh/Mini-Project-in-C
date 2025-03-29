void drawTetriminoWithShift(struct Tetriminos block, int xx, int yy){

    for(int i=0;i<4;i++){
        int x = block.body[i].y * 1 + xx;
        int y = block.body[i].x * -1 + yy;
        gotoxy(x,y);
        printf("#");
    }
}

void drawAllTetrimino(){
    //(0,8)
    //(-3,7)
    //Draw I
    drawTetriminoWithShift(tetrimino[I_BLOCK],-3,7);
    gotoxy(-30,7);
    printf("I");
    /*
    //Draw I
    drawTetriminoWithShift(tetrimino[J_BLOCK],-20,10);
    gotoxy(-20,7);
    printf("J");
    //Draw I
    drawTetriminoWithShift(tetrimino[L_BLOCK],-10,10);
    gotoxy(-10,7);
    printf("L");
    //Draw I
    drawTetriminoWithShift(tetrimino[T_BLOCK],0,10);
    gotoxy(0,7);
    printf("T");
    //Draw I
    drawTetriminoWithShift(tetrimino[Z_BLOCK],-25,3);
    gotoxy(-25,1);
    printf("Z");
    //Draw I
    drawTetriminoWithShift(tetrimino[O_BLOCK],-15,3);
    gotoxy(-15,1);
    printf("O");
    //Draw I
    drawTetriminoWithShift(tetrimino[S_BLOCK],-5,3);
    gotoxy(-5,1);
    printf("S");
    */
}
