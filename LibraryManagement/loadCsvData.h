
// adjust BUFFER_SZ to suit longest line
#define BUFFER_SZ 1024
#define STU_COL_NUM 4
#define BK_COL_NUM 7
#define MAX_ERROR_NUM 5
#define BK_ROW_NUM 15
#define PASS 1
#define FAIL 0
#define FALSE 0
#define TRUE 1
#define STU_DATA_FILE "StudentData.csv"
#define BK_DATA_FILE "BookData.csv"
#define TMP_BK_DATA_FILE "tmpBookData.csv"


// field offsets into sFields array for Student Profile data:
#define ID 0
#define fNAME 1
#define lNAME 2
#define FACULTY 3

// field offsets into lFields array for Books data:

#define BOOK_ID 0
#define TITLE 1
#define AUTHOR 2
#define GENRE 3
#define YEAR 4
#define STK_CNT 5
#define SHELF_NO 6


static int getStudentID(char stuId[MAX_ID], struct stuProfile *st);
static int  loadStuValues(char *line, char *sFields[STU_COL_NUM]);
int readBooks();
static int  loadBookValues(char *line, char *lFields[BK_COL_NUM]);
int getRowCount(FILE *fpl);

static int getStudentID(char stuId[MAX_ID], struct stuProfile *st){

    FILE *fps;

    // char* array will point to fields
    char *sFields[STU_COL_NUM];

    int err_count = 0;

    fps = fopen(STU_DATA_FILE, "r");
    if(fps == NULL) {
        //printf("Error opening file: %d\n",errno);
        return(FAIL);
    }

    char inBuffer [BUFFER_SZ];
    long rowNum = 0L;

    while (!feof(fps)) {

        // load line into static buffer
        if(fgets(inBuffer, BUFFER_SZ-1, fps)==NULL)
            break;

        // skip first line (headers)
        if(++rowNum==1)
            continue;

        // jump over empty lines
        if(strlen(inBuffer)==0)
            continue;
        // set pFields array pointers to null-terminated string fields in inBuffer
        if(loadStuValues(inBuffer,sFields)==FAIL){
           err_count++;
            if(err_count > MAX_ERROR_NUM)
                break;
        } else {
            //Compare Student ID
            if(strcmp(sFields[ID],stuId)==0){

                strcpy(st->stuID,sFields[ID]);
                strcpy(st->fName,sFields[fNAME]);
                strcpy(st->lName,sFields[lNAME]);
                strcpy(st->faculty,sFields[FACULTY]);

                fclose(fps);
                return PASS;
            }
        }
    }
    fclose(fps);

    return FAIL;
}


static int  loadStuValues(char *line, char *sFields[STU_COL_NUM]){
    char delim=',';
    if(line == NULL)
        return FAIL;

    // chop of last char of input if it is a CR or LF (e.g.Windows file loading in Unix env.)
    // can be removed if sure fgets has removed both CR and LF from end of line
    if(*(line + strlen(line)-1) == '\r' || *(line + strlen(line)-1) == '\n')
        *(line + strlen(line)-1) = '\0';

    char *cptr = line;
    int fld = 0;
    int inquote = FALSE;
    char ch;

    sFields[fld]=cptr;
    while((ch=*cptr) != '\0' && fld < STU_COL_NUM){

        if(ch == '"') {
            if(! inquote){
                sFields[fld]=cptr+1;
            }else {
                *cptr = '\0';               // zero out " and jump over it
            }
            inquote = ! inquote;
        } else if(ch == delim && ! inquote){
            *cptr = '\0';                   // end of field, null terminate it
            sFields[++fld]=cptr+1;
        }

        cptr++;
    }
    if(fld > STU_COL_NUM-1){
        return FAIL;
    } else if (fld < STU_COL_NUM-1){
        return FAIL;
    }
    return PASS;
}


