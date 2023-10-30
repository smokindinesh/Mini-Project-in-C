//File pointers
FILE *fp, *ft;

//Read data from file
int view(struct data d[], int sz){

    struct data a;
    int i=0;
    fp = fopen(DATA_FILE,"rb");
    while(fread(&a,sizeof(a),1,fp)==1 && i<sz){
        d[i]=a;
        i++;
    }
    fclose(fp);
    return i;
}

//Add data into the file
void add(struct data d){

    fp = fopen(DATA_FILE,"ab+");
    fseek(fp,0,SEEK_END);
    fwrite(&d,sizeof(d),1,fp);
    fclose(fp);
}

//Update data into the file
void update(struct data d, char *oldNumber){

    struct data a;

    fp=fopen(DATA_FILE,"rb+");

    while(fread(&a,sizeof(a),1,fp)==1){
        if(strcmp(oldNumber, a.mPhone)==0){
            fseek(fp,ftell(fp)-sizeof(a),0);
            fwrite(&d,sizeof(d),1,fp);
            fclose(fp);
        }
    }

}

//Delete data from the file
void del(char *delNumber){

    struct data a;

    fp=fopen(DATA_FILE,"rb+");
    ft=fopen(TEMP_FILE,"wb+");

    while(fread(&a,sizeof(a),1,fp)==1){
        if(strcmp(delNumber, a.mPhone)!=0){
            fwrite(&a,sizeof(a),1,ft);
        }
    }

    fclose(ft);
    fclose(fp);

    remove(DATA_FILE);
    rename(TEMP_FILE,DATA_FILE);

}

//Search mobile number in the file
int searchByNum(char *num){

    struct data a;
    int i=0;
    if(strcmp(num,"")==0){
        i=2;
    } else {
        fp = fopen(DATA_FILE,"rb");
        while(fread(&a,sizeof(a),1,fp)==1){
            if(strcmp(num, a.mPhone)==0){
                i=1; //return 1 if found
            }
        }
        fclose(fp);
    }

    return i; //return 0 if not found
}

//Get string input from user
static void getString(char *buff, size_t sz){

    fgets(buff,sz, stdin);
    if ((strlen(buff) > 0) && (buff[strlen (buff) - 1] == '\n'))
        buff[strlen (buff) - 1] = '\0';

    fflush(stdin);
}





