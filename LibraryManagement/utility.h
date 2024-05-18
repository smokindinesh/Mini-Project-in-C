
//File pointers
FILE *fp, *ft, *fa;

// Define Constant Variables
#define ESC 27
#define MAX_USR_SZ 20
#define MAX_PWD_SZ 20
#define MAX_ID 10
#define MAX_NAME 20
#define MAX_YR 5
#define MAX_TITLE 50
#define DATE_SZ 64
#define READ_ARRAY_SZ 15

struct password{
    char userName[MAX_USR_SZ];
    char password[MAX_PWD_SZ];
};

struct stuProfile{
    char stuID[MAX_ID];
    char fName[MAX_NAME];
    char lName[MAX_NAME];
    char faculty[MAX_NAME];
};

struct books{
    char bookID[MAX_ID];
    char title[MAX_TITLE];
    char author[MAX_NAME];
    char genre[MAX_NAME];
    char year[MAX_YR];
    char stockCount[MAX_ID];
    char shelfNo[MAX_ID];
};

struct stuBooks{
    char stuID[MAX_ID];
    char bookID[MAX_ID];
    char title[MAX_TITLE];
    char author[MAX_NAME];
    char startDate[DATE_SZ];
    char endDate[DATE_SZ];
};

struct books *bk;
int bkCount=0;
//Function declaration
static void getString(char *buff, size_t sz);
void printWelcomeMsg();
void printStudentWelcomeMsg();


//Function definition

//Get string input from user
static void getString(char *buff, size_t sz){

    fgets(buff,sz, stdin);
    if ((strlen(buff) > 0) && (buff[strlen(buff) - 1] == '\n'))
        buff[strlen(buff) - 1] = '\0';

    fflush(stdin);
}

static void getPassword(char *buff, size_t sz){

    char ch;
    int i=0;

    while(ch!=13 && i!=sz)
    {
        ch=getch();

        if(ch==8 && i>0){
            printf("\b \b");
            i--;
            buff[i]='\0';
        }else if(ch!=13 && ch!=8){

            putch('*');
            buff[i] = ch;
            i++;
        }
    }

    buff[i]='\0';
    ch=' ';i=0;
}

void printWelcomeMsg()
{
    system("cls");

    gotoxy(35,6);
    printf("----Welcome to Library Management System----");
}
void printStudentWelcomeMsg(struct stuProfile st)
{
    system("cls");
    gotoxy(3,1);
    printf("User Details:");
    gotoxy(3,2);
    printf("%s %s (%s)", st.fName,st.lName,st.stuID);
    gotoxy(3,3);
    printf("Faculty-> %s", st.faculty);
    gotoxy(35,6);
    printf("----Welcome to Library Management System----");
}

int stringToInt(char *str){
    int num = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        num = num * 10 + (str[i] - 48);
    }

    return num;
}

static void intToString(char* str, int num){

    char temp[MAX_ID];
    sprintf(temp,"%d",num);
    strcpy(str,temp);

}
