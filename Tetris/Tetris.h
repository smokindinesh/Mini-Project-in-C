#define I_BLOCK 0
#define J_BLOCK 1
#define L_BLOCK 2
#define O_BLOCK 3
#define S_BLOCK 4
#define T_BLOCK 5
#define Z_BLOCK 6

#define NUM_BOX 4
#define win_half_x 6
#define win_half_y 11

#define board_half_x 5
#define board_half_y 10
#define neg_board_half_x -5
#define neg_board_half_y -10
#define board_index_i_y 21
#define board_index_j_x 11

//Structure definition of x,y coordinate
struct Point2D {
    int x;
    int y;
};

//Structure definition to define each game board boxes
struct Tetriminos {
    struct Point2D body[4];
};

//Structure definition of individual Tetris box
//Added on the Tetris board.
struct TetrisBox {
    struct Point2D box;
    int flag_T;
};

//Store four corner of the Tetris board
struct Point2D window[4];
//Store 7 shapes (Tetrimino)
struct Tetriminos tetrimino[7];

//Current Tetris shapes
struct Tetriminos current_T;

//Next Tetris shapes
struct Tetriminos next_T;

//Declare all box 11 * 21 = 231 within Tetris board
//double array matrix is created to represent board vertical boxes and horizontal boxes.
//The flag is to identify occupied box.
struct TetrisBox tetrisBoard[board_index_i_y][board_index_j_x];

//Current Translate vector
struct Point2D currTranslateVec = {0,11};

//Unit vector toward  x-axis and y-axis both positive and negative
//0= + y-axis, 1 = - y-axis, 2 = + x-axis, and 3 = - x-axis
struct Point2D unitVec[4] = {{0,1},{0,-1},{1,0},{-1,0}};

//Clockwise rotation vector, 0 = clockwise, 1 = anti-clock wise
struct Point2D currRotationVec[2] = {{1,-1},{-1,1}};

//Index to indicate direction of unit vector
int unitVecDir = 1;

//Variable to calculate score
int score=0;

void initShapes(){

    //Initialize window
    window[0] = (struct Point2D){-win_half_x,-win_half_y};
    window[1] = (struct Point2D){win_half_x,win_half_y};
    window[2] = (struct Point2D){win_half_x,-win_half_y};
    window[3] = (struct Point2D){-win_half_x,win_half_y};

    //initialize I Block
    tetrimino[I_BLOCK].body[3] = (struct Point2D){0,2};
    tetrimino[I_BLOCK].body[2] = (struct Point2D){0,1};
    tetrimino[I_BLOCK].body[1] = (struct Point2D){0,0};
    tetrimino[I_BLOCK].body[0] = (struct Point2D){0,-1};

    //initialize J Block
    tetrimino[J_BLOCK].body[3] = (struct Point2D){0,1};
    tetrimino[J_BLOCK].body[2] = (struct Point2D){0,0};
    tetrimino[J_BLOCK].body[1] = (struct Point2D){-1,-1};
    tetrimino[J_BLOCK].body[0] = (struct Point2D){0,-1};

    //initialize L Block
    tetrimino[L_BLOCK].body[3] = (struct Point2D){0,1};
    tetrimino[L_BLOCK].body[2] = (struct Point2D){0,0};
    tetrimino[L_BLOCK].body[1] = (struct Point2D){1,-1};
    tetrimino[L_BLOCK].body[0] = (struct Point2D){0,-1};

    //initialize O Block
    tetrimino[O_BLOCK].body[3] = (struct Point2D){0,1};
    tetrimino[O_BLOCK].body[2] = (struct Point2D){1,1};
    tetrimino[O_BLOCK].body[1] = (struct Point2D){1,0};
    tetrimino[O_BLOCK].body[0] = (struct Point2D){0,0};

    //initialize S Block
    tetrimino[S_BLOCK].body[3] = (struct Point2D){1,1};
    tetrimino[S_BLOCK].body[2] = (struct Point2D){0,1};
    tetrimino[S_BLOCK].body[1] = (struct Point2D){-1,0};
    tetrimino[S_BLOCK].body[0] = (struct Point2D){0,0};

    //initialize T Block
    tetrimino[T_BLOCK].body[3] = (struct Point2D){-1,0};
    tetrimino[T_BLOCK].body[2] = (struct Point2D){1,0};
    tetrimino[T_BLOCK].body[1] = (struct Point2D){0,0};
    tetrimino[T_BLOCK].body[0] = (struct Point2D){0,-1};

    //initialize Z Block
    tetrimino[Z_BLOCK].body[3] = (struct Point2D){-1,1};
    tetrimino[Z_BLOCK].body[2] = (struct Point2D){0,1};
    tetrimino[Z_BLOCK].body[1] = (struct Point2D){1,0};
    tetrimino[Z_BLOCK].body[0] = (struct Point2D){0,0};

    //initialize Tetris board

    int start_y = board_half_y;
    int start_x = board_half_x * -1;
    int x,y;
    for(int i=0; i<board_index_i_y; i++){
        y = start_y - i;
        x = start_x;
        for(int j=0; j<board_index_j_x; j++){
            x = start_x + j;

            tetrisBoard[i][j].box = (struct Point2D){x,y};
            tetrisBoard[i][j].flag_T = 0;

        }
    }

}

