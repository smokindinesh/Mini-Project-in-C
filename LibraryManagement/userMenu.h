
// Define Constant Variables
#define ESC 27
#define MAX_PASS_SZ 60

struct stuProfile myProfile;

//Function declaration
void adminMenu();
void accessMenu();
void bookMenu();
int checkBookID(char bookID[MAX_ID]);
//int getBookIndex(char bookID[MAX_ID]);
int findStudentID(char stuId[MAX_ID]);
void viewBooksByPage(int sIndex,int lIndex,int total,int flag);
void viewAllBooks(int flag);
void addBook();
void updateBook();
void delBook();
void searchBooks(int flag);
void viewMyBooks();
void studentMenu();
void viewAccount();
void addAccount();
void updAccount();
void delAccount();
void issueReturnMenu();
void issueBook();
void returnBook();
void viewIssuedBook();


//Function definition
void adminMenu(){

    char choice;
    bkCount = readBooks();

    printWelcomeMsg();

    gotoxy(35,8);
    printf("Please select the any option a, b, c, d, e or ESC");
    gotoxy(35,10);
    printf("A) Add/Modify Admin Account");
    gotoxy(35,12);
    printf("B) Add/Modify Books Info");
    gotoxy(35,14);
    printf("C) Issue or Return Books");
    gotoxy(35,16);
    printf("D) Search Books");
    gotoxy(35,18);
    printf("E) Exit Application");
    gotoxy(35,20);
    printf("Please enter ESC to exit application");


    choice=tolower(getch());


    switch(choice){
        case 'a':
            accessMenu();
            break;
        case 'b':
            bookMenu();
            break;
        case 'c':
            issueReturnMenu();
            break;
        case 'd':
            searchBooks(1);
            break;
        case 'e':
        case ESC:
            writeBook();
            exit(0);
        default:
            gotoxy(35,22);
            printf("Please enter options V, A, U, D, E or ESC");
            if(getch())
                adminMenu();

    }

}

void accessMenu(){

    char choice;

    printWelcomeMsg();

    gotoxy(35,8);
    printf("Please enter:");
    gotoxy(35,9);
    printf("V: To View All Accounts");
    gotoxy(35,10);
    printf("A: To Add Accounts");
    gotoxy(35,11);
    printf("U: To Update Accounts");
    gotoxy(35,12);
    printf("D: To Delete Accounts");
    gotoxy(35,15);
    printf("Enter ESC to go back");

    choice=tolower(getch());

    if(choice=='v'){
        viewAccount();
    } else if (choice=='a'){
        addAccount();
    } else if (choice=='u'){
        updAccount();
    }else if (choice=='d'){
        delAccount();
    } else if (choice==ESC) {
        adminMenu();
    } else {
        gotoxy(15,17);
        printf("Please enter only options V, A, U, and D or ESC. Press any key to continue.");

        getch();
        accessMenu();
    }

}

int checkBookID(char bookID[MAX_ID]){
    int index=-1;
    for(int i=0;i<bkCount;i++){
        if(strcmp(bookID,bk[i].bookID)==0){
           index=i;
           break;
        }
    }
    return index;
}

void bookMenu(){

    char choice;

    printWelcomeMsg();

    gotoxy(35,8);
    printf("Please Enter:");
    gotoxy(35,9);
    printf("V: To View All Books");
    gotoxy(35,10);
    printf("A: To Add Books");
    gotoxy(35,11);
    printf("U: To Update Books");
    gotoxy(35,12);
    printf("D: To Delete Books");
    gotoxy(35,15);
    printf("Enter ESC to go back");

    choice=tolower(getch());

    if(choice=='v'){
        viewAllBooks(1);
    } else if (choice=='a'){
        addBook();
    } else if (choice=='u'){
        updateBook();
    } else if (choice=='d'){
        delBook();
    } else if (choice==ESC) {
        adminMenu();
    } else {
        gotoxy(15,17);
        printf("Please enter only options V, A, U, and D or ESC. Press any key to continue.");

        getch();
        bookMenu();
    }

}


//Function definition
void studentMenu(){

    char choice;
    bkCount = readBooks();



    printStudentWelcomeMsg(myProfile);

    gotoxy(35,8);
    printf("Please select the any option a, b, c, d or ESC");
    gotoxy(35,10);
    printf("A) View All Books");
    gotoxy(35,12);
    printf("B) Search Books");
    gotoxy(35,14);
    printf("C) View issued books");
    gotoxy(35,16);
    printf("D) Exit Application");
    gotoxy(35,20);
    printf("Please enter ESC to exit application");


    choice=tolower(getch());


    switch(choice){
        case 'a':
            viewAllBooks(0);
            break;
        case 'b':
            searchBooks(0);
            break;
        case 'c':
            viewMyBooks();
            break;
        case 'd':
        case ESC:
            writeBook();
            exit(0);
        default:
            gotoxy(35,22);
            printf("Please enter options A, B, C, D or ESC");
            if(getch())
                studentMenu();

    }
}

