
#include <stdio.h>//For standard I/O Operation
#include <stdlib.h>//To use functions like system(); system("dos command"); - this performs the dos command given. Eg. system("del abc.txt"); - This command deletes the file abc.txt from current location of project
#include <windows.h>//Used in making gotoxy(int, int) function
#include <conio.h>//For getch(); getche() type of functions
#include <time.h>//To get system date and time
#include <math.h>//To calculate mathematical problems, used esp. in interest calculation


//I've divided our user defined functions into two parts: Minor Functions (which are used frequently to support execution of core porgram) and Major Functions (which are a part of core program).  Minor function definition from Line 12-25. Major function definitions from Line 27-40.

void gotoxy(int x,int y); //To move the cursor to x column and y row of output screen
void _password(char buffer[]);// To input password from user so that asterik (*) is displayed for each character entered. Similar to gets(string); function
void rectangle(int x,int y,int l,int b);// To make a rectangle starting from (x,y) with length l and breadth b
void cls(int x1,int y1,int x2, int y2); // To clear only certain portion of screen starting from (x1,y1) to (x2,y2). Notice this function has been used in date entry. When date is not in dd/mm/yyyy format, the wrong value is cleared on the screen
void increase(char i_id[]); // To increase ID by unit value. Eg. U001 ---> U002 and AC00099 ---> AC00100. Since i_id is an array, it is passed by reference. So the input value and changed value is obtained from  same variable i_id[]
void date_input(char date[]); // To convert date in format dd/mm/yyyy (The format in which user is asked to enter date) to mm/dd/yyyy (The format in which date is stored in data file)
void date_output(char date[]); //To convert date in format mm/dd/yy to dd MMM, yyyy. Eg. 01/01/11 is changed to 01 Jan, 2011
void currency(char cur[], float n); // To convert a floating number n into currency format in Hindu Arabic Number system. Eg. on execution of the statement currency(cur,123456.789); the value of cur will be "1,23,456.78"
void num2word(double n,char word[]);// To convert a floating (double) number n into word according to Hindu Arabic Number System
void _one(int n, char one[]); // This function is a part of function num2word(). Simple function that stores "One " for 1, "Two " for 2, ... upto 19 in string varaible one[].
void _ten(int n,char ten[]); // This function is a part of function num2word(). Simple function that stores "Ten " for 10, "Twenty " for 20, ... upto 90 in string varaible ten[].
int date_check(char date[]);//Function to check if date is in format dd/mm/yyyy or not. Returns 0 if the format is not valid and 1 for valid format.
void title();//Clears the screen and displays Program title, Current User and Current date on top of Screen
void welcome();// Displays welcome screen that you see as soon as program is executed

void admin();// Main program for ADMIN portion to manage user
void add_user();// To add a new user
void del_user();// To delete an existing user
void edit_user();// To edit user name and/or password of existing user
void view_log();// To view log history of user

void staff();//Main program for STAFF portion to manage accounts
void uptodate();// This function updates every account by calculating interest and stores the updated value. This function runs every time the program is executed.
void add_ac();// To create a new account
void deposit(); // To deposit cash in A/C
void withdraw(); // To withdraw cash from A/C
void fund_transfer();// To transfer cash from one account to another
void ac_info();// To view informations about the A/C and account holder
void transaction();// To view all the trasactions of an A/C



char date[13],ttime[10]; // These are global variables to store system date and time

FILE *fp,*fp1,*tfp; // File pointers

struct//Structure for storing User information
    {
        char uid[4];
        char name[30], password[30];

    } user;

struct account//Structure for storing account information
    {
        char ac_no[8];
        char fname[30], lname[30];
        char u_date[15];
        char dob[12];
        char sex;
        char address[50],contact[20];
        char ac_type;
        float c_bal,interest,t_bal;
    };

struct trans//Structure for storing transaction information
    {
        char ac_no[8],ac_t[25],_date[15],_ttime[10],usr[30];
        float amt;
    };

typedef struct//Structure for storing user log information
{
    char id[4];
    char name[30];
    char date[15]; //Log in date
    char stime[10];// Log in time
    char etime[10];// Log out or exit time
}user_log;

int gbl_flag=0;

int main()
{
    char c;
    welcome(); //Welcome sreen at beginning
    do
    {
        system("cls"); //Clears the screen
        rectangle(8,9,70,13);
        gotoxy(10,11); printf("Press A to Log in as ADMINISTRATOR or S to log in as STAFF\n\n\n\t\t\t\t\t");
        c=getche(); //Variable c stores the key pressed by user

        if(c=='A'||c=='a')
        {
            strcpy(user.name,"Admin");
            admin();
            break;
        }
        if (c=='S'||c=='s')
        {
            staff();
            break;
        }
        if (c==27) exit(0); //27 is ASCII code of escape key, means program exits when user presses Esc key insted to A or S

    }while(1); //infinite loop incase any key other than Esc, A, or S is pressed.



    return 0;
}




void staff()
{
    int i,ch;
//Log in Screen begins...

    char uname[30], pass[30],passwrd[30]={0},id[10],nam[30];
    int c=0,cnt=0;
    char ex,stime[9],etime[9];


    cnt=0;//This variable cnt counts the number of attempts of Log in
    do
    {
        system("cls");
        rectangle(10,8,70,15);
        gotoxy(7,5);printf("Only THREE attempts shall be allowed to enter username and password.");
        gotoxy(23,10); printf("Enter User name : "); scanf("%s",user.name);
        gotoxy(23,12); printf("Password        : ");
        char passwrd[30]={0};//To nullify the string passwrd
        _password(passwrd);
        strcpy(user.password,passwrd);
        cnt++;

        if (cnt==3)// when no of attempts exceeds 3
        {
            title();
            gotoxy(25,10); printf("Invalid User name or Password!\a");
            gotoxy(22,12);printf("Press ENTER to exit the program...");
            getch();
            exit(0);
        }



        c=0;//Counts the no. of user for which the name and password matches
        fp=fopen("USER.DAT","r");
        while(fscanf(fp,"%s %s %s\n",id,nam,pass)!=EOF)
        {
             strcpy(nam,strupr(nam));//Changing all strings id, nam, pass into uppercase
             strcpy(pass,strupr(pass));
             strcpy(user.name,strupr(user.name));
             strcpy(user.password,strupr(user.password));

             if((strcmp(user.name,nam)==0)&&(strcmp(user.password,pass)==0)) //if the combination matches value of c is increased and user id of req user is stored in user.id
             {
                 c++;
                 strcpy(user.uid,id);
             }
         }

        fclose(fp);

        title();
        if (c==0)// when no records are found c=0
        {

            gotoxy(10,10); printf("Cannot find the given combination of USER NAME and PASSWORD!\a");
            getch();
        }
        else break; //terminates do... while loop if record found




    } while(1);//not exactly infinite as user is prompted only maximum three times but the terminating conditions are on line 146 and 176


    _strtime(stime);

//Log in screen ends





//Main Menu begins//
    uptodate(); // To update interests
    do
    {
        title();

        gotoxy(15,8);printf("1. Create New Account\n");
        gotoxy(15,10);printf("2. Cash Deposit");
        gotoxy(15,12);printf("3. Cash Withdrawl");
        gotoxy(15,14);printf("4. Fund Transfer");
        gotoxy(15,16);printf("5. Account information");
        gotoxy(45,8);printf("6. Transaction information");
        gotoxy(45,10); printf("7. Log out");
        gotoxy(45,12);printf("8. Exit");


        gotoxy(1,17); for(i=0;i<78;i++) printf("_");
        gotoxy(23,19);printf("Press a choice between the range [1-8] ");

        switch(getch()-48)
        {
        case 1:

            add_ac();


        break;
        case 2:


            deposit();


        break;
        case 3:

            withdraw();

        break;

        case 4:

            fund_transfer();
        break;
        case 5:
            ac_info();

        break;
        case 6:
            transaction();

        break;


        case 7:
        title();
        gotoxy(15,10); printf("Are you sure you want to Log out? <Y/N> : ");
        ex=getche();
        if (ex=='Y'||ex=='y')
        {
            //if user wants to log out all user log information are stored in LOG.DAT and the function staff() called again i.e. log in screen begins again
            _strtime(etime);
            fp=fopen("LOG.DAT","a");
            fprintf(fp,"%s %s %s %s\n",user.uid,date,stime,etime);
            fclose(fp);
            staff();
        }


        break;


        case 8:

        title();
        gotoxy(15,10); printf("Are you sure you want to exit? <Y/N> : ");
        ex=getche();
        if (ex=='Y'||ex=='y')
        {
            //if user wants to exit, all user log information are stored in LOG.DAT and the program is terminated

            _strtime(etime);
            fp=fopen("LOG.DAT","a");
            fprintf(fp,"%s %s %s %s\n",user.uid,date,stime,etime);
            fclose(fp);
            exit(0);
        }


        break;

        default://when entered characted is not between 1-8
        title();
        gotoxy(10,10); printf("Your input is out of range! Enter a choice between 1 to 8!");
        gotoxy(15,12); printf("Press any key to return to main menu...");
        getch();

    }

 }while(1);//infinite loop to return to main menu after execution of any function


//return 0;
 }