//Update translate vector
void updTranslateVec(){

    currTranslateVec.x = currTranslateVec.x + unitVec[unitVecDir].x;
    currTranslateVec.y = currTranslateVec.y + unitVec[unitVecDir].y;
}
//Revert translate vector
void revertTranslateVec(){
    if(unitVecDir==1){
        currTranslateVec.x = currTranslateVec.x + unitVec[0].x;
        currTranslateVec.y = currTranslateVec.y + unitVec[0].y;
    } else if(unitVecDir==3){
        currTranslateVec.x = currTranslateVec.x + unitVec[2].x;
        currTranslateVec.y = currTranslateVec.y + unitVec[2].y;
    } else if(unitVecDir==2){
        currTranslateVec.x = currTranslateVec.x + unitVec[3].x;
        currTranslateVec.y = currTranslateVec.y + unitVec[3].y;
    }

}
//Reset translate vector
void resetTranslateVec(){
    currTranslateVec.x = 0;
    currTranslateVec.y = 12;
}
//Set current and next tetrimino which is required at
//beginning of the game
void setCurrentNextTetrimino(int rand_c, int rand_n){

    for(int i=0;i<NUM_BOX;i++){
        current_T.body[i].x = tetrimino[rand_c].body[i].x;
        current_T.body[i].y = tetrimino[rand_c].body[i].y;
    }

    for(int i=0;i<NUM_BOX;i++){
        next_T.body[i].x = tetrimino[rand_n].body[i].x;
        next_T.body[i].y = tetrimino[rand_n].body[i].y;
    }
}

//set current tetrimino by next tetrimino
//and get new random next tetrimino
void getNextTetrimino(int rand_n){

    for(int i=0;i<NUM_BOX;i++){
        current_T.body[i].x = next_T.body[i].x;
        current_T.body[i].y = next_T.body[i].y;
    }

    for(int i=0;i<NUM_BOX;i++){
        next_T.body[i].x = tetrimino[rand_n].body[i].x;
        next_T.body[i].y = tetrimino[rand_n].body[i].y;
    }
}

int checkCollisionWithBoxes(struct Point2D r){

    for(int i=board_index_i_y-1;i>=0;i--){
        for(int j=0;j<board_index_j_x;j++){
            if(tetrisBoard[i][j].flag_T == 1
                && tetrisBoard[i][j].box.y == r.y
                && tetrisBoard[i][j].box.x == r.x){
                    return 1;
                }
            }
        }
    return 0;
}

int checkOutOfBoard(int x){
    if( x > board_half_x || x < neg_board_half_x){
        return 1;
    }
    return 0;
}

