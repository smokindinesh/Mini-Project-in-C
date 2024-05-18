
#define DATA_FILE "adminAccess.dat"
#define TEMP_FILE "tempFile.dat"

//Read data from file

int check(struct password d,int flag){

    struct password a;
    int i=0;
    fp = fopen(DATA_FILE,"rb");
    while(fread(&a,sizeof(a),1,fp)==1){
        if(flag==0){
            if(strcmp(a.userName,d.userName)==0 && strcmp(a.password,d.password)==0){
                i=1;
                break;
            }
        } else if (flag==1){
            if(strcmp(a.userName,d.userName)==0){
                i=1;
                break;
            }
        }
    }
    fclose(fp);
    return i;
}

//Read data from file
int view(struct password d[], int sz){

    struct password a;
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
void add(struct password d){

    fp = fopen(DATA_FILE,"ab+");
    fseek(fp,0,SEEK_END);
    fwrite(&d,sizeof(d),1,fp);
    fclose(fp);
}


//Update data into the file
int update(struct password d){

    struct password a;
    int flag=0;

    fp=fopen(DATA_FILE,"rb+");

    while(fread(&a,sizeof(a),1,fp)==1){
        if(strcmp(a.userName, d.userName)==0){
            fseek(fp,ftell(fp)-sizeof(a),0);
            fwrite(&d,sizeof(d),1,fp);
            fclose(fp);
            flag=1;
        }
    }
    fclose(fp);

    return flag;
}

//Delete data from the file
int del(char *userName){

    struct password a;
    int flag=0;

    fp=fopen(DATA_FILE,"rb+");
    ft=fopen(TEMP_FILE,"wb+");

    while(fread(&a,sizeof(a),1,fp)==1){
        if(strcmp(userName, a.userName)!=0){
            fwrite(&a,sizeof(a),1,ft);
        } else {
            flag=1;
        }
    }

    fclose(ft);
    fclose(fp);

    remove(DATA_FILE);
    rename(TEMP_FILE,DATA_FILE);

    return flag;

}