void add_ac()
{
     struct account ac;//structure variable ac created
     char acn[8],curr[35],ch;
     int i;
     float irate;

     fp=fopen("ACCOUNT.DAT","r");
     if(fp==NULL) strcpy(ac.ac_no,"AC00001");//if "ACCOUNT.DAT" does not exist i.e. there are no records at all then A/C no. is taken AC00001 for 1st rec
     else //otherwise a/c no of last record is accessed and increased by unit value which becomes the new a/c no.
     {
        while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF);//note the while statement is terminated without any statement inside it. This helps in geting the last rec. of the data file
        increase(ac.ac_no);
     }

     fclose(fp);

     title();
     gotoxy(8,8); printf("PERSONAL DETAILS");
     gotoxy(7,9); for(i=0;i<18;i++) printf("%c",205);
     gotoxy(10,11); printf("Full name        :    "); scanf("%s",ac.fname); scanf("%s",ac.lname);
     gotoxy(10,13); printf("Gender <M/F>     :    "); scanf(" %c",&ac.sex);
        int temp1,temp2;
     do
     {
        gotoxy(10,15); printf("DOB (dd/mm/yyyy) :    "); scanf(" %s",ac.dob);
        temp1=(ac.dob[6]-48)*1000+(ac.dob[7]-48)*100+(ac.dob[8]-48)*10+(ac.dob[9]-48);
        temp2=2000+(date[6]-48)*10+(date[7]-48);
        if(date_check(ac.dob)==0||temp1>temp2)//checks if dob format is correct, on invalid format screen is partially cleared, beep tone is produced and asked to re-enter date
        {
            printf("\a");
            cls(10,15,60,15);

        }
     }while(date_check(ac.dob)==0||temp1>temp2);//asks date unless format is correct

     _strdate(date);
     date_input(ac.dob);//to change dd/mm/yyyy format to mm/dd/yy format to store in file
     gotoxy(10,17); printf("Address          :    "); scanf(" %[^\n]s",ac.address);
     for(i=0;i<strlen(ac.address);i++)//User may enter a space key for address (eg. New Baneswor). bt on reading formatted data from file space is taken as terminating char (eg. "New" and "Baneswor" are taken as separate variables. To remove this error, spaces entered by user is replace by '+'. Now "New+Baneswor is single string
        if (ac.address[i]==32) ac.address[i]='+';
        int err;
    do
    {
     gotoxy(10,19); printf("Contact number   :    "); scanf(" %s",ac.contact);
     err=0;
        for(i=0;i<strlen(ac.contact);i++)
        if(!((ac.contact[i]>='0'&&ac.contact[i]<='9'||ac.contact[i]=='-'||ac.contact[i]=='+')&&strlen(ac.contact)>=6)) err++;
    if (err!=0) {printf("\a"); cls(10,19,70,19);}
    } while(err!=0);
     title();
     gotoxy(8,8); printf("ACCOUNT DETAILS");
     gotoxy(7,9); for(i=0;i<17;i++) printf("%c",205);
     gotoxy(10,11); printf("A/C number                     :   %s",ac.ac_no);
     int flag;
     do {
     gotoxy(10,13); printf("A/C type <S/C>                 :   ");  scanf(" %c",&ac.ac_type);
     flag=0;
     cls(45,13,78,13); //clears screen partially to display full account type. Eg. when user enters 's', "Saving Account" is displayed
     if (ac.ac_type=='S'||ac.ac_type=='s')
     {
         irate=8; //interest rate 8% for saving a/c
         gotoxy(45,13); printf("Saving Account");
     }
     else if (ac.ac_type=='C'||ac.ac_type=='c')
      {
         irate=4; //interest rate 4% for current saving
         gotoxy(45,13); printf("Current Saving");
     }
     else
     {
         printf("\a");
         flag=1;//note that flag was initially zero. on error, its turned to 1
     }

     } while(flag==1);//for repeated asking of a/c type unless user enters correct input

     date_output(date);
     gotoxy(10,15); printf("Account Opened Date            :   %s",date);
     _strdate(date);
     strcpy(ac.u_date,date);//copies current date to last updated date
     gotoxy(10,17); printf("Interest rate                  :   %.2f%c per annum", irate,37);
     do
     {
        gotoxy(10,19); printf("Opening Balance (in NRs.)      :   "); scanf("%f",&ac.c_bal);
        if (ac.c_bal<0) { printf("\a"); cls(10,19,70,19);}
     }while(ac.c_bal<0);
     ac.interest=0;
     ac.t_bal=ac.c_bal+ac.interest;

    title();
    gotoxy(3,9); printf("Full name      : %s %s",ac.fname,ac.lname);
    gotoxy(3,11); printf("Gender <M/F>   : %c",ac.sex);
    gotoxy(3,13); printf("DOB (mm/dd/yy) : %s",ac.dob);
    gotoxy(3,15); printf("Address        : ");
    for(i=0;i<strlen(ac.address);i++)//In order to display address, '+' is replaced by space
            if (ac.address[i]=='+') putchar(32);
            else putchar(ac.address[i]);

    gotoxy(3,17); printf("Contact number : %s",ac.contact);

    gotoxy(43,9); printf("A/C number      : %s",ac.ac_no);
    gotoxy(43,11); printf("A/C type        : ");
    if (ac.ac_type=='S'||ac.ac_type=='s') printf("Saving Account");
    if (ac.ac_type=='C'||ac.ac_type=='c') printf("Current Saving");

    gotoxy(43,13); printf("Current Date    : %s",date);
    gotoxy(43,15); printf("Interest rate   : %.2f%c per annum", irate,37);
    currency(curr,ac.c_bal);
    gotoxy(43,17); printf("Opening Balance : %s",curr);
    gotoxy(2,19); for(i=0;i<75;i++) printf("%c",196);

    gotoxy(15,21); printf("Are the informations above all correct? <Y/N> ");
    ch=getche();

    if (ch=='Y'||ch=='y')//On confirmation, new a/c (in account.dat) + transaction showing "A/C Opened" is added (in transaction.dat)
    {
        fp=fopen("ACCOUNT.DAT","a");
        fp1=fopen("TRANSACTION.DAT","a");
        _strtime(ttime);
        fprintf(fp1,"%s %s %s %s %.2f %s\n",ac.ac_no,"A/C+Opened",date,ttime,ac.c_bal,user.name);
        fprintf(fp,"%s %s %s %s %s %s %c %s %c %.2f %.2f %.2f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,ac.sex,ac.u_date,ac.ac_type,ac.c_bal,ac.interest,ac.t_bal);
        fclose(fp);
        fclose(fp1);
        title();
        gotoxy(20,10); printf("Record Added Successfully!");
        getch();
    }



}