int readBooks(){

    FILE *fpl;

    fpl = fopen(BK_DATA_FILE,"r");

    if(fpl == NULL) {
        //printf("Error opening file: %d\n",errno);
        return(FAIL);
    }

    int bkSize=getRowCount(fpl);
    bkSize--;

    rewind(fpl);

    bk = (struct books*)malloc(bkSize * sizeof(struct books));

    //printf("Size of array: %d\n",bkSize);

    // char* array will point to fields
    char *lFields[BK_COL_NUM];

    int err_count = 0;

    char inBuffer [BUFFER_SZ];
    int rowNum = 0;

    while(!feof(fpl)){
        //printf("Error in line %d\n",rowNum);
        // load line into static buffer
        if(fgets(inBuffer, BUFFER_SZ-1, fpl)==NULL)
            break;

        // skip first line (headers)
        if(++rowNum==1)
            continue;

        // jump over empty lines
        if(strlen(inBuffer)==0)
            continue;
        // set pFields array pointers to null-terminated string fields in inBuffer
        if(loadBookValues(inBuffer,lFields)==FAIL){
           err_count++;
           //printf("Error in line %d\n",rowNum);
            if(err_count > MAX_ERROR_NUM)
                return FAIL;
        } else {

            //printf("Pointer Address is at %p\n",(void*)bk);

            strcpy(bk->bookID,lFields[BOOK_ID]);
            strcpy(bk->title,lFields[TITLE]);
            strcpy(bk->author,lFields[AUTHOR]);
            strcpy(bk->genre,lFields[GENRE]);
            strcpy(bk->year,lFields[YEAR]);
            strcpy(bk->stockCount,lFields[STK_CNT]);
            strcpy(bk->shelfNo,lFields[SHELF_NO]);

            bk++;
        }

    }

    bk=(bk-bkSize);
    //printf("loaded successfully\n");

    fclose(fpl);

    return bkSize;
}

static int  loadBookValues(char *line, char *lFields[BK_COL_NUM]){
    char delim=',';
    if(line == NULL)
        return FAIL;

    // chop of last char of input if it is a CR or LF (e.g.Windows file loading in Unix env.)
    // can be removed if sure fgets has removed both CR and LF from end of line
    if(*(line + strlen(line)-1) == '\r' || *(line + strlen(line)-1) == '\n')
        *(line + strlen(line)-1) = '\0';

    char *cptr = line;
    int fld = 0;
    int inquote = FALSE;
    char ch;

    lFields[fld]=cptr;
    while((ch=*cptr) != '\0' && fld < BK_COL_NUM){

        if(ch == '"') {
            if(! inquote){
                lFields[fld]=cptr+1;
            }else {
                *cptr = '\0';               // zero out " and jump over it
            }
            inquote = ! inquote;
        } else if(ch == delim && ! inquote){
            *cptr = '\0';                   // end of field, null terminate it
            lFields[++fld]=cptr+1;
        }

        cptr++;
    }
    if(fld > BK_COL_NUM-1){

        printf("Error!Field greater then column\n");
        return FAIL;
    } else if (fld < BK_COL_NUM-1){

        printf("Error!Field less then column\n");
        return FAIL;
    }
    return PASS;
}

int getRowCount(FILE *fpl){

    int n=0;
    char tBuffer [BUFFER_SZ];

    while(!feof(fpl)){

        // load line into static buffer
        if(fgets(tBuffer, BUFFER_SZ-1, fpl)==NULL)
            break;
        n++;
    }

    return n;
}

void writeBook(){

    FILE *fpl;

    fpl = fopen(TMP_BK_DATA_FILE,"w+");

    if(fpl != NULL){

        fprintf(fpl,"BookID,Title,Author,Genre,Year of Publication,Stock Count,Shelf Number\n");

        for(int i=0;i<bkCount;i++){
            fprintf(fpl,"\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",bk[i].bookID,bk[i].title,bk[i].author,bk[i].genre,bk[i].year,bk[i].stockCount,bk[i].shelfNo);
        }

    }

    fclose(fpl);

    remove(BK_DATA_FILE);
    rename(TMP_BK_DATA_FILE,BK_DATA_FILE);
}
