#define winXLen 40 //Snake game play window x-coordinate size
#define winYLen 20 //Snake game play window y-coordinate size
#define startPosX 11 //Game play window starting x-coordinate
#define startPosY 1 //Game play window starting y-coordinate
#define startLen 3 //Game play window starting y-coordinate

#define sSize 800 //Max size of the snake must be always >= winXLen * winYLen

#define UP 0 //Up direction array index
#define DW 1 //Down direction array index
#define RT 2 //Right direction array index
#define LT 3 //Left direction array index

static const int winBorderX = winXLen + startPosX;
static const int winBorderY = winYLen + startPosY;

static const int wX1 = startPosX-1, wY1 = startPosY-1; //First Corner of the Window

static const int wX2 = winBorderX, wY2 = startPosY-1; //Second Corner of the Window

static const int wX3 = winBorderX, wY3 = winBorderY; //Third Corner of the Window

static const int wX4 = startPosX-1, wY4 = winBorderY; //Fourth Corner of the Window

struct Point2D{
    int x;
    int y;
};

struct Snake{
    struct Point2D body[sSize];
    struct Point2D head;
    struct Point2D tail;
    struct Point2D dir;
    int length;
};

struct Snake s;

struct Point2D dir[4]; //array for snake direction vector
struct Point2D food[sSize];

void initDir(){

    //Up direction
    dir[UP].x = 0;
    dir[UP].y = -1;

    //Down direction
    dir[DW].x = 0;
    dir[DW].y = 1;

    //Right Direction
    dir[RT].x = 1;
    dir[RT].y = 0;

    //Left Direction
    dir[LT].x = -1;
    dir[LT].y = 0;
}

void initFood(){

    int i=0;
    for(int j=0;j<winYLen;j++){
        for(int k=0;k<winXLen;k++){
            food[i].x = k + startPosX;
            food[i].y = j + startPosY;

            i++;
        }
    }
}

void initSnake(){

    for(int i=0;i<startLen;i++){
        s.body[i].x = startPosX + i;
        s.body[i].y = 10;
    }

    s.head.x = s.body[startLen-1].x;
    s.head.y = s.body[startLen-1].y;

    //In first frame of the game tail position
    //need to be out of window or blank
    s.tail.x = 0;
    s.tail.y = 0;

    s.dir.x = dir[RT].x; s.dir.y = dir[RT].y;

    s.length = startLen;
}

int buildSnake(struct Point2D f,struct Point2D d){

    if(s.dir.x != -d.x && s.dir.y != -d.y){
        s.dir.x = d.x; s.dir.y = d.y;
    }

    s.head.x = s.body[s.length-1].x + s.dir.x;
    s.head.y = s.body[s.length-1].y + s.dir.y;

    s.body[s.length].x = s.head.x;
    s.body[s.length].y = s.head.y;
    if(s.head.x == f.x && s.head.y == f.y){
        s.length++;
        return 1;
    } else {
        s.tail.x = s.body[0].x;
        s.tail.y = s.body[0].y;
        //Swap snake body back starting from initial index
        for (int i = 0;i<s.length;i++){
            s.body[i].x = s.body[i+1].x;
            s.body[i].y = s.body[i+1].y;
        }

    }

    return 0;
}

int checkCollision(){
    if(s.length == sSize){
        return 2;
    }

    if(s.head.x == wX1 || s.head.x == wX2){
        return 1;
    }

    if(s.head.y == wY1 ||s.head.y == wY3){
        return 1;
    }

    for (int i=0;i<s.length-2;i++){

        if(s.head.x == s.body[i].x && s.head.y == s.body[i].y){
            return 1;
        }
    }

    return 0;
}