int findStudentID(char stuId[MAX_ID]){

    if(getStudentID(stuId,&myProfile)==1){

        return 1;
    } else {
        return 0;
    }
    return 0;
}
void viewAllBooks(int flag){

    //bkCount = readBooks();
    int pageSize = 15;
    int lIndex = 0;
    int hIndex = pageSize;
    char choice = 'a';

    viewBooksByPage(lIndex,hIndex,bkCount,flag);

    do{
        choice=tolower(getch());

        if(choice==ESC){
            break;
        } else if(choice=='b'){
            if(lIndex>=pageSize){
                lIndex=lIndex-pageSize;
                hIndex=lIndex+pageSize;
                if(hIndex>bkCount){
                    hIndex=bkCount;
                    viewBooksByPage(lIndex,hIndex,bkCount,flag);
                } else {
                    viewBooksByPage(lIndex,hIndex,bkCount,flag);
                }
            }

        } else if(choice=='n'){

            if(hIndex<bkCount){

                lIndex=lIndex+pageSize;
                hIndex=hIndex+pageSize;

                if(hIndex>bkCount){
                    hIndex=bkCount;
                }
                viewBooksByPage(lIndex,hIndex,bkCount,flag);

            }
        }
    }while(1==1);

    if(flag==0){
        studentMenu();
    } else if (flag==1) {
        bookMenu();
    }


}

void viewBooksByPage(int sIndex,int lIndex, int total, int flag){

    int j=0;

    if(flag==0){
        printStudentWelcomeMsg(myProfile);
    } else if(flag==1) {
        printWelcomeMsg();
    }



    gotoxy(15,8);
    printf("Showing books from %d to %d out of %d.",sIndex+1,lIndex,total);

    gotoxy(1,10);
    printf("BookID");
    gotoxy(11,10);
    printf("Title");
    gotoxy(62,10);
    printf("Author");
    gotoxy(83,10);
    printf("Genre");
    gotoxy(100,10);
    printf("Year");
    gotoxy(105,10);
    printf("ShelfNo");
    gotoxy(113,10);
    printf("Stock");
    for(int i=sIndex;i<lIndex;i++){
        gotoxy(1,11 + j);
        printf("%s",bk[i].bookID);
        gotoxy(11,11 + j);
        printf("%s",bk[i].title);
        gotoxy(62,11 + j);
        printf("%s",bk[i].author);
        gotoxy(83,11 + j);
        printf("%s",bk[i].genre);
        gotoxy(100,11 + j);
        printf("%s",bk[i].year);
        gotoxy(105,11 + j);
        printf("%s",bk[i].shelfNo);
        gotoxy(113,11 + j);
        printf("%s",bk[i].stockCount);

        j++;
    }
    gotoxy(25,13 + j);
    printf("Please press B or N to go back or next page,ESC to go back to menu..");

}
void addBook(){

    struct books b;

    printWelcomeMsg();

    gotoxy(15,10);
    printf("Please enter the book details below.");
    gotoxy(15,12);
    printf("BookID: ");
    getString(b.bookID,MAX_ID);
    if(checkBookID(b.bookID) < 0){
        gotoxy(15,13);
        printf("Title: ");
        getString(b.title,MAX_TITLE);
        gotoxy(15,14);
        printf("Author: ");
        getString(b.author,MAX_NAME);
        gotoxy(15,15);
        printf("Genre: ");
        getString(b.genre,MAX_NAME);
        gotoxy(15,16);
        printf("Year: ");
        getString(b.year,MAX_YR);
        gotoxy(15,17);
        printf("Shelf No: ");
        getString(b.shelfNo,MAX_ID);
        gotoxy(15,18);
        printf("Stock Count: ");
        getString(b.stockCount,MAX_ID);

        int newbkCount=bkCount+1;

        bk = (struct books*)realloc(bk,newbkCount * sizeof(struct books));
        bk = (bk+bkCount);

        strcpy(bk->bookID,b.bookID);
        strcpy(bk->title,b.title);
        strcpy(bk->author,b.author);
        strcpy(bk->genre,b.genre);
        strcpy(bk->year,b.year);
        strcpy(bk->stockCount,b.stockCount);
        strcpy(bk->shelfNo,b.shelfNo);

        bk = (bk-bkCount);
        bkCount=newbkCount;
    } else {
        gotoxy(15,19);
        printf("Sorry! Book ID already exist.");
    }

    gotoxy(15,20);
    printf("Press any key to continue or press ESC to go back.");
    if(getch()==ESC){
        bookMenu();
    } else {
        addBook();
    }
}

