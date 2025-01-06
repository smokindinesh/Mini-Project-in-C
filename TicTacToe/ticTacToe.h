#define boardSize_X 21
#define boardSize_Y 12
#define boardStart_X 10
#define boardStart_Y 2
#define numBox 9
#define numDiv 3
#define firstPlayer 0
#define secondPlayer 1

int initBoxSize_X = boardSize_X/3;// 7
int initBoxSize_Y = boardSize_Y/3;//4

int msgStart_X = boardSize_X + boardStart_X + 5;
int msgStart_Y = boardStart_Y;

struct Point2D {
    int x;
    int y;
};

struct BoardBox {
    struct Point2D center;
    int value;
};

struct BoardBox box[numBox];

void initBoard(){

    for(int i =0; i<numBox; i++){
        box[i].center.x = initBoxSize_X/2 + initBoxSize_X * (i % 3);
        box[i].center.y = initBoxSize_Y/2 + initBoxSize_Y * (i / 3);
        box[i].value = 0;
        printf("Box %d: X: %d Y: %d Value: %d",i,box[i].center.x,box[i].center.y,box[i].value);

    }
}

void setBox(int i, int player){
    if(player==human)
        box[i].value= 3;
    else if(player==computer)
        box[i].value= 5;
}

int isBoxEmpty(int i){

    return box[i].value;
}

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

    total = box[0].value + box[4].value + box[8].value;

    if(total == 9 || total == 15)
        return 1;

    total = box[2].value + box[4].value + box[6].value;

    if(total == 9 || total == 15)
        return 1;

    return 0;
}


