#define boardSize_X 21 //Board length, toward x-axis
#define boardSize_Y 12 //Board height, toward y-axis
#define boardStart_X 10 //Board starting x-coordinate
#define boardStart_Y 2 //Board starting x-coordinate
#define numBox 9 //Number of boxes
#define numDiv 3 //Number of division on board
#define firstPlayer 0 //Flag for first player
#define secondPlayer 1 //Flag for second player

int initBoxSize_X = boardSize_X/3; //7 ,each box length , toward x-axis
int initBoxSize_Y = boardSize_Y/3; //4 ,each box height , toward y-axis

int msgStart_X = boardSize_X + boardStart_X + 5; //X-Coordinate value to start message on window
int msgStart_Y = boardStart_Y; //Y-Coordinate value to start message on window

//Structure definition to store window x,y coordinates
struct Point2D {
    int x;
    int y;
};

//Structure definition to define each game board boxes
struct BoardBox {
    struct Point2D center;
    int value;
};

struct BoardBox box[numBox]; //struct variable to store nine boxes of the board.

void initBoard(){
    //Calculate the center of box to display X or O.
    //Also, assign zero value to all boxes to represent it as empty
    for(int i =0; i<numBox; i++){
        box[i].center.x = initBoxSize_X/2 + initBoxSize_X * (i % 3);
        box[i].center.y = initBoxSize_Y/2 + initBoxSize_Y * (i / 3);
        box[i].value = 0;
    }
}

void setBox(int i, int player){
    //Set the value of box based on player type
    if(player==human)
        box[i].value= 3;
    else if(player==computer)
        box[i].value= 5;
}

int isBoxEmpty(int i){

    return box[i].value;
}
//This function check the winner
int checkWinner(){

    int total=0;

    //Check Column
    for(int i=0;i<3;i++){
        total = box[i].value + box[i + 3].value + box[i + 6].value;
        if (total == 9 || total == 15)
            return 1;
    }

    //Check rows
    for(int i=0;i<9;i=i+3){
        total = box[i].value + box[i + 1].value + box[i + 2].value;
        if (total == 9 || total == 15)
            return 1;
    }

    //Check first diagonal of the board
    total = box[0].value + box[4].value + box[8].value;

    if(total == 9 || total == 15)
        return 1;

    //Check second diagonal of the board
    total = box[2].value + box[4].value + box[6].value;

    if(total == 9 || total == 15)
        return 1;

    return 0;
}