void updateBook(){
    int index;
    struct books b;

    printWelcomeMsg();

    gotoxy(15,10);
    printf("Please enter book id to update details.");
    gotoxy(15,12);
    printf("BookID: ");
    getString(b.bookID,MAX_ID);

    index = checkBookID(b.bookID);
    if(index >=0 ){
        gotoxy(15,13);
        printf("Title: ");
        getString(b.title,MAX_TITLE);
        gotoxy(15,14);
        printf("Author: ");
        getString(b.author,MAX_NAME);
        gotoxy(15,15);
        printf("Genre: ");
        getString(b.genre,MAX_NAME);
        gotoxy(15,16);
        printf("Year: ");
        getString(b.year,MAX_YR);
        gotoxy(15,17);
        printf("Shelf No: ");
        getString(b.shelfNo,MAX_ID);
        gotoxy(15,18);
        printf("Stock Count: ");
        getString(b.stockCount,MAX_ID);

        strcpy(bk[index].title,b.title);
        strcpy(bk[index].author,b.author);
        strcpy(bk[index].genre,b.genre);
        strcpy(bk[index].year,b.year);
        strcpy(bk[index].shelfNo,b.shelfNo);
        strcpy(bk[index].stockCount,b.stockCount);

    } else {
        gotoxy(15,15);
        printf("Sorry! Book ID do not exist.");
    }

    gotoxy(15,20);
    printf("Press any key to continue or press ESC to go back.");
    if(getch()==ESC){
        bookMenu();
    } else {
        updateBook();
    }
}

void delBook(){

    int indexToRemove=0;
    struct books b;

    printWelcomeMsg();

    gotoxy(15,10);
    printf("Please enter book id to delete.");
    gotoxy(15,12);
    printf("BookID: ");
    getString(b.bookID,MAX_ID);

    indexToRemove = checkBookID(b.bookID);
    if(indexToRemove >= 0){
        struct books *tmp_bk;

        tmp_bk = (struct books*)malloc((bkCount-1) * sizeof(struct books));

        if(indexToRemove != 0)
            memmove(tmp_bk,bk,(indexToRemove)*sizeof(struct books));

        if(indexToRemove != (bkCount-1))
            memmove(tmp_bk+indexToRemove,bk+(indexToRemove+1),(bkCount-indexToRemove-1)*sizeof(struct books));

        free(bk);
        bk = tmp_bk;
        bkCount--;

        gotoxy(15,15);
        printf("Book details deleted successfully");

    } else {
        gotoxy(15,15);
        printf("Sorry! Book ID do not exist.");
    }

    gotoxy(15,20);
    printf("Press any key to continue or press ESC to go back.");
    if(getch()==ESC){
        bookMenu();
    } else {
        delBook();
    }
}

void searchBooks(int flag){

    char bookID[MAX_ID];
    int index=-1;

    if(flag==0){
        printStudentWelcomeMsg(myProfile);
    } else if(flag==1) {
        printWelcomeMsg();
    }
    gotoxy(35,8);
    printf("Please enter BookID: ");
    getString(bookID,MAX_ID);

    index = checkBookID(bookID);

    if(index >= 0){
        gotoxy(35,9);
        printf("BookID %s details: ",bookID);
        gotoxy(35,10);
        printf("-------------------------------------------------");
        gotoxy(35,12);
        printf("Title: %s",bk[index].title);
        gotoxy(35,13);
        printf("Author: %s",bk[index].author);
        gotoxy(35,14);
        printf("Genre: %s",bk[index].genre);
        gotoxy(35,15);
        printf("Year: %s",bk[index].year);
        gotoxy(35,16);
        printf("ShelfNO: %s",bk[index].shelfNo);
        gotoxy(35,17);
        printf("StockCount: %s",bk[index].stockCount);
    } else {
        gotoxy(35,12);
        printf("Sorry! Book not found.");
    }

    gotoxy(35,25);
    printf("Please press any key to go back.");
    getch();
    if(flag==0){
        studentMenu();
    } else if(flag==1) {
        adminMenu();
    }
}

