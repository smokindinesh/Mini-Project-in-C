
#define STU_BK_DATA_FILE "stuBooks.dat"
//#define STU_BK_TEMP_FILE "stuBooksTemp.dat"

//Read data from file
int viewStuBook(struct stuBooks d[], int sz){

    struct stuBooks a;
    int i=0;
    fp = fopen(STU_BK_DATA_FILE,"rb");
    while(fread(&a,sizeof(a),1,fp)==1 && i<sz){
        d[i]=a;
        i++;
    }
    fclose(fp);
    return i;
}

int viewMyStuBook(struct stuBooks d[], char stuID[MAX_ID],int sz){

    struct stuBooks a;
    int i=0;
    fp = fopen(STU_BK_DATA_FILE,"rb");
    while(fread(&a,sizeof(a),1,fp)==1 && i<sz){
        if(strcmp(a.stuID,stuID)==0){
            d[i]=a;
            i++;
        }
    }
    fclose(fp);
    return i;
}
//Add data into the file
void addStuBook(struct stuBooks d){

    fp = fopen(STU_BK_DATA_FILE,"ab+");
    fseek(fp,0,SEEK_END);
    fwrite(&d,sizeof(d),1,fp);
    fclose(fp);
}


//Update data into the file
int updateStuBook(char bookID[MAX_ID],char stuID[MAX_ID],char retDate[DATE_SZ]){

    struct stuBooks a;
    int flag=0;

    fp=fopen(STU_BK_DATA_FILE,"rb+");

    while(fread(&a,sizeof(a),1,fp)==1){
        if(strcmp(bookID, a.bookID)==0 && strcmp(stuID, a.stuID)==0){
            strcpy(a.endDate,retDate);
            fseek(fp,ftell(fp)-sizeof(a),0);
            fwrite(&a,sizeof(a),1,fp);
            fclose(fp);
            flag=1;
        }
    }
    fclose(fp);

    return flag;
}
