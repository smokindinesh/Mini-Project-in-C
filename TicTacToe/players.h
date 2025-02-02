
//structure definition to store player information
struct Player {
    int numOfTurn;
    int selectedBox;
    int currentPlayer;
    int nextPlayer;

};

struct Player p; //Global variable to represent player

//Function to initialize players
void initPlayer(int player_1, int player_2){

    p.numOfTurn = 0;
    p.selectedBox = 0;
    p.currentPlayer = player_1;
    p.nextPlayer = player_2;
}

//Set the value of current player and next player
//in each turn of the game
void setNextPlayer(int box, int prevPlayer){

    p.numOfTurn++;
    p.selectedBox = box;
    p.currentPlayer = p.nextPlayer;
    p.nextPlayer = prevPlayer;

}

//This function will return game winning move or game draw move based on prameters
//flag == 0, winning move
//flag == 1, draw move
int getWinDrawMove(int flag){

    int total=-1;

    if(flag==0){
        total=10;
    } else if(flag==1){
        total=6;
    }

    //Check Column
    for(int i=0;i<3;i++){
        if (total == (box[i].value + box[i + 3].value + box[i + 6].value)) {
            if(box[i].value==0)
                return i;
            else if (box[i + 3].value==0)
                return i+3;
            else if (box[i + 6].value==0)
                return i+6;
        }
    }

    //Check rows
    for(int i=0;i<9;i=i+3){
        if ((box[i].value + box[i + 1].value + box[i + 2].value) == total) {
            if(box[i].value==0)
                return i;
            else if (box[i+1].value==0)
                return i+1;
            else if (box[i+2].value==0)
                return i+2;
        }
    }
    //Check first diagonal of the board
    if((box[0].value + box[4].value + box[8].value) == total){
        if(box[0].value==0)
            return 0;
        else if (box[4].value==0)
            return 4;
        else
            return 8;
    }
    //Check second diagonal of the board
    if((box[2].value + box[4].value + box[6].value) == total){
        if(box[2].value==0)
            return 2;
        else if (box[4].value==0)
            return 4;
        else
            return 6;
    }

    return -1;
}

//Get location of boxes 5,2,4,6,8 respectively
int getMake2()
{
    if(box[4].value == 0)
        return 4;
    if(box[1].value == 0)
        return 1;
    if(box[3].value == 0)
        return 3;
    if(box[5].value == 0)
        return 5;
    if(box[7].value == 0)
        return 7;

    return -1;
}

//Get location of boxes 1,3,7,9 respectively
int getMake4()
{
    if(box[0].value == 0)
        return 0;
    if(box[2].value == 0)
        return 2;
    if(box[6].value == 0)
        return 6;
    if(box[8].value == 0)
        return 8;

    return -1;
}

//This function return best next move for computer player
int getNextMove(){

    int boxNum;


    if(p.numOfTurn >= 3){
        //Get winning position
        boxNum = getWinDrawMove(0);
        if(boxNum!=-1)
            return boxNum;

        //Get Draw position
        boxNum = getWinDrawMove(1);
        if(boxNum!=-1)
            return boxNum;
    }

    boxNum = getMake2();
    if(boxNum!=-1)
        return boxNum;

    boxNum = getMake4();
    if(boxNum!=-1)
        return boxNum;

    return -1;
}