void uptodate()
{
    struct account ac;
    int i,no_of_yr,no_of_month,no_of_days,n1,n2;
    float r;
    fp=fopen("ACCOUNT.DAT","r");

    if (fp!=NULL)//performs every thing only when file exists i.e. only wen pointer is not null
    {
        fp1=fopen("TEMP.DAT","w");
        i=0;
        while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
        {
        //extracting no of days, months and yr of system date
        no_of_yr=(date[6]-48)*10+(date[7]-48);
        no_of_month=(date[0]-48)*10+(date[1]-48);
        no_of_days=(date[3]-48)*10+(date[4]-48);

        n1=no_of_yr*365+no_of_month*30+no_of_days;//n1 is no. of days elasped

        //extracting no of days, months and yr of date stored in ACCOUNT.DAT
        no_of_yr=(ac.u_date[6]-48)*10+(ac.u_date[7]-48);
        no_of_month=(ac.u_date[0]-48)*10+(ac.u_date[1]-48);
        no_of_days=(ac.u_date[3]-48)*10+(ac.u_date[4]-48);
        n2=no_of_yr*365+no_of_month*30+no_of_days;//n2 is no. of days elasped on last updated date

        if (ac.ac_type=='S'||ac.ac_type=='s') r=8.0/365; else r=4.0/365;

        ac.t_bal=ac.c_bal*pow((1+r/100),n1-n2);//calculation of compound interest
        ac.interest+=ac.t_bal-ac.c_bal;//calculation and addition of interest
        ac.t_bal=ac.c_bal+ac.interest;//calculation of total balance
        strcpy(ac.u_date,date);
        fprintf(fp1,"%s %s %s %s %s %s %c %s %c %.2f %.2f %.2f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,ac.sex,ac.u_date,ac.ac_type,ac.c_bal,ac.interest,ac.t_bal);

        }
        fclose(fp);
        fclose(fp1);
        system("del ACCOUNT.DAT");
        system("ren TEMP.DAT ACCOUNT.DAT");
    }


}

void deposit()
{
    title();
    struct account ac;
    char acn[10],curr[35],ch,csh[80],temp[80],nam[35];
    int c=0;
    float amt;

    gotoxy(5,10); printf("Deposit to A/C number            : "); scanf("%s",acn);
    strcpy(acn,strupr(acn)); //changing a/c no. to uppercase
    fp=fopen("ACCOUNT.DAT","r");
    while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
        if(strcmp(acn,ac.ac_no)==0) { c++; strcpy(nam,ac.fname); strcat(nam," "); strcat(nam,ac.lname); } //variable c counts if the given a/c no exist in data file or not. also if available, the full name is extracted

    fclose(fp);

    if(c==0)//c=0 means no given a/c no. in data file
    {
        title();
        gotoxy(20,12); printf("Given A/C number does not exits!");
        getch();
        return;
    }

    gotoxy(50,10); printf("[ %s ]",nam);
    gotoxy(5,12); printf("Amount to be Deposited (in NRs.) : "); scanf("%f",&amt);
    title();
    gotoxy(30,10); printf("Confirm Transaction");
    currency(curr,amt);
    gotoxy(3,12); printf("%s to be deposited in A/C number : %s [ %s ]",curr,acn,nam);

    num2word((double)amt,csh);
                strcpy(temp,"[In words : ");
                strcat(temp,csh);
                strcat(temp,"]");
    gotoxy(40-strlen(temp)/2,14); puts(temp);

    gotoxy(8,17);printf("Are you sure you want to perform this tranasction? <Y/N>");
    ch=getche();
    if (ch=='Y'||ch=='y')
    {
        fp=fopen("ACCOUNT.DAT","r");
        fp1=fopen("TEMP.DAT","a");
        while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
        {
            if (strcmp(ac.ac_no,acn)==0) ac.c_bal+=amt;//balance is increased
            ac.t_bal=ac.c_bal+ac.interest;
            fprintf(fp1,"%s %s %s %s %s %s %c %s %c %.2f %.2f %.2f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,ac.sex,ac.u_date,ac.ac_type,ac.c_bal,ac.interest,ac.t_bal);
        }
        fclose(fp1);
        fclose(fp);
        system("del ACCOUNT.DAT");
        system("ren TEMP.DAT ACCOUNT.DAT");

        fp=fopen("TRANSACTION.DAT","a");//transaction is added
        _strtime(ttime);
        fprintf(fp,"%s %s %s %s %.2f %s\n",acn,"Cash+Deposited",date,ttime,amt,user.name);
        fclose(fp);
        title();
        gotoxy(20,12);printf("Transaction completed successfully!");
        getch();


    }



}

void withdraw()//exactly similar to deposit. only difference is amount is subtracted.
{
    title();
    struct account ac;
    char acn[10],ch,curr[35],csh[80],temp[80], nam[50];
    int c=0;
    float amt;

    gotoxy(5,10); printf("Withdraw from A/C number          : "); scanf("%s",acn);
    strcpy(acn,strupr(acn));
    fp=fopen("ACCOUNT.DAT","r");
    while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
        if(strcmp(acn,ac.ac_no)==0) { c++; strcpy(nam,ac.fname); strcat(nam," "); strcat(nam,ac.lname); }
    fclose(fp);

    if(c==0)
    {
        title();
        gotoxy(20,12); printf("Given A/C number does not exits!");
        getch();
        return;
    }

    gotoxy(50,10); printf("[ %s ]",nam);
    gotoxy(5,12); printf("Amount to be Withdrawn (in NRs.)  : "); scanf("%f",&amt);



    fp=fopen("ACCOUNT.DAT","r");

            c=0;
            while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
            {

                if (strcmp(ac.ac_no,acn)==0&&ac.t_bal<amt)// when given amount is higher than bank balance
                {
                    title();
                    gotoxy(20,12); printf("Sorry, the current balance is Rs. %.2f only!",ac.t_bal);
                    gotoxy(25,14); printf("Transaction NOT completed!");
                    c=1;
                    getch();
                    return;
                }

            }
            fclose(fp);


                title();
    gotoxy(30,10); printf("Confirm Transaction");
    currency(curr,amt);
    gotoxy(3,12); printf("%s to be Withdrawn from A/C number : %s [%s]",curr,acn,nam);
    num2word((double)amt,csh);
                strcpy(temp,"[In words : ");
                strcat(temp,csh);
                strcat(temp,"]");
    gotoxy(40-strlen(temp)/2,14); puts(temp);
    gotoxy(8,17);printf("Are you sure you want to perform this tranasction? <Y/N>");
    ch=getche();


            if (ch=='Y'||ch=='y')
            {
                fp=fopen("ACCOUNT.DAT","r");
                fp1=fopen("TEMP.DAT","w");
                c=0;
                while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
                {
                    if (strcmp(ac.ac_no,acn)==0) ac.c_bal-=amt;
                    if (ac.c_bal<0) { ac.interest+=ac.c_bal; ac.c_bal=0; }
                    ac.t_bal=ac.c_bal+ac.interest;

                    fprintf(fp1,"%s %s %s %s %s %s %c %s %c %.2f %.2f %.2f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,ac.sex,ac.u_date,ac.ac_type,ac.c_bal,ac.interest,ac.t_bal);
                }
            fclose(fp1);
            fclose(fp);
            system("del ACCOUNT.DAT");
            system("ren TEMP.DAT ACCOUNT.DAT");





        fp=fopen("TRANSACTION.DAT","a");
        _strtime(ttime);
        fprintf(fp,"%s %s %s %s %.2f %s\n",acn,"Cash+Withdrawn",date,ttime,amt,user.name);
        fclose(fp);
        title();
        gotoxy(20,12);printf("Transaction completed successfully!");

        getch();




    }



}


void fund_transfer()
{
    char f_acn[8],t_acn[8],ch,curr[35],rem[25],csh[80]={0},temp[80]={0},fnam[35],tnam[35];
    struct account ac;
    float amt;
    int c=0;

    title();

        gotoxy(3,8); printf("Transferred from (A/C no. )        : "); scanf("%s",f_acn);

        strcpy(f_acn,strupr(f_acn));
        fp=fopen("ACCOUNT.DAT","r");
        c=0;
        while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
            if(strcmp(f_acn,ac.ac_no)==0) { c++; strcpy(fnam,ac.fname); strcat(fnam," "); strcat(fnam,ac.lname); }
        fclose(fp);

    if (c==0)
    {
        title();
        gotoxy(20,12); printf("Given A/C number does not exits!");
        getch();
        return;
    }

        gotoxy(50,8); printf("[ %s ]",fnam);
        gotoxy(3,10); printf("Transferred to  (A/C no. )         : "); scanf("%s",t_acn);

        strcpy(t_acn,strupr(t_acn));
        fp=fopen("ACCOUNT.DAT","r");
        c=0;
        while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
        if(strcmp(t_acn,ac.ac_no)==0) { c++; strcpy(tnam,ac.fname); strcat(tnam," "); strcat(tnam,ac.lname); }
        fclose(fp);

        if (c==0)
        {
            title();
            gotoxy(20,12); printf("Given A/C number does not exits!");
            getch();
            return;
        }


            gotoxy(50,10); printf("[ %s ]",tnam);
            gotoxy(3,12); printf("Amount to be transferred (in NRs.) : "); scanf("%f",&amt);




            fp=fopen("ACCOUNT.DAT","r");

            c=0;
            while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
            {
                if (strcmp(ac.ac_no,f_acn)==0)
                {
                if (ac.t_bal<amt)
                {
                    title();
                    gotoxy(15,12); printf("Sorry, the current balance is Rs. %.2f only!",ac.t_bal);
                    gotoxy(28,14); printf("Transaction NOT completed!");
                    getch();
                    return;
                }
                }
            }
            fclose(fp);



                title();
                gotoxy(30,8); printf("Confirm Transaction");
                currency(curr,amt);
                gotoxy(25,10); printf("%s to be Transfered",curr);
                num2word((double)amt,csh);
                strcpy(temp,"[In words : ");
                strcat(temp,csh);
                strcat(temp,"]");
                gotoxy(40-strlen(temp)/2,12); puts(temp);
                gotoxy(18,14); printf("FROM A/C number %s [ %s ]",f_acn,fnam);
                gotoxy(18,16); printf("TO   A/C number %s [ %s ]",t_acn,tnam);
                gotoxy(12,19);printf("Are you sure you want to perform this tranasction? <Y/N>");
                ch=getche();


            if (ch=='Y'||ch=='y')
            {
                fp=fopen("ACCOUNT.DAT","r");
                fp1=fopen("TEMP.DAT","w");
                c=0;
                while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
                {
                    if (strcmp(ac.ac_no,f_acn)==0) ac.c_bal-=amt;
                    if (ac.c_bal<0) { ac.interest+=ac.c_bal; ac.c_bal=0; }
                    ac.t_bal=ac.c_bal+ac.interest;

                    fprintf(fp1,"%s %s %s %s %s %s %c %s %c %.2f %.2f %.2f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,ac.sex,ac.u_date,ac.ac_type,ac.c_bal,ac.interest,ac.t_bal);
                }
            fclose(fp1);
            fclose(fp);
            system("del ACCOUNT.DAT");
            system("ren TEMP.DAT ACCOUNT.DAT");

            fp=fopen("ACCOUNT.DAT","r");
            fp1=fopen("TEMP.DAT","w");
            c=0;
            while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
            {
                if (strcmp(ac.ac_no,t_acn)==0) ac.c_bal+=amt;
                ac.t_bal=ac.c_bal+ac.interest;

                fprintf(fp1,"%s %s %s %s %s %s %c %s %c %.2f %.2f %.2f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,ac.sex,ac.u_date,ac.ac_type,ac.c_bal,ac.interest,ac.t_bal);
            }
            fclose(fp1);
            fclose(fp);
            system("del ACCOUNT.DAT");
            system("ren TEMP.DAT ACCOUNT.DAT");


            fp=fopen("TRANSACTION.DAT","a");
            _strtime(ttime);
            strcpy(rem,"Transfered+to+");
            strcat(rem,t_acn);
            fprintf(fp,"%s %s %s %s %.2f %s\n",f_acn,rem,date,ttime,amt,user.name);
            strcpy(rem,"Received+from+");
            strcat(rem,f_acn);
            fprintf(fp,"%s %s %s %s %.2f %s\n",t_acn,rem,date,ttime,amt,user.name);
            fclose(fp);
            title();
            gotoxy(20,12);printf("Transaction completed successfully!");
            getch();




            }








}


void ac_info()
{

    int i;

    char buffer[30]={0},curr[35],curr1[35],curr2[35];
    struct account ac,srh;//structure variable srh stores the matched data from data file
    float irate;
    char c,acn[8];

         	int pos = 0,n=0,m=0,cnt;

    title();//sub menu to search records
    gotoxy(27,8);printf("1. Search by A/C number");
    gotoxy(27,10);printf("2. Search by Name");
    gotoxy(27,12);printf("3. Return to main menu");
    gotoxy(25,16); printf("Press a choice between 1-3 ");
    c=getche();
    switch(c-48)
    {
        case 1:

        title();
        gotoxy(5,8); printf("Enter A/C number : ");
        scanf("%s",acn);
        strcpy(acn,strupr(acn));
        fp=fopen("ACCOUNT.DAT","r");
        cnt = 0;

           		while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
           		{
           		    if (strcmp(acn,ac.ac_no)==0) { srh=ac; cnt++; }// if a/c no matches, srh stores all values of ac
           		}

        if (cnt==0)
        {
            title();
            gotoxy(20,12); printf("Given A/C number does not exits!");
            getch();
            return;
        }

        ac=srh;
    title();
    gotoxy(3,9); printf("Full name      : %s %s",ac.fname,ac.lname);
    gotoxy(3,11); printf("Gender <M/F>   : %c",ac.sex);
    gotoxy(3,13); printf("DOB (mm/dd/yy) : %s",ac.dob);
    gotoxy(3,15); printf("Address        : ");
    for(i=0;i<strlen(ac.address);i++)
            if (ac.address[i]=='+') putchar(32);
            else putchar(ac.address[i]);

    gotoxy(3,17); printf("Contact number : %s",ac.contact);

    gotoxy(43,9); printf("A/C number      : %s",ac.ac_no);
    gotoxy(43,11); printf("A/C type <S/F>  : ");
    if (ac.ac_type=='S'||ac.ac_type=='s') { printf("Saving Account"); irate=8.0; }
    if (ac.ac_type=='C'||ac.ac_type=='c') { printf("Current Saving"); irate=4.0;  }


    gotoxy(43,13); printf("Interest rate   : %.2f%c per annum", irate,37);
    currency(curr,ac.c_bal);
    gotoxy(43,15); printf("Current Balance : %s",curr);
    currency(curr1,ac.interest);
    gotoxy(43,17); printf("Interset        : %s",curr1);
    currency(curr2,ac.t_bal);
    gotoxy(43,19); printf("Total Balance   : %s",curr2);

    gotoxy(2,21); for(i=0;i<75;i++) printf("%c",196);
    gotoxy(5,22); printf("Press ENTER to search again or ANY OTHER KEY to return to main menu");
    c=getch();
    if(c==13) ac_info();//13 ascii code of enter
    else return;




        break;

        case 2:


         	title();
         	gotoxy(5,6); printf("Enter first name : ");

           	do
            	{

            	    gotoxy(2,7); for(i=0;i<75;i++) printf("%c",196);
                    gotoxy(2,20); for(i=0;i<75;i++) printf("%c",196);
                    gotoxy(15,21); printf("Press ENTER to view detailed information of FIRST record");
                    gotoxy(18,22); printf(" or press ESCAPE to return to main menu");



            	    gotoxy(25+n,6);
                    c = getch();
            		if( isprint(c) )
            		{
            			buffer[ pos++ ] = c;
            			printf("%c", c);
            			n++;
            		}
            		else if( c == 8 && pos )
            		{
            			buffer[ pos-- ] = '\0';
            			printf("%s", "\b \b");
            			n--;
           		}

       cls(3,10,75,11+m);
       m=0;


                        gotoxy(3,8); printf("A/C no.");
           		        gotoxy(13,8); printf("Full name");
           		        gotoxy(43,8); printf("Contact no.");
                        gotoxy(60,8); printf("Net Balance");
                        gotoxy(2,9); for(i=0;i<75;i++) printf("%c",196);



fp=fopen("ACCOUNT.DAT","r");

           		while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
           		{
           		    cnt=0;
           		    for(i=0;i<strlen(buffer);i++)
           		    {
           		        if(buffer[i]>='a'&&buffer[i]<='z') buffer[i]=buffer[i]-32;
           		        if(ac.fname[i]>='a'&&ac.fname[i]<='z') ac.fname[i]=ac.fname[i]-32;
           		    if(buffer[i]!=ac.fname[i]) cnt++;
           		    }



           		    if(cnt==0)
           		   {

           		        if(m==0) srh=ac;

                        if(m<=9)
                        {
           		        gotoxy(3,10+m); printf("%s",ac.ac_no);
           		        gotoxy(13,10+m); printf("%s %s",ac.fname,ac.lname);
           		        gotoxy(43,10+m); printf("%s",ac.contact);
           		        currency(curr,ac.t_bal);
                        gotoxy(55,10+m); printf("%20s",curr);
                        m++;
                        }

           		    }

           		    }





fclose(fp);





           		}while( c != 13&&c!=27 );

if (c==13)
{
    ac=srh;
    title();
    gotoxy(3,9); printf("Full name      : %s %s",ac.fname,ac.lname);
    gotoxy(3,11); printf("Gender <M/F>   : %c",ac.sex);
    gotoxy(3,13); printf("DOB (mm/dd/yy) : %s",ac.dob);
    gotoxy(3,15); printf("Address        : ");
    for(i=0;i<strlen(ac.address);i++)
            if (ac.address[i]=='+') putchar(32);
            else putchar(ac.address[i]);

    gotoxy(3,17); printf("Contact number : %s",ac.contact);

    gotoxy(43,9); printf("A/C number      : %s",ac.ac_no);
    gotoxy(43,11); printf("A/C type <S/F>  : ");
    if (ac.ac_type=='S'||ac.ac_type=='s') { printf("Saving Account"); irate=8.0; }
    if (ac.ac_type=='C'||ac.ac_type=='c') { printf("Current Saving"); irate=4.0;  }


    gotoxy(43,13); printf("Interest rate   : %.2f%c per annum", irate,37);
    currency(curr,ac.c_bal);
    gotoxy(43,15); printf("Current Balance : %s",curr);
    currency(curr1,ac.interest);
    gotoxy(43,17); printf("Interset        : %s",curr1);
    currency(curr2,ac.t_bal);
    gotoxy(43,19); printf("Total Balance   : %s",curr2);

    gotoxy(2,21); for(i=0;i<75;i++) printf("%c",196);
    gotoxy(5,22); printf("Press ENTER to search again or ANY OTHER KEY to return to main menu");
    c=getch();
    if(c==13) ac_info();
    else return;


}

break;
case 3:
    return;
break;
default:
title();
        gotoxy(10,10); printf("Your input is out of range! Enter a choice between 1 to 8!");
        gotoxy(15,12); printf("Press any key to return to main menu...");
        getch();
        ac_info();



    }




}



void transaction()
{
    char acn[8],mon[10],ch,camt[25],temp[40];
    int c,i,j,l,n,x,pg=1;
    int nr;
    nr=num_of_rec("TRANSACTION.DAT",6);

    struct trans t, *selected;
    selected=(struct trans *)malloc(sizeof(struct trans)*nr);

    struct account ac,sac;

    title();
    gotoxy(8,8); printf("A/C number         : "); scanf("%s",acn);
    strcpy(acn,strupr(acn));
    fp=fopen("ACCOUNT.DAT","r");
    c=0;
    while(fscanf(fp,"%s %s %s %s %s %s %c %s %c %f %f %f\n",ac.ac_no,ac.fname,ac.lname,ac.dob,ac.address,ac.contact,&ac.sex,ac.u_date,&ac.ac_type,&ac.c_bal,&ac.interest,&ac.t_bal)!=EOF)
    if(strcmp(acn,ac.ac_no)==0)
    {
        c++;
        sac=ac;

    }

    fclose(fp);

    if (c==0)
    {
        title();
        gotoxy(20,12); printf("Given A/C number does not exits!");
        getch();
    }
    else
    {



        fp=fopen("TRANSACTION.DAT","r");
        i=0;
        while(fscanf(fp,"%s %s %s %s %f %s\n",t.ac_no,t.ac_t,t._date,t._ttime,&t.amt,t.usr)!=EOF)
                if(strcmp(acn,t.ac_no)==0) selected[i++]=t;
        l=i;
        fclose(fp);

        strcpy(selected[l].ac_no,t.ac_no);
        strcpy(selected[l].ac_t,"Interest");
        strcpy(selected[l]._date,date);
        _strtime(ttime);
        strcpy(selected[l]._ttime,ttime);
        selected[l].amt=sac.interest;
        l++;
        strcpy(selected[l].ac_no,t.ac_no);
        strcpy(selected[l].ac_t,"Closing balance");
        strcpy(selected[l]._date,date);
        _strtime(ttime);
        strcpy(selected[l]._ttime,ttime);
        selected[l].amt=sac.c_bal+sac.interest;
        l++;
        n=0; c=0;
        float dr=0,cr=0;
        do
        {
        title();

        gotoxy(2,6);puts("SN");
        gotoxy(6,6);puts("     Details");
        gotoxy(28,6); puts("Date");
        gotoxy(44,6); puts("Time");
        gotoxy(50,6);puts("   Dr. (NRs.)");
        gotoxy(65,6);puts("   Cr. (NRs.)");
        gotoxy(1,7); for(i=1;i<79;i++) printf("%c",196);
        gotoxy(1,21); for(i=1;i<79;i++) printf("%c",196);
        if(n>l) {n=0; pg=1;}
        i=n;

        gotoxy(2,22); printf("Page : %d out of %d",pg,(int)l/10+1);
        if (l>9)
            if (pg!=(int)l/10+1) { gotoxy(25,22); printf("Press SPACE BAR to view next page");}
            else { gotoxy(25,22); printf("Press SPACE BAR to view first page");}
        gotoxy(2,20); printf("A/C holder : %s %s",sac.fname,sac.lname);
        currency(camt,sac.t_bal);
        strcpy(temp,"Bank Balance : ");
        strcat(temp,camt);
        gotoxy(78-strlen(temp),20); printf("%s",temp);


        for(j=0;j<10;j++)
        {

        gotoxy(2,8+j); printf("%d.",i+1);
        for(x=0;x<strlen(selected[i].ac_t);x++) if(selected[i].ac_t[x]=='+') selected[i].ac_t[x]=32;
        gotoxy(6,8+j); puts(selected[i].ac_t);
        if (c==0) date_output(selected[i]._date);
        gotoxy(28,8+j); puts(selected[i]._date);
        selected[i]._ttime[5]='\0';
        gotoxy(44,8+j); printf("%s",selected[i]._ttime);
        if(selected[i].ac_t[0]=='T')
        {
            gotoxy(65,8+j);
            printf("%13.2f",selected[i].amt);
            cr+=selected[i].amt;
        }
        else if (selected[i].ac_t[0]=='C'&&(selected[i].ac_t[5]=='W'||selected[i].ac_t[1]=='l'))
            {
            gotoxy(65,8+j);
            printf("%13.2f",selected[i].amt);
            cr+=selected[i].amt;
            }
            else
            {
                gotoxy(50,8+j);
                printf("%13.2f",selected[i].amt);
                dr+=selected[i].amt;
            }
            i++;
            if(i>=l) break;


        }


        n+=10;

       if (i>=l)
       {
        gotoxy(1,9+j); for(x=1;x<79;x++) printf("%c",196);
        gotoxy(40,10+j); printf("TOTAL");
        gotoxy(50,10+j); printf("%13.2f",dr);
        gotoxy(65,10+j); printf("%13.2f",cr);
        dr=cr=0;
        gotoxy(1,11+j); for(x=1;x<79;x++) printf("%c",196);
        c++;
    }
        ch=getche();
        if (ch==32) pg++;

        } while(ch==32);











    }





}





//----------------------------------------------------------------------------------------------



void admin()
{
    char uname[30], pass[30]={0};

    int c=0,cnt=0;
    do
    {
    c=0;
    system("cls");
    gotoxy(7,5);printf("Only THREE attempts shall be allowed to enter username and password.");
    rectangle(10,8,70,15);
    gotoxy(23,10); printf("Enter User name : "); scanf("%s",uname);
    char pass[30]={0};
    gotoxy(23,12); printf("Password        : "); _password(pass);


    strcpy(uname,strupr(uname)); //Changes string uname into uppercase
    strcpy(pass,strupr(pass));

    cnt++;//This variable counts the number of times the password is asked. Note that if cnt==3 then the program terminates after displaying error message
    if (cnt==3)
    {
        title();
        gotoxy(25,8); printf("Invalid User name or Password!\a");
        gotoxy(22,11);printf("Press any key to exit the program...");
        getch();


        exit(0); //exits the program
    }
    if(strcmp(uname,"ADMIN")==0&&strcmp(pass,"IOE")==0) c=1;//if user name and passpord matches, the value of c is changed from 0 to 1. The purpose of changing value of c is seen @line 77 where the password is asked again if c!=0 i.e. if given password is invalid
    else
    {
        title();
        gotoxy(25,10); printf("Invalid User name or Password!\a");
        getch();

    }

    } while(c!=1);

do
    {
    title();

    int ch,i;
    char ex,key;
    gotoxy(30,8);printf("1. Add User");
    gotoxy(30,10);printf("2. Delete User");
    gotoxy(30,12);printf("3. Edit User name / Password");
    gotoxy(30,14);printf("4. View User Log");
    gotoxy(30,16);printf("5. Exit");
    gotoxy(1,17); for(i=0;i<78;i++) printf("_");
    gotoxy(23,19);printf(" Press a number between the range [1 -5]  ");
    key=getche();//Reads a character entered by user andstroes in char variable key
    ch=key-48;//changes char key into integer ch eg. '1'(ascii value 49)--->49-48=1




    switch(ch)
    {
        case 1:

        add_user();


        break;
        case 2:


        del_user();


        break;
        case 3:

        edit_user();


        break;

        case 4:

        view_log();
        break;

        case 5:
        title();
        gotoxy(15,10); printf("Are you sure you want to exit? <Y/N> : ");
        ex=getche();
        if (ex=='Y'||ex=='y') exit(0);


        break;

        default:
        title();
        gotoxy(10,10); printf("Your input is out of range! Enter a choice between 1 to 5!");
        gotoxy(15,12); printf("Press ENTER to return to main menu...");
        getch();

    }

    } while(1);//goes to main menu repeatedly unless user's choice is exit
    return;
}





void add_user()
{


        int err1=0,c=0;
        char passwrd1[30]={0};
        char passwrd2[30]={0};
        char nam[30],pass[30];
        do{
            title();
            err1=0;
            gotoxy(25,8);printf("User Name        : ");
            scanf("%s",user.name);
            fp=fopen("USER.DAT","r");//opens the datafile USER.DAT to check if the user name already exits or not


        c=0;
                while(fscanf(fp,"%s %s %s\n",user.uid,nam,pass)!=EOF)
                {
                    strcpy(nam,strupr(nam));
                    strcpy(user.name,strupr(user.name));
                    if(strcmp(nam,user.name)==0) c++;//if given username and the username of datafile matches, c is increased by 1
                }

                fclose(fp);
                if(c!=0)//it is neccessary for c to be zero to avoid duplicate user name
                {
                    gotoxy(10,10);
                    printf("User name already exists! Please enter a new user name.\a");
                    getch();
                    err1++;//this is an error flag. its signigicance is observed @line 216
                    continue;// skips all the commands below and go for next loop of do..while @line 174
                }




            gotoxy(25,10);printf("Password         : ");
            _password(passwrd1);
            strcpy(user.password,passwrd1);
            gotoxy(25,12);printf("Confirm Password : ");
            _password(passwrd2);
            if (strcmp(user.password,passwrd2)!=0)//checking if password and confirm password match
            {
                title();
                gotoxy(10,10);
                printf("Password and confirm password does not match!\a");
                getch();
                err1++;
            }
        }while(err1!=0);

        fp=fopen("USER.DAT","r");//data file again opened to read the last user id

        char id[4];

        if (fp==NULL)  strcpy(user.uid,"U01");//if USER.DAT does not exists userid is set to first i.e. U01
        else
        {
                while(fscanf(fp,"%s %s %s\n",user.uid,nam,pass)!=EOF);//last user id is read
                increase(user.uid);//userid is incread by 1. eg. U09-->U10. note that increase() is our user defined function



        }
        fclose(fp);

        fp=fopen("USER.DAT","a");//data file open to append (add) record


        fprintf(fp,"%s %s %s\n",user.uid,user.name,user.password); //record written in datafile
        fclose(fp);

        title();
        gotoxy(25,10); printf("Record ADDED successfully!");
        getch();

}

void del_user()
{
    char nam[30], pass[30],ch,id[5],passwrd[30]={0};
    int c=0;
    user_log log;
       title();

            gotoxy(25,8);printf("User Name  : ");
            scanf("%s",user.name);
            gotoxy(25,10);printf("Password  : ");
            _password(passwrd);
            strcpy(user.password,passwrd);

        fp=fopen("USER.DAT","r");//opening datafile to read in order to check if the given user name and password combination exists
         while(fscanf(fp,"%s %s %s\n",user.uid,nam,pass)!=EOF)
         {
             strcpy(nam,strupr(nam));
             strcpy(pass,strupr(pass));
             strcpy(user.name,strupr(user.name));
             strcpy(user.password,strupr(user.password));
             if(strcmp(user.name,nam)==0&&strcmp(user.password,pass)==0) c++;
         }

        fclose(fp);
        title();
        if (c==0)//note that c must be 1 if given user name and password exists
        {

            gotoxy(10,10); printf("Cannot find the given combination of USER NAME and PASSWORD!\a");
            getch();
            return;
        }

            gotoxy(15,10); printf("Are you sure you want to DELETE this user? <Y/N> : ");
            ch=getche();
            if(ch=='Y'||ch=='y')
            {
                fp=fopen("USER.DAT","r");
                tfp=fopen("temp.dat","a");//creating a temporary datafile where all the contents of USER.DAT is copied except the one entered by user to delete. Note that @line 292 and 293 we have first deleted our old datafile USER.DAT and renamed the duplicate copy temp.dat into USER.DAT. This concept has been used to delete and edit records of data file
                while(fscanf(fp,"%s %s %s\n",user.uid,nam,pass)!=EOF)
                {
                    strcpy(nam,strupr(nam));
                    strcpy(pass,strupr(pass));
                    if(strcmp(user.name,nam)!=0||strcmp(user.password,pass)!=0)
                       fprintf(tfp,"%s %s %s\n",user.uid,nam,pass);
                    else
                       strcpy(id,user.uid);
                }
                fclose(fp);
                fclose(tfp);
                system("del USER.DAT");
                system("ren temp.dat USER.DAT");

                fp=fopen("LOG.DAT","r");
                tfp=fopen("temp.dat","w");//creating a temporary datafile where all the contents of USER.DAT is copied except the one entered by user to delete. Note that @line 292 and 293 we have first deleted our old datafile USER.DAT and renamed the duplicate copy temp.dat into USER.DAT. This concept has been used to delete and edit records of data file
                while(fscanf(fp,"%s %s %s %s",log.id,log.date,log.stime,log.etime)!=EOF)
                {
                    strupr(log.id);
                    strupr(id);
                    if(strcmp(log.id,id)!=0)
                        fprintf(tfp,"%s %s %s %s\n",log.id,log.date,log.stime,log.etime);
                }
                fclose(fp);
                fclose(tfp);
                system("del LOG.DAT");
                system("ren temp.dat LOG.DAT");


                title();
                gotoxy(25,10); printf("Record DELETED successfully!");
                getch();
            }




}

void edit_user()
{
    char nam[30], pass[30],ch, n_nam[30], n_pass[30]={0},passwrd[30]={0},n_pass1[30]={0};
    int c=0,err=0;
        title();

            gotoxy(25,8);printf("User Name  : ");
            scanf("%s",user.name);
            gotoxy(25,10);printf("Password  : ");
            _password(passwrd);
            strcpy(user.password,passwrd);

        fp=fopen("USER.DAT","r");
         while(fscanf(fp,"%s %s %s\n",user.uid,nam,pass)!=EOF)
         {
             strcpy(nam,strupr(nam));
             strcpy(pass,strupr(pass));
             strcpy(user.name,strupr(user.name));
             strcpy(user.password,strupr(user.password));
             if(strcmp(user.name,nam)==0&&strcmp(user.password,pass)==0) c++;
         }

        fclose(fp);
        title();
        if (c==0)
        {

            gotoxy(10,10); printf("Cannot find the given combination of USER NAME and PASSWORD!\a");
            getch();
        }
        else
        {
           gotoxy(8,10); printf("Are you sure you want to CHANGE user name and/or password? <Y/N> : ");
            ch=getche();
            if(ch=='Y'||ch=='y')
            {
                do
                {
                 title();
                    err=0;
                    gotoxy(25,8);
                    printf("NEW User Name        : ");
                    scanf("%s",n_nam);
                    gotoxy(25,10);
                    printf("NEW Password         : ");
                    _password(n_pass);
                    gotoxy(25,12);
                    printf("Confirm NEW Password : ");
                    _password(n_pass1);

                    if (strcmp(n_pass,n_pass1)!=0)
                    {
                        title();
                        gotoxy(10,10);
                        printf("Password and confirm password does not match!\a");
                        getch();
                        err++;
                    }

                } while(err!=0);

                fp=fopen("USER.DAT","r");
                tfp=fopen("temp.dat","a");
                while(fscanf(fp,"%s %s %s\n",user.uid,nam,pass)!=EOF)
                {
                    strcpy(nam,strupr(nam));
                    strcpy(pass,strupr(pass));
                    if(strcmp(user.name,nam)!=0||strcmp(user.password,pass)!=0)
                        fprintf(tfp,"%s %s %s\n",user.uid,nam,pass);
                    else
                        fprintf(tfp,"%s %s %s\n",user.uid,n_nam,n_pass);
                }
                fclose(fp);
                fclose(tfp);
                system("del USER.DAT");
                system("ren temp.dat USER.DAT");

                title();
                gotoxy(25,10); printf("Record has been EDITED successfully!");
                getch();
            }


        }

}



void view_log()
{
    int nr;
    nr=num_of_rec("LOG.DAT",4);
    user_log *log,*selected,*temp;

    log=(user_log *)malloc(sizeof(user_log)*nr);
    selected=(user_log *)malloc(sizeof(user_log)*nr);
    temp=(user_log *)malloc(sizeof(user_log)*nr);

    int i=0,l,j,c=0,n=0,l1,cnt=0;
    char uid[4],nam[30],pass[30],key,ch;

do {
        i=0;c=0;n=0;cnt=0;
        tfp=fopen("LOG.DAT","r");//note that 2 datafiles LOG.DAT and USER.DAT are opened to store necessary informations in structure variable log[] all informations are availeble on LOG.DAT but to access user name we have to open USER.DAT also. After storing necessary information in structure variable log, there is no need to further open these datafiles

        while(fscanf(tfp,"%s %s %s %s\n",log[i].id,log[i].date,log[i].stime,log[i].etime)!=EOF)
        {

            fp=fopen("USER.DAT","r");
            while(fscanf(fp,"%s %s %s\n",uid,nam,pass)!=EOF)

                if(strcmp(log[i].id,uid)==0) strcpy(log[i].name,nam);


            i++;
            fclose(fp);
        }
        l=i;//thus l is num of rec.s

        fclose(tfp);



    title();
    gotoxy(30,8);printf("1. View by USER NAME");
    gotoxy(30,10);printf("2. View by DATE");
    gotoxy(30,12);printf("3. View ALL User history");
    gotoxy(30,14);printf("4. Return to main menu");
    gotoxy(1,15); for(i=0;i<78;i++) printf("_");
    gotoxy(23,17);printf(" Press a number between the range [1 -4]  ");
    key=getche()-48;
    j=0;
    title();
    switch(key)
    {
        case 1:

            gotoxy(30,10); printf("Enter user name : "); scanf(" %s",nam);
            strcpy(nam,strupr(nam));
            for(i=0;i<l;i++)
            {   strcpy(log[i].name,strupr(log[i].name));
                if(strcmp(log[i].name,nam)==0) selected[j++]=log[i];//selected[] is a structure array variable that stores selected (that are to be displayed) data from log[]
            }
            l1=j;//l1 is number of selected (that are to be displayed) records
        break;
        case 2:

            do
            {
            gotoxy(30,10); printf("Enter Date (dd/mm/yyyy) : "); scanf(" %s",nam);

            if(date_check(nam)==0) { cls(30,10,70,10); printf("\a");}
            }while(date_check(nam)==0);

            date_input(nam);
            for(i=0,j=0;i<l;i++)
                  if(strcmp(log[i].date,nam)==0) selected[j++]=log[i];
            l1=j;
        break;
        case 3:

            for(i=0;i<l;i++)
                  selected[j++]=log[i];
            l1=j;
        break;
        case 4:

            return;

        break;
        default:

        title();
        gotoxy(10,10); printf("Your input is out of range! Enter a choice between 1 to 4!");
        gotoxy(15,12); printf("Press ENTER to return to main menu...");
        getch();
        c=1;
    }


    if(l1==0)//l1==0 means no supporing data available
    {
        title();
        gotoxy(27,12); printf("No related record(s) found!\a");
        getch();
        view_log();
    }



    if(c==0)
    {

        for(i=0,j=l1-1;i<l1;i++,j--)
            temp[i]=selected[j];
        for(i=0;i<l1;i++)
            selected[i]=temp[i];

        do
        {
        title();
            if (l1<12)
            {
                gotoxy(8,21); printf("Press S to toggle Sorting between ascending or descending order.");
            }

            else
            {
            gotoxy(15,21); printf("Press SPACE BAR to view more data");
            }
        gotoxy(5,8); printf("SN\t User Name\tDate\t\tStart time\tEnd Time");
        gotoxy(4,9); for(i=0;i<70;i++) printf("%c",196);
        if(cnt!=0)
            {
                for(i=l1-1;i>=0;i--)
                    temp[l1-i-1]=selected[i];
                for(i=0;i<l1;i++)
                    selected[i]=temp[i];
            }


        if(n>l1) n=0;

        for(i=n,j=0;i<l1;i++,j++)
        {
        gotoxy(5,10+j);printf("%d.",i+1);
        selected[i].stime[5]='\0';
        selected[i].etime[5]='\0';
        if (strlen(selected[i].date)<10)
        {
        date_output(selected[i].date);

        }
        gotoxy(9,10+j); printf("%s\t\t%s\t%s\t\t%s",selected[i].name,selected[i].date,selected[i].stime,selected[i].etime);
        if(i>=n+9) { n=n+10; break;}
        }
        ch=getche();
        if(ch=='S'||ch=='s')cnt=1;
        if(ch==32&&i==l1) n=0;

        } while(ch=='S'||ch=='s'||ch==32);


    }
    else c=0;

    } while(1);

}



//------------------------------------------------------------------------------------------------

void welcome()
{
    int i;
    system("cls");
    rectangle(0,0,80,23);
    gotoxy(27,4); printf("BANK MANAGEMENT SYSTEM");
    gotoxy(25,5); for(i=0;i<27;i++) printf("%c",196);
    gotoxy(25,8); printf("Designed and Programmed by:");
    gotoxy(25,9);for(i=0;i<27;i++) printf("%c",196);
    gotoxy(33,11); printf("Ravi Agrawal");
    gotoxy(33,13); printf("Sagar Sharma");
    gotoxy(33,15); printf("Sawal Maskey");
    gotoxy(24,20);

    printf("Press Any key to continue...");


    getch();

}


void date_input(char date[]) // dd/mm/yyyy ----> mm/dd/yy
{
    char temp[15];

    temp[3]=date[0];
    temp[4]=date[1];
    temp[0]=date[3];
    temp[1]=date[4];
    temp[6]=date[8];
    temp[7]=date[9];
    temp[8]='\0';
    temp[2]=temp[5]='/';

    strcpy(date,temp);
}


void date_output(char date[]) //mm/dd/yy ---> dd MMM, yyyy
{
    struct
    {
        int dd;
        char mm[4];
        int yyyy;
    }_date;

    char temp[15];
    int mm,c,i;
    _date.dd=(date[3]-48)*10+(date[4]-48);

    mm=(date[0]-48)*10+(date[1]-48);
    _date.yyyy=2000+(date[6]-48)*10+(date[7]-48);
switch(mm)
    {
        case 1: strcpy(_date.mm,"Jan"); break;
        case 2: strcpy(_date.mm,"Feb"); break;
        case 3: strcpy(_date.mm,"Mar"); break;
        case 4: strcpy(_date.mm,"Apr"); break;
        case 5: strcpy(_date.mm,"May"); break;
        case 6: strcpy(_date.mm,"Jun"); break;
        case 7: strcpy(_date.mm,"Jul"); break;
        case 8: strcpy(_date.mm,"Aug"); break;
        case 9: strcpy(_date.mm,"Sep"); break;
        case 10: strcpy(_date.mm,"Oct"); break;
        case 11: strcpy(_date.mm,"Nov"); break;
        case 12: strcpy(_date.mm,"Dec"); break;
    }

    temp[0]=(int)(_date.dd/10)+48;
    temp[1]=(int)(_date.dd%10)+48;
    temp[2]=32;
    temp[3]='\0';
    strcat(temp,_date.mm);
    temp[6]=',';
    c=0;
    temp[7]=32;
    for(i=3;i>=0;i--)
    {
        temp[8+c]=(int)(_date.yyyy/pow(10,i))+48;
        c++;
        _date.yyyy%=(int)pow(10,i);
    }
    temp[12]='\0';
    strcpy(date,temp);
    }


int date_check(char _date[]) //_date[] is in format dd/mm/yyyy
{
    int err=0,mm,dd,yyyy;
    if(strlen(_date)!=10) err++;
    if(_date[2]!='/'||_date[5]!='/') err++;
    mm=(_date[3]-48)*10+(_date[4]-48);
    if (mm>12) err++;
    dd=(_date[0]-48)*10+(_date[1]-48);

    yyyy=(_date[6]-48)*1000+(_date[7]-48)*100+(_date[8]-48)*10+(_date[9]-48);

    switch(mm)
    {
        case 1: if (dd>31) err++; break;
        case 2:
            if (dd>28) err++;
            if (yyyy%4==0&&dd==29) err--;
            break;
        case 3: if (dd>31) err++; break;
        case 4: if (dd>30) err++; break;
        case 5: if (dd>31) err++; break;
        case 6: if (dd>30) err++; break;
        case 7: if (dd>31) err++; break;
        case 8: if (dd>31) err++; break;
        case 9: if (dd>30) err++; break;
        case 10: if (dd>31) err++; break;
        case 11: if (dd>30) err++; break;
        case 12: if (dd>31) err++; break;

    }

    if (err==0)
        return 1;
    else
        return 0;

}



void num2word(double n,char word[])
{
    long int num;
    int a[6],i;

    num=(int)n;

    a[5]=num%1000;
    num=num/1000;

    for(i=4;i>=0;i--)
    {
        a[i]=num%100;
        num=num/100;
    }

//OK


    int m,h,tt,t,o;
    m=a[5];
    h=m/100;
    tt=m%100;
    t=tt/10;
    o=tt%10;

    char one[10],ten[10],hh[20]={0};

    if(tt<20&&h!=0)
    {
        _one(h,one);
        strcpy(hh,one);
        strcat(hh,"Hundred ");
        _one(tt,one);
        strcat(hh,one);
    }

    else if(tt<20&&h==0)
    {
        _one(tt,one);
        strcpy(hh,one);
    }
    else if(tt>20&&h!=0)
    {
        _one(h,one);
        strcpy(hh,one);
        strcat(hh,"Hundred ");
        _ten(t,ten);
        strcat(hh,ten);
        _one(o,one);
        strcat(hh,one);
    }
    else
    {
        _ten(t,ten);
        strcpy(hh,ten);
        _one(o,one);
        strcat(hh,one);
    }


//ok

    char aa[5][30];
    for(i=4;i>=0;i--)
    {
        if (a[i]<20)
        {
            _one(a[i],one);
            strcpy(aa[i],one);
        }
        else
        {
            _ten(a[i]/10,ten);
            strcpy(aa[i],ten);
            _one(a[i]%10,one);
            strcat(aa[i],one);
        }
    }

    char x[10]={0},w[50]={0};
    int l;
    for(i=0;i<5;i++)
    {
        l=strlen(aa[i]);
        if(l!=0)
        {
            switch(i)
            {
                case 0: strcpy(x,"Kharab "); break;
                case 1: strcpy(x,"Arab "); break;
                case 2: strcpy(x,"Crore "); break;
                case 3: strcpy(x,"Lakh "); break;
                case 4: strcpy(x,"Thousand "); break;
            }
            strcat(w,aa[i]);
            strcat(w,x);
        }
    }

    strcpy(word,w);
    strcat(word,hh);
    word[strlen(word)-1]='\0';

}

void _ten(int n,char ten[])
{
    switch(n)
    {
        case 2: strcpy(ten,"Twenty "); break;
        case 3: strcpy(ten,"Thirty "); break;
        case 4: strcpy(ten,"Forty "); break;
        case 5: strcpy(ten,"Fifty "); break;
        case 6: strcpy(ten,"Sixty "); break;
        case 7: strcpy(ten,"Seventy "); break;
        case 8: strcpy(ten,"Eighty "); break;
        case 9: strcpy(ten,"Ninety "); break;
        default:
        strcpy(ten,"");
    }
}

void _one(int n, char one[])
{
    switch(n)
    {
        case 1: strcpy(one,"One "); break;
        case 2: strcpy(one,"Two "); break;
        case 3: strcpy(one,"Three "); break;
        case 4: strcpy(one,"Four "); break;
        case 5: strcpy(one,"Five "); break;
        case 6: strcpy(one,"Six "); break;
        case 7: strcpy(one,"Seven "); break;
        case 8: strcpy(one,"Eight "); break;
        case 9: strcpy(one,"Nine "); break;
        case 10: strcpy(one,"Ten "); break;
        case 11: strcpy(one,"Eleven "); break;
        case 12: strcpy(one,"Tweleve "); break;
        case 13: strcpy(one,"Thirteen "); break;
        case 14: strcpy(one,"Fourteen "); break;
        case 15: strcpy(one,"Fifteen "); break;
        case 16: strcpy(one,"Sixteen "); break;
        case 17: strcpy(one,"Seventeen "); break;
        case 18: strcpy(one,"Eighteen "); break;
        case 19: strcpy(one,"Nineteen "); break;
        default:
        strcpy(one,"");




    }

}


void currency(char cur[], float n)
{

    int num,i,x,c;
    char temp[30];
    num=(int)n;
    int a[6];
    a[5]=num%1000;
    num=num/1000;

    for(i=4;i>=0;i--)
    {
        a[i]=num%100;
        num=num/100;
    }



    for(i=0;i<6;i++)
        if (a[i]!=0) break;

        x=i;
        c=0;
        for(i=x;i<6;i++)
        {
            if(i==5)
            {
                if (a[i]>=100||i!=x) cur[c++]=(a[i]/100)+48;
                if (a[i]%100>=10||i!=x) cur[c++]=(a[i]%100)/10+48;
                if (a[i]%100<10&&i==x) cur[c++]=48;
                cur[c++]=(a[i]%100)%10+48;
            }
            else
            {
                if (a[i]>=10||i!=x) cur[c++]=(a[i]/10)+48;
                cur[c++]=(a[i]%10)+48;
                cur[c++]=',';
            }

        }

        cur[c++]='.';
        num=(n-(int)n)*100;
        cur[c++]=num/10+48;
        cur[c++]=num%10+48;
        cur[c]='\0';
        if (n==0) strcpy(cur,"0.00");
        strcpy(temp,"Rs. ");
        strcat(temp,cur);
        strcpy(cur,temp);
}



void cls(int x1,int y1,int x2, int y2)
{
    int i,j;
    for(i=y1;i<=y2;i++)
        for(j=x1;j<=x2;j++)
            {
                gotoxy(j,i); printf("%c",32);
            }

}


void increase(char i_id[])
{
    int l;
    l=strlen(i_id)-1;
    do
    {
        if(i_id[l]!='9') i_id[l]+=1;
        else i_id[l]='0';
        l--;

    }while(i_id[l+1]=='0');


}

int num_of_rec(char file[],int n)
{
    FILE *fptr;
    char dat[200];
    long int c=0;
    fptr=fopen(file,"r");
    while(fscanf(fptr,"%s",dat)!=EOF) c++;
    fclose(fptr);
    return c/n;

}


void _password(char buffer[])
	{


	     	char c;
         	int pos = 0;
           	do
            	{
           		 c = getch();
            		if( isprint(c) )
            		{
            			buffer[ pos++ ] = c;
            			printf("%c", '*');
            		}
            		else if( c == 8 && pos )
            		{
            			buffer[ pos-- ] = '\0';
            			printf("%s", "\b \b");
           		}
            	}while( c != 13 );



	}



void rectangle(int x,int y,int l,int b)
{
    int i,m;
    gotoxy(x,y); printf("%c",201);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,y);
        printf("%c",205);
    }
    gotoxy(i,y); printf("%c",187);

    for (m=y+1;m<b;m++)
    {
        gotoxy(x,m);
        for(i=x;i<l;i++)
        {
            if(i==x||i==l-1)
            {
                gotoxy(i,m); printf("%c",186);
            }

        }

    }

    gotoxy(x,m); printf("%c",200);
    for(i=x+1;i<l-1;i++)
    {
        gotoxy(i,m);
        printf("%c",205);
    }
    gotoxy(i,m); printf("%c",188);
}


void title()
{
    int i;

    system("cls");

    rectangle(0,0,80,23);
    gotoxy(25,1);
    printf("Banking Management System");
    gotoxy(5,3);
    if (strcmp(user.name,"Admin")==0) gbl_flag=1;
    if (gbl_flag) printf("Current User : Admin");
    else printf("Current User : %s",user.name);
    printf("\t\t\t\tDate : ");
    _strdate(date);
    date_output(date);
    printf("%s",date);
    _strdate(date);
    gotoxy(1,5);
      for(i=0;i<78;i++) printf("%c",196);

}


COORD coord = {0, 0};

void gotoxy (int x, int y)
        {
        coord.X = x;
        coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }

