struct Player {
    int numOfTurn;
    int selectedBox;
    int currentPlayer;
    int nextPlayer;

};

struct Player p;

void initPlayer(int player_1, int player_2){

    p.numOfTurn = 0;
    p.selectedBox = 0;
    p.currentPlayer = player_1;
    p.nextPlayer = player_2;
}

void setNextPlayer(int box, int prevPlayer){

    p.numOfTurn++;
    p.selectedBox = box;
    p.currentPlayer = p.nextPlayer;
    p.nextPlayer = prevPlayer;

}

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

    if((box[0].value + box[4].value + box[8].value) == total){
        if(box[0].value==0)
            return 0;
        else if (box[4].value==0)
            return 4;
        else
            return 8;
    }

    if((box[2].value + box[4].value + box[7].value) == total){
        if(box[2].value==0)
            return 2;
        else if (box[4].value==0)
            return 4;
        else
            return 6;
    }

    return -1;
}

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

int getNextMove(){

    int boxNum;


    if(p.numOfTurn >= 3){
        //Get winning position
        boxNum = getWinDrawMove(1);
        if(boxNum!=-1)
            return boxNum;

        //Get Draw position
        boxNum = getWinDrawMove(0);
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