void viewMyBooks(){

    struct stuBooks sb[READ_ARRAY_SZ];;
    int sz=0;
    int j=0;

    sz = viewMyStuBook(sb,myProfile.stuID,READ_ARRAY_SZ);

    printStudentWelcomeMsg(myProfile);

    gotoxy(10,10);
    printf("Book ID");
    gotoxy(20,10);
    printf("Title");
    gotoxy(70,10);
    printf("Author");
    gotoxy(90,10);
    printf("Start Date");
    gotoxy(105,10);
    printf("End Date");
    for(int i=0; i<sz; i++){
        gotoxy(10,11 + j);
        printf("%s",sb[i].bookID);
        gotoxy(20,11 + j);
        printf("%s",sb[i].title);
        gotoxy(70,11 + j);
        printf("%s",sb[i].author);
        gotoxy(90,11 + j);
        printf("%s",sb[i].startDate);
        gotoxy(105,11 + j);
        printf("%s",sb[i].endDate);

        j++;
    }
    gotoxy(25,13 + j);
    printf("Please press any key to go back to menu..");
    getch();
    studentMenu();
}

void viewAccount(){

    struct password p[MAX_PASS_SZ];
    int data_sz=0;
    int col_sz=4;
    int x=0,y=0;

    data_sz=view(p,MAX_PASS_SZ);
    int row_num=0;
    int col_num=0;

    printWelcomeMsg();

    gotoxy(35,8);
    printf("List of User Accounts(Total:%d)",data_sz);
    for(int i=0;i<data_sz;i++){

        row_num = i/col_sz;
        col_num=i%col_sz;

        x=15+MAX_USR_SZ*col_num;
        y=10+row_num;
        gotoxy(x,y);
        printf("%d.%s",1+i,p[i].userName);
    }
    gotoxy(35,y+2);
    printf("Please press any key to go back.");
    getch();
    accessMenu();

}
void addAccount(){
    char passV[MAX_PWD_SZ];
    struct password pd;

    printWelcomeMsg();

    gotoxy(35,8);
    printf("Please Enter New Username and Password.");
    gotoxy(35,10);
    printf("New User Name: ");
    getString(pd.userName,MAX_USR_SZ);
    gotoxy(35,11);
    printf("New Password: ");
    getPassword(pd.password,MAX_PWD_SZ);
    gotoxy(35,12);
    printf("Re-type Password: ");
    getPassword(passV,MAX_PWD_SZ);


    if(strcmp(passV,pd.password)==0){
        if(check(pd,1)==0){

            add(pd);

            printWelcomeMsg();

            gotoxy(35,8);
            printf("Congratulation! User account created.");
            gotoxy(35,10);
            printf("Please press any key to add more accounts or press ESC to go back.");
            if(getch()==ESC){
                accessMenu();
            } else {
                addAccount();
            }
        } else {
            printWelcomeMsg();

            gotoxy(15,8);
            printf("Sorry! Username already exits. Press any key to continue or press ESC to go back.");
            if(getch()==ESC){
                accessMenu();
            } else {
                addAccount();
            }
        }


    } else {

        printWelcomeMsg();

        gotoxy(15,8);
        printf("Sorry! Both passwords do not match. Press any key to continue or press ESC to go back.");
        if(getch()==ESC){
            accessMenu();
        } else {
            addAccount();
        }

    }
}
void updAccount(){

    struct password pd;

    printWelcomeMsg();

    gotoxy(35,8);
    printf("Please Enter Username");
    gotoxy(35,10);
    printf("User Name: ");
    getString(pd.userName,MAX_USR_SZ);
    gotoxy(35,11);
    printf("new Password: ");
    getPassword(pd.password,MAX_PWD_SZ);
    if(update(pd)==1){
        gotoxy(15,13);
        printf("Username updated successfully. Press any key to continue or press ESC to go back.");
    } else {
        gotoxy(15,13);
        printf("Sorry! Username do not exit. Press any key to continue or press ESC to go back.");
    }
    if(getch()==ESC){
        accessMenu();
    } else {
        updAccount();
    }

}
void delAccount(){

    char uName[MAX_USR_SZ];

    printWelcomeMsg();

    gotoxy(35,8);
    printf("Please Enter Username");
    gotoxy(35,10);
    printf("User Name: ");
    getString(uName,MAX_USR_SZ);

    if(del(uName)==1){
        gotoxy(15,13);
        printf("Username deleted successfully. Press any key to continue or press ESC to go back.");
    } else {
        gotoxy(15,13);
        printf("Sorry! Username do not exit. Press any key to continue or press ESC to go back.");
    }
    if(getch()==ESC){
        accessMenu();
    } else {
        delAccount();
    }
}