//Return 1 if it reachs bottom of the board or collide with boxes,
//else return 0
int translateTetrimino(int rand_c, int rotationFlag){

    int outOfBoard=0;
    int collision=0;
    int stopY = 0;
    struct Tetriminos current_T_TEMP;
    struct Tetriminos rotate_T_TEMP;
    int flag;

    //1) Rotate and Translate
    //   1.1) check collision: if yes, then do not rotate
    //   1.2) Check OutOfBox: if yes, then do not rotate
    //                   else rotate.
    if((rotationFlag == 0 || rotationFlag == 1) && rand_c != O_BLOCK){

        int x, y;

        for(int i=0;i<NUM_BOX;i++){
            x = tetrimino[rand_c].body[i].y * currRotationVec[rotationFlag].x;
            y = tetrimino[rand_c].body[i].x * currRotationVec[rotationFlag].y;

            rotate_T_TEMP.body[i].x = x + currTranslateVec.x;
            rotate_T_TEMP.body[i].y = y + currTranslateVec.y;

            //flag = checkOutOfBoard(rotate_T_TEMP.body[i].x);
            if(checkOutOfBoard(rotate_T_TEMP.body[i].x)){
                outOfBoard = 1;
            }

            if(checkCollisionWithBoxes(rotate_T_TEMP.body[i])==1){
                collision = 1;
            }
        }

        //Rotate only if Tetrimino do not go out of Tetris board
        //and do not collide with Tetris boxes.
        if(outOfBoard == 0 && collision == 0){

            for(int i=0;i<NUM_BOX;i++){
                x = tetrimino[rand_c].body[i].y * currRotationVec[rotationFlag].x;
                y = tetrimino[rand_c].body[i].x * currRotationVec[rotationFlag].y;

                tetrimino[rand_c].body[i].x = x;
                tetrimino[rand_c].body[i].y = y;
            }
        }

        outOfBoard = 0;
        collision = 0;
    }

    //2) Translate Tetrimino
    for(int i=0;i<NUM_BOX;i++){
        current_T_TEMP.body[i].x = tetrimino[rand_c].body[i].x + currTranslateVec.x;
        current_T_TEMP.body[i].y = tetrimino[rand_c].body[i].y + currTranslateVec.y;

        if(checkOutOfBoard(current_T_TEMP.body[i].x)){
            outOfBoard = 1;
        }
    }
    //3) Check OutOfBox: if yes, then reset direction to downward (-ne y-axis)
    //   and translate again
    if (outOfBoard==1){
        revertTranslateVec();
        unitVecDir = 1;
        updTranslateVec();
        for(int i=0;i<NUM_BOX;i++){
            current_T_TEMP.body[i].x = tetrimino[rand_c].body[i].x + currTranslateVec.x;
            current_T_TEMP.body[i].y = tetrimino[rand_c].body[i].y + currTranslateVec.y;
        }
    }

    //4) Check collision with boxes vertically or horizontally
    for(int i=0;i<NUM_BOX;i++){
        if(checkCollisionWithBoxes(current_T_TEMP.body[i])){
            collision = 1;
            if(unitVecDir == 1)
                stopY = 1; //Collided vertically
            else
                stopY = 2; //Collided horizontally from side
        }
    }

    // 5) If collided horizontally then Tetrimino moving left or right
    //     so, revert translate vector and move it downward (-ne y-axis)
    //     again, check collision
    if(collision == 1 && stopY == 2){

        revertTranslateVec();
        unitVecDir = 1;
        updTranslateVec();
        collision = 0;
        stopY = 0;
        for(int i=0;i<NUM_BOX;i++){
            current_T_TEMP.body[i].x = tetrimino[rand_c].body[i].x + currTranslateVec.x;
            current_T_TEMP.body[i].y = tetrimino[rand_c].body[i].y + currTranslateVec.y;

            if(checkCollisionWithBoxes(current_T_TEMP.body[i])){
                collision = 1;
                stopY = 1;
            }
        }
    }

    // 6) Check Tetrimino reached the bottom
    //    Check Game over: If tetrimino collided vertically, but any box is outside the window
    for(int i=0;i<NUM_BOX;i++){
        if(current_T_TEMP.body[i].y == neg_board_half_y){
            stopY = 2; //Reached the bottom
        } else if(current_T_TEMP.body[i].y == board_half_y && stopY == 1){
            stopY = 3; //Unable to enter board. Game over
        }
    }

    // If there is no collision, finally translate the Tetrimino
    if(collision == 0){
        for(int i=0;i<NUM_BOX;i++){
            current_T.body[i].x = tetrimino[rand_c].body[i].x + currTranslateVec.x;
            current_T.body[i].y = tetrimino[rand_c].body[i].y + currTranslateVec.y;
        }
    }

  return stopY;
}

void setTetrisBoard(){

    for(int i=board_index_i_y-1;i>=0;i--){
        for(int j=0;j<board_index_j_x;j++){
            if(tetrisBoard[i][j].flag_T == 0)
            for(int z=0;z<NUM_BOX;z++){
                if(tetrisBoard[i][j].box.x == current_T.body[z].x
                   && tetrisBoard[i][j].box.y == current_T.body[z].y){
                    tetrisBoard[i][j].flag_T = 1;
                }
            }
        }
    }
}

void shiftBoxesTopToBottom(int startAt){

    for(int i=startAt;i>=1;i--){
        for(int j=0;j<board_index_j_x;j++){
            tetrisBoard[i][j].flag_T = tetrisBoard[i-1][j].flag_T;
            tetrisBoard[i-1][j].flag_T = 0;
        }
    }

    //Set Top row boxes to Zero
    for(int j=0;j<board_index_j_x;j++){
        tetrisBoard[0][j].flag_T = 0;
    }
}

void drawWindow(){

    //Draw up side border
    for(int i=window[0].x;i<=window[1].x;i++){
        gotoxy(i,window[0].y);
        printf("\xB0");
    }

    //Draw down side border
    for(int i=window[3].x;i<=window[2].x;i++){
        gotoxy(i,window[3].y);
        printf("\xB0");
    }

    //Draw left side border
    for(int i=window[0].y;i<=window[3].y;i++){
        gotoxy(window[0].x,i);
        printf("\xB0");
    }

    //Draw right side border
    for(int i=window[1].y;i>=window[2].y;i--){
        gotoxy(window[1].x,i);
        printf("\xB0");
    }
}

void drawTetrimino(struct Tetriminos block){

    for(int i=0;i<NUM_BOX;i++){
        int x = block.body[i].x ;
        int y = block.body[i].y;
        if(y<=10){
            gotoxy(x,y);
            printf("#");
        }
    }
}

void drawNextTetrimino(struct Tetriminos block){

    for(int i=0;i<NUM_BOX;i++){
        int x = block.body[i].x ;
        int y = block.body[i].y;
        if(y<=10){
            gotoxy(x + 10,y);
            printf("#");
        }
    }
}

void removeTetrimino(struct Tetriminos block){

    for(int i=0;i<NUM_BOX;i++){
        int x = block.body[i].x;
        int y = block.body[i].y;
        if(y<=10){
            gotoxy(x,y);
            printf(" ");
        }
    }
}

void removeNextTetrimino(struct Tetriminos block){

    for(int i=0;i<NUM_BOX;i++){
        int x = block.body[i].x ;
        int y = block.body[i].y;
        if(y<=10){
            gotoxy(x + 10,y);
            printf(" ");
        }
    }
}

void removeBoxesInRow(int atRow){
    for(int i=0;i<board_index_j_x;i++){
        gotoxy(tetrisBoard[atRow][i].box.x,tetrisBoard[atRow][i].box.y);
        printf(" ");
    }

}

void reDrawBoxes(int fromAt){
    for(int i=fromAt;i>=0;i--){
        for(int j=0;j<board_index_j_x;j++){
            if(tetrisBoard[i][j].flag_T == 1){
                gotoxy(tetrisBoard[i][j].box.x,tetrisBoard[i][j].box.y);
                printf("#");
            } else {
                gotoxy(tetrisBoard[i][j].box.x,tetrisBoard[i][j].box.y);
                printf(" ");
            }
        }
    }
}

void checkRowAndReDrawBoard(){

    int product = 0;

    for(int i=board_index_i_y-1;i>=0;i--){
            product = 1;
        for(int j=0;j<board_index_j_x;j++){
            product = product * tetrisBoard[i][j].flag_T;
        }
        if(product == 1){
            score++;
            removeBoxesInRow(i);
            shiftBoxesTopToBottom(i);
            reDrawBoxes(i);

            //reset loop i value to check again in same position
            //after shifting boxes from top to down
            i++;
            product = 1;
        }
    }
}