void issueReturnMenu(){

    char choice;

    printWelcomeMsg();

    gotoxy(35,8);
    printf("Please Enter:");
    gotoxy(35,9);
    printf("V: To View Issued Books");
    gotoxy(35,10);
    printf("I: To Issue Books");
    gotoxy(35,11);
    printf("R: To Return Books");
    gotoxy(35,14);
    printf("Enter ESC to go back");

    choice=tolower(getch());

    if(choice=='v'){
        viewIssuedBook();
    } else if(choice=='i'){
        issueBook();
    } else if (choice=='r'){
        returnBook();
    } else if (choice==ESC) {
        adminMenu();
    } else {
        gotoxy(15,17);
        printf("Please enter only options I and R or ESC. Press any key to continue.");

        getch();
        issueReturnMenu();
    }

}

void issueBook(){

    char bookID[MAX_ID];
    struct stuBooks sb;
    int index;
    int tempNum;
    char tempStr[MAX_ID];

    printWelcomeMsg();

    gotoxy(15,8);
    printf("Please enter BookID:");
    getString(bookID,MAX_ID);

    index=checkBookID(bookID);

    if(index==-1){
        gotoxy(15,10);
        printf("Sorry BookID does not exist or out of stock.");
    } else if(strcmp(bk[index].stockCount,"0")==0){
        gotoxy(15,10);
        printf("Sorry BookID is out of stock.");
    } else {
        strcpy(sb.bookID,bookID);
        strcpy(sb.author,bk[index].author);
        strcpy(sb.title,bk[index].title);

        gotoxy(15,9);
        printf("Please enter Student ID:");
        getString(sb.stuID,MAX_ID);
        gotoxy(15,10);
        printf("Please enter Start Date:");
        getString(sb.startDate,DATE_SZ);
        gotoxy(15,11);
        printf("Please enter end Date:");
        getString(sb.endDate,DATE_SZ);

        addStuBook(sb);

        tempNum = stringToInt(bk[index].stockCount);
        intToString(tempStr,tempNum-1);
        strcpy(bk[index].stockCount,tempStr);

        gotoxy(15,13);
        printf("Book issued successfully.");

    }

    gotoxy(15,18);
    printf("Press any key to continue or press ESC to go back.");

    if(getch()==ESC){
        issueReturnMenu();
    } else {
        issueBook();
    }


}

void returnBook(){

    char bookID[MAX_ID];
    char stuID[MAX_ID];
    char retDate[DATE_SZ];
    int index;

    printWelcomeMsg();

    gotoxy(15,8);
    printf("Please enter BookID: ");
    getString(bookID,MAX_ID);

    index=checkBookID(bookID);

    if(index==-1){
        gotoxy(15,10);
        printf("Sorry BookID does not exist.");
    } else {
        gotoxy(15,9);
        printf("Please enter Student ID: ");
        getString(stuID,MAX_ID);

        gotoxy(15,10);
        printf("Please enter return Date: ");
        getString(retDate,DATE_SZ);

        if(updateStuBook(bookID,stuID,retDate)==1){
            gotoxy(15,12);
            printf("Record updated successfully!.");

        } else {
            gotoxy(15,12);
            printf("Sorry! Record not updated. Student ID do not exist.");
        }
    }

    gotoxy(15,18);
    printf("Press any key to continue or press ESC to go back.");

    if(getch()==ESC){
        issueReturnMenu();
    } else {
        returnBook();
    }
}

void viewIssuedBook(){

    int data_sz=0;
    int j=0;
    struct stuBooks sb[READ_ARRAY_SZ];
    data_sz = viewStuBook(sb,READ_ARRAY_SZ);

    printWelcomeMsg();

    gotoxy(15,8);
    printf("Showing issued books (Only %d items)",data_sz);

    gotoxy(1,10);
    printf("StudentID");
    gotoxy(11,10);
    printf("Book ID");
    gotoxy(21,10);
    printf("Title");
    gotoxy(71,10);
    printf("Author");
    gotoxy(86,10);
    printf("Start Date");
    gotoxy(101,10);
    printf("End Date");
    for(int i=0; i<data_sz; i++){
        gotoxy(1,11 + j);
        printf("%s",sb[i].stuID);
        gotoxy(11,11 + j);
        printf("%s",sb[i].bookID);
        gotoxy(21,11 + j);
        printf("%s",sb[i].title);
        gotoxy(71,11 + j);
        printf("%s",sb[i].author);
        gotoxy(86,11 + j);
        printf("%s",sb[i].startDate);
        gotoxy(101,11 + j);
        printf("%s",sb[i].endDate);

        j++;
    }
    gotoxy(25,13 + j);
    printf("Please press any key to go back to menu..");
    getch();
    issueReturnMenu();
}
