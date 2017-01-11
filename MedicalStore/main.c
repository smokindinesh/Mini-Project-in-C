#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<dos.h>
#include<time.h>
#include<ctype.h>
#include<windows.h>

COORD coord = {0, 0};
void gotoxy(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int i;
//function for auto increment customer & supplier Id.
int getcust_id();
int getsupp_id();
//function for welcome & main menu
void welcome();
void main_menu();
//function for all box
void main_box();
void box1();
void wbox();
//function for bill slip
void bill();
//function for about menu
void about();
//function for medicine menu
void medicine();
void medi_sale();
void stock();
void update_stock();
void medi_entry();
void medi_search();
void remainders();
//function for supplier menu
void supplier();
void supp_entry();
void supp_list();
void sup_update();
void search();
void search_id();
void search_name();
//function for customer menu
void customer();
void cust_search();
void search_cid();
void search_cname();
void cust_entry();
void cust_list();
void cust_update();
//function for report menu
void report_menu();
void report();
void sale_rpt();
void sale_rpt_daily();
void profit_rpt();
void pur_rpt();
void pur_rpt_daily();
//===================================structures =========================
struct medical
{
	char id[6];
	char medi_name[20];
	int rack;
	char cabnit[2];
	int quantity;
	float sale;
	float total;
	float unit;
	float cost;
	float profit;
	float bye;
	int qty;
	char pur_date[15];
	char exp_date[15];
	char manu_date[15];
	int bill_no;
	char comp_name[20];
	char supp_name[30];
 };

struct medical temp;
struct medical x[20];
FILE *ptr;

char a[10];
struct supplier
{
	int supp_id;
	char supp_name[25];
	char city[20];
	char mob_no[11];
	char email[30];

};
struct supplier temp1;

struct customer
{
	int cust_id;
	char cust_name[30];
	char city[20];
	char mob_no[11];
	char email[50];

};
struct customer temp_c;
FILE *ptr1;

struct bill
{
	char billno[6];
	char cname[30];
	char mediname[30];
	int medi_qty;
	float medi_rate;
	float total;
	int day;
	int month;
	int year;

};
struct bill bil;
FILE *ptrbill;
struct sales_report
{
	char medi_id[6];
	char medir_name[20];
	char cust_name[30];
	int sDay,sMonth,sYear;
	int qty;
	float rate;
	float total;
};
struct sales_report s_r;
FILE *ptrs_r;

struct purchase_report
{
	char medi_id[6];
	char medir_name[20];
	char supp_name[30];
	int sDay,sMonth,sYear;
	int qty;
	float rate;
	float total;
};
struct purchase_report p_r;
FILE *ptrp_r;

struct profit_report
{
	char medi_id[6];
	char medir_name[20];
	int sDay,sMonth,sYear;
	int qty;
	float rate;
	float unit;
	float profit;
};
struct profit_report pr_r;
FILE *ptrpr_r;

void linkfloat()
{
	float f,*p;
	p=&f;
	f=*p;
}

//=========================Time & Date ====================
int t(void)
{
	//struct date d;
	//struct time t;

    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
	//getdate(&d);
	//gettime(&t);
	gotoxy(55,46);
	printf("Date: %d-%d-%d ",now->tm_mday,now->tm_mon,now->tm_year);
	gotoxy(55,48);
	printf("Time: %d:%d:%d",now->tm_hour, now->tm_min,now->tm_sec);
	return 0;
}

//=======================Animation ==========================
void animation()
{
	for (i=45; i>=1; i--)
	{
		Sleep(30);
		gotoxy(1,i);
		//clreol();
	}
	for (i=1; i<=20; i++)
	{
		//clreol();
		Sleep(40);
		gotoxy(1,i);
	}
}
//=========================== validation =========================
void ventry(char t[],int code)
{
  int i=0;
	if(code==0)
	{
		while((t[i]=getch())!='\r' && i<30)
		if((t[i]>=97 && t[i]<=122) || (t[i]>=65 && t[i]<=90) || t[i]==32 || t[i]=='_')
		{
			printf("%c",t[i]);
			i++;
		}
		else if(t[i]==8 && i>0)
		{
			printf("%c%c%c",8,32,8);
			i--;              //Length counter is decremented.

		}
	}
	else if(code==1)
	{
		while((t[i]=getch())!='\r' && i<10 )
		if((t[i]>=48 && t[i]<=57) || t[i]==46 ||  t[i]=='-')
		{
			printf("%c",t[i]);
			i++;
		}
		else if(t[i]==8 && i>0)
		{
			printf("%c%c%c",8,32,8);
			i--;              //Length counter is decremented.

		}
	}
	else if(code==2)
	{
		while((t[i]=getch())!='\r' && i<30 )
		if((t[i]>=97 && t[i]<=122) || (t[i]>=65 && t[i]<=90) ||(t[i]>=48 && t[i]<=57) || t[i]==32 || t[i]==8 ||t[i]=='@'||t[i]=='.')
		{
			printf("%c",t[i]);
			i++;
		}
		else if(t[i]==8 && i>0)
		{
			printf("%c%c%c",8,32,8);
			i--;              //Length counter is decremented.

		}
	}

	t[i]='\0';
}
//============================================================================
void box()
{
   for(i=3;i<=79;i++) 	//This 'FOR' loop will print a combination of
	{
		gotoxy(i,3);    //the 79th column is reached.
		printf("%c",219);
		gotoxy(78,45);
		printf("%c",219);
		gotoxy(i,45);
		printf("%c",219);
	}

	for(i=3;i<=45;i++)      //This 'FOR' loop will print asteriks 'I'
	{                       //vertically till the 3th row is reached.
		gotoxy(3,i);
		printf("%c",219);
		gotoxy(79,i);
		printf("%c",219);
	}
}
void wbox()
{
	for(i=5;i<=75;i++) 	//This 'FOR' loop will print a combination of
	{
		gotoxy(i,5);    //the 75th column is reached.
		printf("%c",219);
		gotoxy(74,40);
		printf("%c",219);
		gotoxy(i,40);
		printf("%c",219);
	}

	for(i=5;i<=40;i++)      //This 'FOR' loop will print asteriks 'I'
	{                       //vertically till the 17th row is reached.
		gotoxy(5,i);
		printf("%c",219);
		gotoxy(75,i);
		printf("%c",219);
	}
}
//=========================getsupp_id =======================
int getsupp_id()
{

 FILE *fp;
	 fp=fopen("supplier.dat","r");
	 if(fp==NULL)
	 {
		gotoxy(22,15);
		printf("Data not Found.....");
		getch();
	 }
	 else
	 {
		temp1.supp_id=100;
		rewind(fp);
		while(fscanf(fp,"%d %s %s %s %s",&temp1.supp_id,temp1.supp_name,temp1.city, temp1.mob_no,temp1.email)!=EOF)
		{
		}
	 }
	 fclose(fp);
	 return temp1.supp_id+1;
}

//=========================getcust_id =======================
int getcust_id()
{
 FILE *fp;
	 fp=fopen("customer.dat","r");
	 if(fp==NULL)
	 {
		gotoxy(22,15);
		printf("Data not Found.....");
		getch();
	 }
	 else
	 {
		temp_c.cust_id=100;
		rewind(fp);
		while(fscanf(fp,"%d %s %s %s %s",&temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email)!=EOF)
		{
		}
	 }
	 fclose(fp);
	 return temp_c.cust_id+1;
}


//=========================welcome screen ==============

void welcome()
{
 int j,k,l,m;
 system("cls");
	for(m=0;m<16;m++)
	{
		//textcolor(m);
		wbox();
	for(i=0;i<16;i++)
	{
		//textcolor(i);
		gotoxy(35,20);
		printf("WELCOME");
		k=i+2;
		//textcolor(k);
		gotoxy(38,22);
		printf("TO");
		l=i+3;
		//textcolor(l);
		gotoxy(28,24);
		printf("MEDICAL");
		//textcolor(l);
		gotoxy(36,24);
		printf("STORE");
		//textcolor(l);
		gotoxy(42,24);
		printf("SYSTEM");
		gotoxy(52,45);
		j=i+1;
		//textcolor(j);
		printf("Loading......");
		Sleep(40);
	}
	}
}
//============================ box for label ==========
void lbox()
{
	gotoxy(25,6);
	printf("%c",201);
	for(i=26;i<55;i++)
	{
		gotoxy(i,6);
		printf("%c",205);
	}
	gotoxy(55,6);
	printf("%c",187);
	gotoxy(25,6);
	for(i=6;i<8;i++)
	{
		gotoxy(25,i+1);
		printf("%c",186);
	}
	gotoxy(25,9);
	printf("%c",200);
	for(i=26;i<55;i++)
	{
		gotoxy(i,9);
		printf("%c",205);
	}
	gotoxy(55,9);
	printf("%c",188);
	gotoxy(55,6);
	for(i=6;i<8;i++)
	{
		gotoxy(55,i+1);
		printf("%c",186);
	}

}
//============================small box ===============
void box1()
{
	gotoxy(1,3);
	printf("%c",201);
	for(i=1;i<79;i++)
	{
		gotoxy(1+i,3);
		printf("%c",205);
	}

	gotoxy(80,3);
	printf("%c",187);
	gotoxy(1,3);
	for(i=4;i<10;i++)
	{
		gotoxy(1,i);
		printf("%c",186);
	}
	gotoxy(1,9);
	for(i=4;i<8;i++)
	{
		gotoxy(80,i);
		printf("%c",186);
	}
}

//===========================main ===================

int main()
{
	char name[15];
	char pass[15];
	int count=0,i;

	system("cls");

	/*start:
	//textcolor(5);
	wbox();
	lbox();
	//textcolor(GREEN);
	gotoxy(35,8);
	printf(" LOGIN ");

	//textcolor(RED);
	gotoxy(32,18);
	printf("Enter user name :");
	gotoxy(32,22);
	printf("Enter password  :");
	gotoxy(51,18);
	strcpy(gets(name),name);

	gotoxy(51,22);

	i=0;
	do
	{
		pass[i] = getch();
		if(pass[i] == 13 )
		{
			break;
		}
		else if(pass[i]==8 && i>0)
		{
			printf("%c%c%c",8,32,8);
			i--;
		}
		else
		{
			printf("*");
			i++;
		}
	}while(pass[i]!=13);
	pass[i] = '\0';

	if(strcmp(name,"rana") || strcmp(pass,"singh"))
	{
	 system("cls");
	 gotoxy(20,20);
	 printf("Please Enter vailid Username & Passward!!!!!");
	 count++;
	 gotoxy(20,23);
	 printf("%d chance left!!!!",3-count);
	 getch();
	 system("cls");
	 if(count==3)
	 exit(0);
	 else
	 goto start;
	}
	else
	{*/
	 //welcome();
	 main_menu();
	//}

}

void main_box()
{
	gotoxy(1,6);
	printf("%c",201);
	for(i=1;i<79;i++)
	{
		gotoxy(1+i,6);
		printf("%c",205);
	}

	gotoxy(80,6);
	printf("%c",187);
	gotoxy(1,6);
	for(i=5;i<35;i++)
	{
		gotoxy(1,2+i);
		printf("%c",186);
	}
	gotoxy(1,37);
	printf("%c",200);
	for(i=1;i<79;i++)
	{
		gotoxy(1+i,37);
		printf("%c",205);
	}
	gotoxy(80,37);
	printf("%c",188);
	gotoxy(80,6);
	for(i=5;i<35;i++)
	{
		gotoxy(80,2+i);
		printf("%c",186);
	}
}

void main_menu()
{
  char ch;

	do
	{
		//window(1,1,80,50);
		//textbackground(BLACK);
		system("cls");
		//textcolor(4+BLINK);
		gotoxy(3,5);
		printf("S");
		//textcolor(WHITE);
		gotoxy(4,5);
		printf("upplier Info");
		//textcolor(4+BLINK);
		gotoxy(19,5);
		printf("C");
		//textcolor(15);
		gotoxy(20,5);
		printf("ustomer Info");
		//textcolor(4+BLINK);
		gotoxy(36,5);
		printf("M");
		//textcolor(15);
		gotoxy(37,5);
		printf("edicine");
		//textcolor(4+BLINK);
		gotoxy(48,5);
		printf("R");
		//textcolor(15);
		gotoxy(49,5);
		printf("Report");
		//textcolor(4+BLINK);
		gotoxy(57,5);
		printf("B");
		//textcolor(15);
		gotoxy(58,5);
		printf("ill");
		//textcolor(4+BLINK);
		gotoxy(64,5);
		printf("A");
		//textcolor(15);
		gotoxy(65,5);
		printf("bout");
		//textcolor(4+BLINK);
		gotoxy(72,5);
		printf("E");
		//textcolor(15);
		gotoxy(73,5);
		printf("xit");
		t();   //this function display date & time
		box1();
		main_box();
		gotoxy(30,10);
		//textcolor(GREEN);
		printf("Welcome To Medical Store ");
		gotoxy(2,28);
		//textcolor(15);

		remainders();//this function is active when medicine qty is less then 10.
		gotoxy(10,40);
		//textcolor(RED+BLINK);
		printf("Press ");
		gotoxy(16,40);
		//textcolor(15);
		printf("First Character for further Menu  ");

		ch=toupper(getche());
		switch(ch)
		{
			case 'S':supplier();
				 break;
			case 'C':customer();
				 break;
			case 'M':medicine();
				 break;
			case 'R':report_menu();
				 break;
			case 'B':bill();
				 break;
			case 'A':about();
				 break;
			case 'E':gotoxy(23,20);
				 //textcolor(4);
			printf("Do you want to exit now? Y/N :");
			Sleep(100);
			ch=(getche());
			ch=toupper(ch);
			if(ch=='Y')
			{
				animation();
				system("cls");
				//textcolor(2);
				gotoxy(35,20);
				printf(" Please wait.....");
				Sleep(2000);
				exit(0);
			}
			else
			{
				main_menu();
			}

			default://textcolor(4+BLINK);
			gotoxy(11,34);
			printf("Plese Enter right character ONLY (S,C,M,R,B,A).");
			getch();
		}
	}while(ch!='E');
}
//=========================For supplier ===========================
void supplier()
{
  char ch;
	do
	{
	  system("cls");
	  gotoxy(34,3);
	  //textcolor(GREEN);
	  printf("----------------");
	  gotoxy(35,4);
	  //textcolor(GREEN);
	  printf("Supplier MENU");
	  gotoxy(34,5);
	  //textcolor(GREEN);
	  printf("----------------");
	  gotoxy(25,11);
	  //textcolor(4+BLINK);
	  printf("A");
	  gotoxy(26,11);
	  //textcolor(15);
	  printf("dd New Supplier");

	  gotoxy(25,15);
	  //textcolor(4+BLINK);
	  printf("U");
	  gotoxy(26,15);
	  //textcolor(15);
	  printf("pdate Supplier");

	  gotoxy(25,19);
	  //textcolor(4+BLINK);
	  printf("S");
	  gotoxy(26,19);
	  //textcolor(15);
	  printf("earch Supplier");

	  gotoxy(25,23);
	  //textcolor(4+BLINK);
	  printf("L");
	  gotoxy(26,23);
	  //textcolor(15);
	  printf("ist of Existing Supplier");

	  gotoxy(25,27);
	  //textcolor(4+BLINK);
	  printf("M");
	  gotoxy(26,27);
	  //textcolor(15);
	  printf("ain Menu");
	  main_box();

	  gotoxy(10,40);
	  //textcolor(15);
	  printf("Press First Character for further Operation ");


	  ch=toupper(getche());
	  switch(ch)
	  {
		case 'A':animation();
			 supp_entry();
			 break;
		case 'U':animation();
			 sup_update();
			 break;
		case 'L':animation();
			 supp_list();
			 break;
		case 'S':search();
			 break;
		case 'M':main_menu();
			 break;
		default://textcolor(4+BLINK);
			gotoxy(11,34);
			printf("Plese Enter right character ONLY (A,L,U,S,M).");
			getch();
	  }
	}while(ch!='M');

}
//=========================For customer ===========================
void customer()
{
	char ch;
	do
	{
	  system("cls");

	  gotoxy(34,3);
	  //textcolor(GREEN);
	  printf("---------------");
	  gotoxy(35,4);
	  printf("Customer Menu.");
	  gotoxy(34,5);
	  printf("---------------");
	  gotoxy(25,11);
	  //textcolor(4+BLINK);
	  printf("A");
	  gotoxy(26,11);
	  //textcolor(15);
	  printf("dd New Customer");

	  gotoxy(25,15);
	  //textcolor(4+BLINK);
	  printf("U");
	  gotoxy(26,15);
	  //textcolor(15);
	  printf("pdate Customer");

	  gotoxy(25,19);
	  //textcolor(4+BLINK);
	  printf("S");
	  gotoxy(26,19);
	  //textcolor(15);
	  printf("earch Customer");

	  gotoxy(25,23);
	  //textcolor(4+BLINK);
	  printf("L");
	  gotoxy(26,23);
	  //textcolor(15);
	  printf("ist of Existing Customer");

	  gotoxy(25,27);
	  //textcolor(4+BLINK);
	  printf("M");
	  gotoxy(26,27);
	  //textcolor(15);
	  printf("ain Menu");
	  main_box();

	  gotoxy(10,40);
	  //textcolor(15);
	  printf("Press First Character for further Operations  ");


	  ch=toupper(getche());
	  switch(ch)
	  {
		case 'A':animation();
			 cust_entry();
			 break;
		case 'U':animation();
			 cust_update();
			 break;
		case 'L':animation();
			 cust_list();
			 break;
		case 'S':cust_search();
			 break;
		case 'M':main_menu();
			 break;
		default://textcolor(4+BLINK);
			gotoxy(11,34);
			printf("Plese Enter right character ONLY (A,L,U,S,M).");
			getch();
	  }
	}while(ch!='M');

}
//=========================For Medicine ===========================
void medicine()
{
	char ch;
	do
	{
	  system("cls");

	  gotoxy(34,3);
	  //textcolor(GREEN);
	  printf("---------------");
	  gotoxy(35,4);
	  printf("Medicine Menu.");
	  gotoxy(34,5);
	  printf("---------------");
	  gotoxy(25,15);
	  //textcolor(4+BLINK);
	  printf("P");
	  gotoxy(26,15);
	  //textcolor(15);
	  printf("urchase New Medicine");

	  gotoxy(25,19);
	  //textcolor(4+BLINK);
	  printf("S");
	  gotoxy(26,19);
	  //textcolor(15);
	  printf("ale Medicine");

	  gotoxy(25,23);
	  //textcolor(15);
	  printf("Sto");
	  gotoxy(28,23);
	  //textcolor(4+BLINK);
	  printf("c");
	  gotoxy(29,23);
	  //textcolor(15);
	  printf("k of Medicine");

	  gotoxy(25,27);
	  //textcolor(15);
	  printf("Se");
	  gotoxy(27,27);
	  //textcolor(4+BLINK);
	  printf("a");
	  gotoxy(28,27);
	  //textcolor(15);
	  printf("rch Medicine");

	  gotoxy(25,31);
	  //textcolor(4+BLINK);
	  printf("M");
	  gotoxy(26,31);
	  //textcolor(15);
	  printf("ain Menu");
	  main_box();

	  gotoxy(10,40);
	  //textcolor(15);
	  printf("Press First Character for further Operations  ");


	  ch=toupper(getche());
	  switch(ch)
	  {
		case 'P':medi_entry();
			 break;
		case 'S':medi_sale();
			 break;
		case 'C':stock();
			 break;
		case 'A':medi_search();
			 break;
		case 'M':main_menu();
			 break;
		default://textcolor(4+BLINK);
			gotoxy(11,34);
			printf("Plese Enter right character ONLY (P,S,C,M).");
			getch();
	  }
	}while(ch!='M');

}
//=========================For Report ===========================
void report_menu()
{
	char ch;
	do
	{
	  system("cls");

	  gotoxy(34,3);
	  //textcolor(GREEN);
	  printf("---------------");
	  gotoxy(35,4);
	  printf("Report Menu.");
	  gotoxy(34,5);
	  printf("---------------");
	  gotoxy(25,12);
	  //textcolor(4+BLINK);
	  printf("P");
	  gotoxy(26,12);
	  //textcolor(15);
	  printf("urchase Report");

	  gotoxy(25,16);
	  //textcolor(4+BLINK);
	  printf("S");
	  gotoxy(26,16);
	  //textcolor(15);
	  printf("ale Report");

	  gotoxy(25,20);
	  //textcolor(15);
	  printf("Pr");
	  gotoxy(27,20);
	  //textcolor(4+BLINK);
	  printf("o");
	  gotoxy(28,20);
	  //textcolor(15);
	  printf("fit Report");

	  gotoxy(25,24);
	  //textcolor(15);
	  printf("D");
	  gotoxy(26,24);
	  //textcolor(4+BLINK);
	  printf("a");
	  gotoxy(27,24);
	  //textcolor(15);
	  printf("ily Sale Report");

	  gotoxy(25,28);
	  //textcolor(4+BLINK);
	  printf("D");
	  gotoxy(26,28);
	  //textcolor(15);
	  printf("aily Purchase Report");

	  gotoxy(25,32);
	  //textcolor(4+BLINK);
	  printf("M");
	  gotoxy(26,32);
	  //textcolor(15);
	  printf("ain Menu");
	  main_box();

	  gotoxy(10,40);
	  //textcolor(15);
	  printf("Press First Character for further Operations  ");


	  ch=toupper(getche());
	  switch(ch)
	  {
		case 'P':pur_rpt();
			 break;
		case 'S':sale_rpt();
			 break;
		case 'A':sale_rpt_daily();
			 break;
		case 'O':profit_rpt();
			 break;
		case 'D':pur_rpt_daily();
			 break;
		case 'M':main_menu();
			 break;
		default://textcolor(4+BLINK);
			gotoxy(11,34);
			printf("Plese Enter right character ONLY (P,S,O,M).");
			getch();
	  }
	}while(ch!='M');

}

void about()
{  int c;
   system("cls");

   do
   {
//   window(1,1,80,50);

	//textcolor(LIGHTGRAY);
	gotoxy(28,4);
	//textcolor(RED+BLINK);
	printf("***** MEDICAL STORE *****");
	gotoxy(10,8);
	printf("=> This Project Is About Medical Store ");
	gotoxy(10,10);
	printf("=> In This Project we Can Add Medicine ,Customer,Supplier Details");
	gotoxy(10,12);
	printf("=> We Can Modifed & Delete Existing Record");
	gotoxy(10,14);
	printf("=> We Can Also Search Medicine ,Customer,Supplier Details");
	gotoxy(10,16);
	printf("=> It's Helpfull For Display Stock Of Medicine ");

	printf("<<<<-Press 1 for main menu->>>>");
	c = (getche());

	switch (c)      //This 'SWITCH' structure will ask the user for input from [1] to [7] and will display error on Invalid Entry.
		{
			case '1':animation(); main_menu();
				gotoxy(26,24);
				puts("<<--ENTER FROM 1 PLEASE-->>");	//This message will only print on INVALID ENTRY and Will ask again for input.
				getch();
		}

}while(c != '1');

}
//======================remainders for medicine stock ===============
void remainders()
{
	ptr1=fopen("medical.dat","r");
	if(ptr1==NULL)
	{
	//	printf("\n\t Can not open File! ");
	}
	while((fread(&temp,sizeof(temp),1,ptr1))==1)
	{
		if(temp.quantity<10)
		{
			gotoxy(10,45);
			//textcolor(RED);
			printf("%s : ",temp.medi_name);
			printf("Quantity of this medicine is less then 10");
		}
	}
}

//========================for bill =============================
void bill()
{
//struct date d;
    time_t td = time(0);   // get time now
    struct tm * now = localtime( & td );

	   FILE *ptrbill;
	   char id[6];
	   int j=1,d1,m,y,k;
	   float netamt=0.0;
	   //getdate(&d);
	   d1=now->tm_mday;
	   m=now->tm_mon;
	   y=now->tm_year;
	   system("cls");
	   ptrbill=fopen("dbbill.dat","r");
	   gotoxy(13,4);
	   printf("Enter bill no : ");
	   scanf("%s",&id);
	   system("cls");
	   gotoxy(25,3);
	   ////textcolor(YELLOW+BLINK);
	  // printf("***** CareWell Medico *****");
	   box();
	   gotoxy(7,7);
	   printf("Bill No: ");
	   printf(" %s",id);
	   gotoxy(7,9);
	   printf("Customer Name: ");
	   gotoxy(50,7);
	   printf("Date : ");
	   printf("%d-%d-%d",d1,m,y);
	   gotoxy(7,12);
	   printf("Sr.No   Medicine Name       Qty          Rate         Total ");
	   gotoxy(6,14);
	   printf("---------------------------------------------------------------------");

	   i=15;
	   while(fscanf(ptrbill,"%s %s %s %d %f %f %d %d %d",bil.billno,bil.cname,bil.mediname,&bil.medi_qty,&bil.medi_rate,&bil.total,&bil.day,&bil.month,&bil.year)!=EOF)
	   {

		       do
		       {
			if(strcmp(id,bil.billno)==0)
			{
				gotoxy(7,i);
				printf(" %d",j);
				gotoxy(14,i);
				printf(" %s",bil.mediname);
				gotoxy(22,9);
				printf(" %s",bil.cname);
				gotoxy(35,i);
				printf(" %d",bil.medi_qty);
				gotoxy(47,i);
				printf(" %.2f",bil.medi_rate);
				gotoxy(60,i);
				printf(" %.2f",bil.total);
				netamt=netamt+bil.total;
				i++;
				j++;
				gotoxy(35,32);
				printf("                                ");
				gotoxy(20,50);
				//textcolor(YELLOW+BLINK);
				printf("Press Any key to go to  MENU ...........");

			       //	break;
			}


		}while(feof(ptrbill));

	   }


	   gotoxy(6,35);
	   printf("---------------------------------------------------------------------");
	   gotoxy(50,37);
	   printf("Net Amount : ");
	   printf("%.2f",netamt);

	   fclose(ptrbill);
	   getch();
}

//========FOR SUPPLIERS ENTRY=================
void supp_entry()
{
 int id;
 char ch;
 FILE *fp;
 system("cls");

	   fp=fopen("supplier.dat","a");
	   if(fp==NULL)
	   {
		printf("\n Can not open file!!");
		exit(0);
	   }
	   system("cls");
	   ch='y';
	   while(ch=='y')
	   {
		system("cls");
		//textcolor(14);
		t();
		box();
		lbox();
		gotoxy(30,8);
		printf(" SUPPLIER ENTRY ");
		gotoxy(8,13);
//		//flushall();
		temp1.supp_id=getsupp_id();
		printf("SUPPLIER ID : %d ",temp1.supp_id);
		//ventry(temp1.supp_id,1);
		//flushall();
		gotoxy(39,13);
		printf("SUPPLIER NAME : ");
		gotoxy(8,18);
		printf("CITY        : ");
		gotoxy(39,18);
		printf("CONTACT NO.   : ");
		gotoxy(8,23);
		printf("EMAIL ID    : ");

		gotoxy(55,13);
		//flushall();
		ventry(temp1.supp_name,0);
		gotoxy(22,18);
		ventry(temp1.city,0);
		//flushall();
		gotoxy(55,18);
		ventry(temp1.mob_no,1);
		//flushall();
		gotoxy(22,23);
		gets(temp1.email);
		//flushall();

		gotoxy(20,30);
		//textcolor(RED+BLINK);
		printf("S");
		//textcolor(WHITE);
		gotoxy(21,30);
		printf("ave");
		gotoxy(28,30);
		//textcolor(RED+BLINK);
		printf("C");
		//textcolor(WHITE);
		gotoxy(29,30);
		printf("ancel");
		gotoxy(18,36);
		printf("Press First charecter for the operation : ");
		ch=getch();
		if(ch=='s' || ch=='S')
		{
			fprintf(fp,"%d %s %s %s %s\n\n",temp1.supp_id,temp1.supp_name,temp1.mob_no,temp1.city,temp1.email);
			fprintf(fp,"\n");
			//flushall();
			system("cls");
			gotoxy(20,20);
			printf("Supplier Added successfully!!!!!");
			//textcolor(10);
			gotoxy(20,25);
			printf("More entries  [y/n]");
			ch=getche();
		}
	   }
	   fclose(fp);

}
//=========FOR SUPPLIER DISPLAY LIST ==========
void supp_list()
{
 char ch;
 int j;
 system("cls");
	   ptr1=fopen("supplier.dat","r");
	   if(ptr1==NULL)
	   {
		printf("\n\t Can not open File! ");
		exit(0);
	   }
	   system("cls");
	   box();
	   t();
	   //textcolor(GREEN+BLINK);
	   gotoxy(8,48);
	   printf("Press Anykey to go to SUPPLIER MENU !!!");
	   //textcolor(GREEN);
	   lbox();
	   gotoxy(30,8);
	   printf(" SUPPLIER LIST ");
	   //textcolor(WHITE);
	   gotoxy(5,10);
	   printf("ID.  SUPPLIER NAME.      PH.NO.     CITY.         EMAIL");
	   gotoxy(4,12);
	   i=14;
	   printf("=================================================================");
	   while(fscanf(ptr1,"%d %s %s %s %s",&temp1.supp_id,temp1.supp_name,temp1.city,temp1.mob_no,temp1.email)!=EOF)
	   {
		gotoxy(4,i);
		printf(" %d",temp1.supp_id);
		gotoxy(9,i);
		printf(" %s",temp1.supp_name);
		gotoxy(29,i);
		printf(" %s",temp1.city);
		gotoxy(41,i);
		printf(" %s",temp1.mob_no);
		gotoxy(54,i);
		printf(" %s",temp1.email);
		i=i+2;
	   }
	   getche();
}
//======================search supplier==================
void search()
{
  int ch;

	do
	 {
	   system("cls");
	   //textcolor(WHITE);
	   gotoxy(17,10);
	   printf(" Two options Available for searching ");
	   gotoxy(15,15);
	   printf("Search by");
	   gotoxy(25,15);
	   //textcolor(RED+BLINK);
	   printf("I");
	   //textcolor(WHITE);
	   gotoxy(26,15);
	   printf("D number");

	   gotoxy(15,18);
	   printf("Search by");
	   gotoxy(25,18);
	   //textcolor(RED+BLINK);
	   printf("N");
	   //textcolor(WHITE);
	   gotoxy(26,18);
	   printf("ame");

	   gotoxy(15,21);
	   //textcolor(RED+BLINK);
	   printf("R");
	   //textcolor(WHITE);
	   gotoxy(16,21);
	   printf("eturn");
	   main_box();
	   gotoxy(17,24);
	   printf("Press First charecter for the operation : ");
	   ch=toupper(getche());
	   switch(ch)
	   {
		case 'I':
			animation();
			search_id();

			break;
		case 'N':
			animation();
			search_name();
			break;
		case 'R':
			animation();
			supplier();
			break;
		default:
			gotoxy(22,18);
			printf("You entered wrong choice!!!!!");
			getch();
	   }
	   }while(ch!='R');

}
//=============================== Search by id =============================
void search_id()
{
  int id;
  FILE *fp;

	   fp=fopen("supplier.dat","r");
	   if(fp==NULL)
	   {
	     printf("file can't open!!!!");

	   }
	   system("cls");
	   box();
	   gotoxy(13,8);
	   printf("Enter id to be searched:");
	   scanf("%d",&id);
	   gotoxy(20,35);
	   //textcolor(YELLOW);
	   printf("Press Any key to Return Back Menu ....");
	   gotoxy(12,14);
	   printf("ID.  SUPPLIER NAME.   CITY.     PH.NO.       EMAIL");
	   gotoxy(12,16);
	   i=18;
	   printf("==============================================================");
	   while(fscanf(fp,"%d %s %s %s %s",&temp1.supp_id,temp1.supp_name,temp1.mob_no,temp1.city,temp1.email)!=EOF)
	   {
		if(temp1.supp_id==id)
		{
			gotoxy(10,i);
			printf(" %d",temp1.supp_id);
			gotoxy(15,i);
			printf(" %s",temp1.supp_name);
			gotoxy(30,i);
			printf(" %s",temp1.city);
			gotoxy(40,i);
			printf(" %s",temp1.mob_no);
			gotoxy(53,i);
			printf(" %s",temp1.email);
			i++;
			break;
		}
	   }
	   if(temp1.supp_id!=id)
	   {
		gotoxy(20,30);
		printf("Record not found!");
	   }
	   fclose(fp);
	   getche();
}
//============================ Search by name =============================
void search_name()
{
  char name[20];
  FILE *fp;

	   fp=fopen("supplier.dat","r");
	   if(fp==NULL)
	   {
	     printf("file can't open!!!!");

	   }
	   system("cls");
	   box();
	   fp=fopen("supplier.dat","rb");
	   gotoxy(13,8);
	   printf(" Enter Supplier Name to be searched : ");
	   scanf("%s",&name);
	   gotoxy(20,35);
	   //textcolor(YELLOW);
	   printf("Press Any key to Return Back Menu ....");
	   gotoxy(12,14);
	   printf("ID. SUPPLIER NAME.   CITY.     PH.NO.       EMAIL");
	   gotoxy(12,16);
	   i=18;
	   printf("==============================================================");

	   while(fscanf(fp,"%d %s %s %s %s",&temp1.supp_id,temp1.supp_name,temp1.mob_no, temp1.city,temp1.email)!=EOF)
	   {
		if(strcmp(temp1.supp_name,name)==0)
		{
			gotoxy(11,i);
			printf(" %d",temp1.supp_id);
			gotoxy(15,i);
			printf(" %s",temp1.supp_name);
			gotoxy(30,i);
			printf(" %s",temp1.city);
			gotoxy(40,i);
			printf(" %s",temp1.mob_no);
			gotoxy(53,i);
			printf(" %s",temp1.email);
			i++;
			break;
		}
	   }
	   if(strcmp(temp1.supp_name,name)!=0)
	   {
		gotoxy(20,30);
		//textcolor(YELLOW);
		printf("Record not found!!!");
	   }
	   fclose(ptr1);
	   getche();
}
//============supp update=================
void sup_update()
{
  int i;
  char ch;
  int sid;
  FILE *ft;
  system("cls");
  box();
	   ptr1=fopen("supplier.dat","rb+");
	   if(ptr1==NULL )
	   {
		printf("\n\t Can not open file!! ");
		exit(0);
	   }
	   lbox();
	   gotoxy(30,8);
	   printf(" Modifying Supplier ");
	   gotoxy(12,13);
	   printf("Enter supplier ID :  ");
	  // //flushall();
	   scanf("%d",&sid);
	   gotoxy(12,15);

		ft=fopen("temp.dat","w");
		if(ft==NULL)
		{
			printf(" Can not open file");
			exit(1);
		}
		else
		{
			while(fscanf(ptr1,"%d %s %s %s %s",&temp1.supp_id,temp1.supp_name,temp1.mob_no, temp1.city,temp1.email)!=EOF)
			{
				if(temp1.supp_id==sid)
				{
					gotoxy(18,17);
					printf(" Existing Record  ");
					gotoxy(10,19);
					printf("%d\t %s \t%s \t%s \t%s",temp1.supp_id,temp1.supp_name,temp1.mob_no, temp1.city,temp1.email);
					gotoxy(12,22);
					printf("Enter New Name       : ");
					//flushall();
					ventry(temp1.supp_name,0);
					gotoxy(12,24);
					printf("Enter New mobile no  : ");
					//flushall();
					ventry(temp1.mob_no,1);
					gotoxy(12,26);
					printf("Enter New City       : ");
					//flushall();
					ventry(temp1.city,0);
					gotoxy(12,28);
					printf("Enter New email      : ");
					//flushall();
					ventry(temp1.email,2);
					gotoxy(20,32);
					//textcolor(RED+BLINK);
					printf("U");
					gotoxy(21,32);
					//textcolor(WHITE);
					printf("pdate");
					gotoxy(30,32);
					//textcolor(RED+BLINK);
					printf("C");
					gotoxy(31,32);
					//textcolor(WHITE);
					printf("ancel");
					gotoxy(18,36);
					printf("Press First charecter for the operation : ");
					ch=getch();
					if(ch=='u' || ch=='U')
					{
					    fprintf(ft,"%d %s %s %s %s\n",temp1.supp_id,temp1.supp_name,temp1.mob_no,temp1.city,temp1.email);
					    //flushall();
					    gotoxy(20,38);
					    printf("Supplier updated successfully...");
					    remove("supplier.dat");
					    rename("temp.dat","supplier.dat");

					}
				}
			else
			{
				fprintf(ft,"%d %s %s %s %s\n",temp1.supp_id,temp1.supp_name,temp1.mob_no,temp1.city,temp1.email);
				fflush(stdin);
			}
		}

	   fclose(ft);
	   fclose(ptr1);
	   }
}
//===============================END OF SUPPLIER FUNCTION===================
//========FOR CUSTOMER ENTRY=================
void cust_entry()
{
 char ch;
 int id;
 FILE *fp;
 system("cls");
	   fp=fopen("customer.dat","a");
	   if(fp==NULL)
	   {
		printf("\n Can not open file!!");
		exit(0);
	   }
	   system("cls");
	   ch='y';
	   while(ch=='y')
	   {
		system("cls");
		//textcolor(14);
		t();
		box();
		lbox();
		gotoxy(30,8);
		printf(" CUSTOMER ENTRY ");
		gotoxy(8,13);
		//flushall();
		temp_c.cust_id=getcust_id();
		printf("CUSTOMER ID :%d",temp_c.cust_id);
		//ventry(temp_c.cust_id,1);
		//flushall();
		gotoxy(39,13);
		printf("CUSTOMER NAME : ");
		gotoxy(8,18);
		printf("CITY        : ");
		gotoxy(39,18);
		printf("CONTACT NO.   : ");
		gotoxy(8,23);
		printf("EMAIL ID    : ");

		gotoxy(55,13);
		//flushall();
		ventry(temp_c.cust_name,0);
		gotoxy(22,18);
		ventry(temp_c.city,0);
		//flushall();
		gotoxy(55,18);
		ventry(temp_c.mob_no,1);
		//flushall();
		gotoxy(22,23);
		gets(temp_c.email);
		//flushall();

		gotoxy(20,30);
		//textcolor(RED+BLINK);
		printf("S");
		//textcolor(WHITE);
		gotoxy(21,30);
		printf("ave");
		gotoxy(28,30);
		//textcolor(RED+BLINK);
		printf("C");
		//textcolor(WHITE);
		gotoxy(29,30);
		printf("ancel");
		gotoxy(18,36);
		printf("Press First charecter for the operation : ");
		ch=getch();
		if(ch=='s' || ch=='S')
		{
			fprintf(fp,"%d %s %s %s %s\n",temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email);
			fprintf(fp,"\n");
			fflush(stdin);
			system("cls");
			gotoxy(20,20);
			printf("Customer Added Successfully!!!!!");
			//textcolor(10);
			gotoxy(20,25);
			printf("More entries  [y/n] ");
			ch=getche();

		}
	   }
	   fclose(fp);
}

//=========FOR CUSTOMER DISPLAY LIST ==========
void cust_list()
{
 char ch;
 system("cls");
	   ptr1=fopen("customer.dat","r");
	   if(ptr1==NULL)
	   {
		printf("\n\t Can not open File! ");
		exit(0);
	   }
	   system("cls");
	   box();
	   //textcolor(GREEN+BLINK);
	   gotoxy(8,48);
	   printf("Press Anykey to go to CUSTOMER MENU!!!");
	   //textcolor(GREEN);
	   lbox();
	   gotoxy(30,8);
	   printf(" CUSTOMER LIST ");
	   //textcolor(WHITE);
	   i=14;
	   gotoxy(5,10);
	   printf(" ID. CUSTOMER NAME.    CITY.     MOBILE.NO.      EMAIL");
	   gotoxy(4,12);
	   printf("==============================================================");
	   while(fscanf(ptr1,"%d %s %s %s %s",&temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email)!=EOF)
	   {
		gotoxy(4,i);
		printf(" %d",temp_c.cust_id);
		gotoxy(11,i);
		printf(" %s",temp_c.cust_name);
		gotoxy(28,i);
		printf(" %s",temp_c.city);
		gotoxy(40,i);
		printf(" %s",temp_c.mob_no);
		gotoxy(53,i);
		printf(" %s",temp_c.email);
		i=i+2;
	   }
	   getche();
}
//======================search CUSTOMER==================
void cust_search()
{
  int ch;

	do
	 {
	   system("cls");
	   //textcolor(WHITE);
	   gotoxy(17,10);
	   printf(" Two options Available for searching ");
	   gotoxy(15,15);
	   printf("Search by");
	   gotoxy(25,15);
	   //textcolor(RED+BLINK);
	   printf("I");
	   //textcolor(WHITE);
	   gotoxy(26,15);
	   printf("D number");

	   gotoxy(15,18);
	   printf("Search by");
	   gotoxy(25,18);
	   //textcolor(RED+BLINK);
	   printf("N");
	   //textcolor(WHITE);
	   gotoxy(26,18);
	   printf("ame");

	   gotoxy(15,21);
	   //textcolor(RED+BLINK);
	   printf("R");
	   //textcolor(WHITE);
	   gotoxy(16,21);
	   printf("eturn");
	   main_box();
	   gotoxy(17,24);
	   printf("Press First charecter for the operation : ");
	   ch=toupper(getche());
	   switch(ch)
	   {
		case 'I':
			animation();
			search_cid();

			break;
		case 'N':
			animation();
			search_cname();
			break;
		case 'R':
			animation();
			customer();
			break;
		default:
			gotoxy(22,18);
			printf("You entered wrong choice!!!!!");
			getch();
	   }
	   }while(ch!='R');
       getche();
}
//===========================Search by CustomerId=========================
void search_cid()
{
  int id;
  system("cls");
  box();
	   ptr1=fopen("customer.dat","rb");
	   gotoxy(13,8);
	   printf("\xDB\xDB\xB2  Enter id to be searched:");
	   scanf("%d",&id);
	   //textcolor(GREEN);
	   //textcolor(WHITE);
	   i=18;
	   gotoxy(9,15);
	   printf(" ID. CUSTOMER NAME.    CITY.     MOBILE.NO.      EMAIL");
	   gotoxy(8,16);
	   printf("==============================================================");
	   while(fscanf(ptr1,"%d %s %s %s %s",&temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email)!=EOF)
	   {
		if(temp_c.cust_id==id)
		{
			gotoxy(8,i);
			printf(" %d",temp_c.cust_id);
			gotoxy(15,i);
			printf(" %s",temp_c.cust_name);
			gotoxy(28,i);
			printf(" %s",temp_c.city);
			gotoxy(40,i);
			printf(" %s",temp_c.mob_no);
			gotoxy(54,i);
			printf(" %s",temp_c.email);
			gotoxy(20,35);
			//textcolor(YELLOW);
			printf("Press Any key to go to CUSTOMER MENU ...........");
			break;
		}
	   }
	   if(temp_c.cust_id!=id)
	   {
		gotoxy(20,30);
		printf("Record not found!");
	   }
	   fclose(ptr1);
       getche();
}
/*****************************search by CUSTOMERname******************************/
void search_cname()
{
  char name[20];
  system("cls");
  box();
	   ptr1=fopen("customer.dat","rb");
	   gotoxy(12,8);
	   printf("\xDB\xDB\xB2  Enter Customer Name to be searched:");
	   scanf("%s",&name);
	   //textcolor(GREEN);
	   //textcolor(WHITE);
	   i=18;
	   gotoxy(9,15);
	   printf(" ID. CUSTOMER NAME.    CITY.     MOBILE.NO.      EMAIL");
	   gotoxy(8,16);
	   printf("==============================================================");
	   while(fscanf(ptr1,"%d %s %s %s %s",&temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email)!=EOF)
	   {
		if(strcmp(temp_c.cust_name,name)==0)
		{
			gotoxy(8,i);
			printf(" %d",temp_c.cust_id);
			gotoxy(15,i);
			printf(" %s",temp_c.cust_name);
			gotoxy(28,i);
			printf(" %s",temp_c.city);
			gotoxy(40,i);
			printf(" %s",temp_c.mob_no);
			gotoxy(54,i);
			printf(" %s",temp_c.email);
			gotoxy(20,35);
			//textcolor(YELLOW);
			printf("Press Any key to go to CUSTOMER MENU ...........");
			break;
		}
	   }
	   if(strcmp(temp_c.cust_name,name)!=0)
	   {
		gotoxy(5,10);
		//textcolor(YELLOW);
		printf("Record not found!");
	   }
	   fclose(ptr1);
	getche();
}
//============CUSTOMER update=================
void cust_update()
{
  int i;
  char ch;
  int cid;
  FILE *ft;
  system("cls");
  box();
	   ptr1=fopen("customer.dat","rb+");
	   if(ptr1==NULL)
	   {
		printf("\n\t Can not open file!! ");
		exit(0);
	   }
	   lbox();
	   gotoxy(30,8);
	   printf(" Modifying customer ");
	   gotoxy(12,13);
	   printf("Enter the CUSTOMER ID : ");
	   scanf("%d",&cid);
	   gotoxy(12,15);

		ft=fopen("temp.txt","w");
		if(ft==NULL)
		{
			printf("\n Can not open file");
			exit(0);
		}
		else
		{

			while(fscanf(ptr1,"%d %s %s %s %s",&temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email)!=EOF)
			{
				if(temp_c.cust_id==cid)
				{
					gotoxy(25,17);
					printf("*** Existing Record ***");
					gotoxy(10,19);
					printf("%d\t %s \t%s \t%s \t%s",temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email);
					gotoxy(12,22);
					printf("Enter New Name         : ");
					//flushall();
					ventry(temp_c.cust_name,0);
					gotoxy(12,24);
					printf("Enter New mobile no    : ");
					//flushall();
					ventry(temp_c.mob_no,1);
					gotoxy(12,26);
					printf("Enter New City         : ");
					//flushall();
					ventry(temp_c.city,0);
					gotoxy(12,28);
					printf("Enter New email        : ");
					//flushall();
					scanf("%s",temp_c.email);
					gotoxy(20,32);
					//textcolor(RED+BLINK);
					printf("U");
					gotoxy(21,32);
					//textcolor(WHITE);
					printf("pdate");
					gotoxy(30,32);
					//textcolor(RED+BLINK);
					printf("C");
					gotoxy(31,32);
					//textcolor(WHITE);
					printf("ancel");
					gotoxy(18,35);
					printf("Press First charecter for the operation : ");
					ch=getche();
					if(ch=='u' || ch=='U')
					{
					fprintf(ft,"%d %s %s %s %s\n",temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email);
				       //	fprintf(ft,"\n");
					fflush(stdin);
					gotoxy(20,36);
					printf("Customer updated successfully...");
					remove("customer.dat");
					rename("temp.txt","customer.dat");
					}					}
					else
					{
					fprintf(ft,"%d %s %s %s %s\n",temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email);
					fflush(stdin);
					}
				  }


	   fclose(ft);
	   fclose(ptr1);
      }

}

//============================ END OF CUSTOMER FUNCTION ===================
//============================ FOR MEDICINE PURCHASE    ===================
void medi_entry()
{
  char ch,id[6];
//  struct date d;
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
  int f;
  FILE *fp;
  system("cls");
	  //getdate(&d);

	  ptrp_r=fopen("purreport.dat","a");
	  ch='Y';
	  while(ch=='Y')
	  {
		system("cls");
		box();
		//textcolor(14);
//		t();  // THIS FUN IS USED FOR DISPLAY DATE & TIME.......
		lbox();
		gotoxy(30,8);
		////textcolor(GREEN+BLINK);
		printf(" MEDICINE PURSHASE  ");
		{
			//textcolor(WHITE);
			gotoxy(7,11);
			printf("MEDICINE ID    : ");

			gotoxy(40,11);
			printf("MEDICINE NAME  : ");

			gotoxy(7,14);
			printf("ENTER RACK NO  : ");

			gotoxy(40,14);
			printf("CABNIT NO      : ");

			gotoxy(7,18);
			printf("COMPANY NAME   : ");

			gotoxy(40,18);
			printf("SUPPLIER NAME  : ");

			gotoxy(7,21);
			printf("UNIT COST   Rs.:  ");

			gotoxy(40,21);
			printf("SALE COST   Rs.: ");

			gotoxy(7,24);
			printf("QUANTITY       :  ");

			gotoxy(7,27);
			printf("MFG.DATE(dd-mm-yyyy): ");

			gotoxy(7,29);
			printf("EXP.DATE(dd-mm-yyyy): ");

			gotoxy(25,11);
			ventry(temp.id,1);
			strcpy(id,temp.id);

			fp=fopen("medical.dat","r");
			while((fread(&temp,sizeof(temp),1,fp))==1)
			{

			if(strcmp(id,temp.id)==0)
			{
				f=1;
				break;
			}
			}
			fclose(fp);
			if(f==1)
			{
				gotoxy(20,31);
				printf("ID Allready Exists");
				getche();
				system("cls");
				medi_entry();
			}
			else
			{
			ptr=fopen("medical.dat","a+b");
			strcpy(temp.id,id);
			strcpy(p_r.medi_id,temp.id);
			}
			//flushall();
			gotoxy(58,11);
			ventry(temp.medi_name,0);
			strcpy(p_r.medir_name,temp.medi_name);
			//flushall();
			gotoxy(25,14);
			ventry(a,1);
			temp.rack= atoi(a);//atoi() used for convert str to int.
			//flushall();
			gotoxy(58,14);
			ventry(temp.cabnit,2);
			//flushall();
			gotoxy(25,18);
			ventry(temp.comp_name,0);
			//flushall();
			gotoxy(58,18);
			ventry(temp.supp_name,0);
			strcpy(p_r.supp_name,temp.supp_name);
			//flushall();
			gotoxy(25,21);
			ventry(a,1);
			temp.unit= atof(a);
			//flushall();
			p_r.rate=temp.unit;
			gotoxy(58,21);
			ventry(a,1);
			temp.sale= atof(a);
			//flushall();
			gotoxy(25,24);
			ventry(a,1);
			temp.quantity= atoi(a);
			p_r.qty=temp.quantity;
			//flushall();
			gotoxy(29,27);
			//flushall();
			ventry(temp.manu_date,1);
			gotoxy(29,29);
			//flushall();
			ventry(temp.exp_date,1);

			gotoxy(7,31);
			printf("==========================================================");
			temp.total=temp.quantity*temp.sale;

			//textcolor(10);
			gotoxy(10,33);
			printf("TOTAL SALE COST = Rs. %.2f",temp.total);
			temp.cost=(temp.unit*temp.quantity);
			gotoxy(40,33);
			printf("TOTAL UNIT COST = Rs. %.2f",temp.cost);
			p_r.total=temp.cost;
			p_r.sDay=now->tm_mday;
			p_r.sMonth=now->tm_mon;
			p_r.sYear=now->tm_year;
		 }
		gotoxy(20,35);
		//textcolor(RED+BLINK);
		printf("S");
		//textcolor(WHITE);
		gotoxy(21,35);
		printf("ave");
		gotoxy(28,35);
		//textcolor(RED+BLINK);
		printf("C");
		//textcolor(WHITE);
		gotoxy(29,35);
		printf("ancel");
		gotoxy(18,38);
		printf("Press First charecter for the operation : ");


		ch=toupper(getche());

		if(ch=='S')
		{
			fwrite(&temp,sizeof(temp),1,ptr);
			fflush(stdin);
			//textcolor(10);
			fprintf(ptrp_r,"%s %s %s %d %.2f %.2f %d %d %d\n",p_r.medi_id,p_r.medir_name,p_r.supp_name,p_r.qty,p_r.rate,p_r.total,p_r.sDay,p_r.sMonth,p_r.sYear);
			system("cls");
			gotoxy(20,20);
			printf("Medicine Added sucessfully!!!!!!");
			gotoxy(20,25);
			printf("More entries  [y/n]");
			ch=toupper(getche());
		       /*	if(ch=='Y')
			{
				system("cls");
				medi_entry();
			}*/
		}

	   }
	   fclose(ptr);
	   fclose(ptrp_r);
}
//===========FOR MEDICINE SALE=========================
void medi_sale()
{
  struct bill bil;
  //struct date d;
  time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
  int j,n,i,a,billno;
  int d1,m,y;
  float b,total,rate;
  char tar[30],ch,mediname[30],c_name[30],cname[30];
  FILE *fp,*fpc;
  int count=0;
  //getdate(&d);
  d1=now->tm_mday;
  m=now->tm_mon;
  y=now->tm_year;
	   ch='y';
	   while(ch=='y')
	   {
		fp = fopen("dbbill.dat","a");
		ptr1 = fopen("customer.dat","r");
		ptr = fopen("medical.dat","r");
		ptrs_r=fopen("saleRpt.dat","a");
		ptrpr_r=fopen("profitRpt.dat","a");
		system("cls");
		box();
		for(i=3;i<=45;i++)      //This 'FOR' loop will print asteriks 'I'
		{                       //vertically till the 3th row is reached.
		gotoxy(50,i);
		printf("%c",219);
		}
		i=9;
		gotoxy(52,7);
		printf("Cust_ID    Cust_Name");
		//flushall();
		while(fscanf(ptr1,"%d %s %s %s %s",&temp_c.cust_id,temp_c.cust_name,temp_c.mob_no, temp_c.city,temp_c.email)!=EOF)
		{
			gotoxy(53,i);
			printf("%d",temp_c.cust_id);
			gotoxy(64,i);
			printf("%s",temp_c.cust_name);
			i+=2;
		}

		gotoxy(9,7);
		printf("ENTER MEDICINE ID TO BE SOLD  : ");
		ventry(tar,1);
		//scanf("%s",&tar);
		j=0;
		while((fread(&temp,sizeof(temp),1,ptr))==1)
		{
			if((strcmp(temp.id,tar)<0) || (strcmp(temp.id,tar)>0))
			{
				x[j] = temp;
				j++;
			}
			else if((strcmp(temp.id,tar)==0))
			{

				gotoxy(8,10);
				printf(" Medicine Name        : %s",temp.medi_name);
				gotoxy(8,12);
				printf(" Quantity in stock    : %d",temp.quantity);
				gotoxy(8,14);
				printf(" Sales price          : %.2f",temp.sale);
				gotoxy(8,16);
				printf("Enter bill number     : ");
				//flushall();
				ventry(bil.billno,1);
				//scanf("%s",&bil.billno);
				gotoxy(8,18);
				printf("Enter customer Name   : ");
				//flushall();
				ventry(c_name,0);
				//scanf("%s",&c_name);
				gotoxy(8,20);
				printf("Quantity want to sale : ");
				//ventry(a,1);
				scanf("%d",&a);

				pr_r.profit=(temp.sale-temp.unit)*a;
				x[j]=temp;
				x[j].quantity=(x[j].quantity-a);
				x[j].total=(x[j].quantity*temp.sale);
				x[j].cost=(x[j].quantity*temp.unit);
				x[j].bye=(x[j].sale*a);
				b=x[j].bye;
				x[j].qty=a;
				j++;
				count++;
				strcpy(bil.cname,c_name);
				strcpy(s_r.cust_name,c_name);
				strcpy(bil.mediname,temp.medi_name);
				bil.medi_qty=a;
				bil.medi_rate=temp.sale;
				bil.total=temp.sale*a;

				bil.day=d1;
				bil.month=m;
				bil.year=y;

				fprintf(fp,"%s %s %s %d %.2f %.2f %d %d %d\n",bil.billno,bil.cname,bil.mediname,bil.medi_qty,bil.medi_rate,bil.total,bil.day,bil.month,bil.year);
				fflush(stdin);

				fclose(fp);

				s_r.sDay=d1;
				s_r.sMonth=m;
				s_r.sYear=y;
				strcpy(s_r.medi_id,tar);
				strcpy(s_r.medir_name,temp.medi_name);
				s_r.qty=a;
				s_r.rate=temp.sale;
				s_r.total=temp.sale*a;

				//sale report
				fprintf(ptrs_r,"%s %s %s %d %.2f %.2f %d %d %d\n",s_r.medi_id,s_r.medir_name,s_r.cust_name,s_r.qty,s_r.rate,s_r.total,s_r.sDay,s_r.sMonth,s_r.sYear);
				fflush(stdin);
				fclose(ptrs_r);
				//profit report

				pr_r.sDay=d1;
				pr_r.sMonth=m;
				pr_r.sYear=y;
				strcpy(pr_r.medi_id,tar);
				strcpy(pr_r.medir_name,temp.medi_name);
				pr_r.qty=a;
				pr_r.rate=temp.sale;
				pr_r.unit=temp.unit;
				fprintf(ptrpr_r,"%s %s %d %d %d %d %.2f %.2f  %.2f\n",pr_r.medi_id,pr_r.medir_name,d1,pr_r.sMonth,pr_r.sYear,pr_r.qty,pr_r.unit,pr_r.rate,pr_r.profit);
				fflush(stdin);
				fclose(ptrpr_r);

			}
		}
		if (count==0)
		{
			system("cls");
			gotoxy(33,10);
			printf("Not in stock!!!!!");
			getch();
			return;
		}
		fclose(ptr1);
		fclose(ptr);
		n = j;
		system("cls");
		ptr=fopen("medical.dat","wb");
		for(i=0; i<n; i++)
		fwrite(&x[i],sizeof(x[i]),1,ptr);
		fclose(ptr);
		system("cls");
		box();
		gotoxy(8,15);
		printf("* Price paid by customer = %.2f",b);
		gotoxy(8,17);
		printf("* Quantity sold          = %d",a);
		getch();
		gotoxy(10,20);
		printf("more enteries=(y/n) :");
		ch=getche();
	   }

}
//===========================MEDICINE STOCK=====================================
void stock()
{
  char ch;
  int i,c;
	   do
	   {
		system("cls");
		ptr1=fopen("medical.dat","r");
		if(ptr1==NULL)
		{
			printf("\n\t Can not open File! ");
			exit(1);
		}
		system("cls");
		box();
		lbox();
		//textcolor(GREEN);
		gotoxy(30,8);
		////textcolor(GREEN+BLINK);
		printf(" STOCK OF MEDICINE ");
		//textcolor(WHITE);
		i=14;
		gotoxy(9,10);
		printf("ID.   MEDICINE NAME.    QTY     Supplier Name     Exp.Date");
		gotoxy(9,12);
		printf("==================================================================\n");

		while((fread(&temp,sizeof(temp),1,ptr1))==1)
		{
			gotoxy(9,i);
			printf(" %s",temp.id);
			gotoxy(15,i);
			printf(" %s",temp.medi_name);
			gotoxy(32,i);
			printf(" %d",temp.quantity);
			gotoxy(43,i);
			printf(" %s",temp.supp_name);
			gotoxy(60,i);
			printf(" %s",temp.exp_date);
			i++;
		}
		gotoxy(10,42);
		printf("Press [1] for Update Medicine Stock  & [0] for main menu ");
		c = (getche());
		switch (c)
		{
			case '0':animation();
				 main_menu();
				 break;
			case '1':update_stock();
				 break;
		}

	   }while(c != '1');
	   getche();
}
//=============================== FOR MEDICINE SEARCH ====================
void medi_search()
{
  char mid[6];
  int i,c;
  system("cls");
	   ptr1=fopen("medical.dat","r");
	   if(ptr1==NULL)
	   {
		printf("\n\t Can not open File! ");
		exit(0);
	   }
	   system("cls");
	   box();

	   gotoxy(10,7);
	   printf("Enter Medicine Id to be searched : ");
	   scanf("%s",&mid);
	   system("cls");
	   box();
	   lbox();
	   //textcolor(GREEN);
	   gotoxy(30,8);
	   //textcolor(GREEN+BLINK);
	   printf(" MEDICINE ");
	   //textcolor(WHITE);
	   i=14;
	   gotoxy(9,10);
	   printf("ID.   MEDICINE NAME.    QTY     Supplier Name     Exp.Date");
	   gotoxy(9,12);
	   printf("==================================================================\n");
	   while((fread(&temp,sizeof(temp),1,ptr1))==1)
	   {
		if(strcmp(mid,temp.id)==0)
		{
			gotoxy(9,i);
			printf(" %s",temp.id);
			gotoxy(15,i);
			printf(" %s",temp.medi_name);
			gotoxy(32,i);
			printf(" %d",temp.quantity);
			gotoxy(43,i);
			printf(" %s",temp.supp_name);
			gotoxy(60,i);
			printf(" %s",temp.exp_date);
			i++;
			break;
		}

	   }
	   if(strcmp(mid,temp.id)!=0)
	   {
		gotoxy(20,20);
		printf("Not in Stock.....");
	   }
	   getche();

}
//============================ FOR MEDICINE UPDATE =====================
void update_stock()
{
  char mid[6];
  int j,a,count=0,n;
  system("cls");
	   ptr=fopen("medical.dat","rb");
	   if(ptr==NULL)
	   {
		printf("\n\t Can not open File! ");
		exit(0);
	   }
	   system("cls");
	   box();
	   gotoxy(20,45);
	   printf("Press Enter to go to MENU ...........");
	   //textcolor(GREEN);
	   gotoxy(27,8);
	   ////textcolor(GREEN+BLINK);
	   printf(" UPDATE MEDICINE QUANTITY ");
	   //textcolor(WHITE);
	   gotoxy(9,10);
	   printf("Enter medicine id to be update qty: ");
	   scanf("%s",&mid);
	   j=0;

	   while((fread(&temp,sizeof(temp),1,ptr))==1)
	   {
		if((strcmp(temp.id,mid)<0) || (strcmp(temp.id,mid)>0))
		{
			x[j] = temp;
			j++;
		}
		else
		{
			gotoxy(8,12);
			printf("Medicine Name     : %s",temp.medi_name);
			gotoxy(8,14);
			printf("Quantity in stock : %d",temp.quantity);
			gotoxy(8,16);
			printf("Quantity want to update : ");
			scanf("%d",&a);
			x[j]=temp;
			x[j].quantity=(x[j].quantity+a);
			x[j].total=(x[j].quantity*temp.sale);
			x[j].cost=(x[j].quantity*temp.unit);
			x[j].bye=(x[j].sale*a);
			x[j].qty=a;
			j++;
			count++;
		}
	   }
	   if (count==0)
	   {
		 system("cls");
		 gotoxy(33,10);
		 printf("Not in stock!!!!!!");
		 getch();
		 return;
	   }
	   fclose(ptr);
	   n = j;
	   system("cls");
	   ptr=fopen("medical.dat","wb");
	   for(i=0; i<n; i++)
	   fwrite(&x[i],sizeof(x[i]),1,ptr);
	   fclose(ptr);
}
//===================== view report =============================/
void sale_rpt()
{
  char ch;
  int j;
  system("cls");
	   ptrs_r=fopen("saleRpt.dat","r");
	   if(ptrs_r==NULL)
	   {
		printf("\n\t Can not open File! ");
		exit(0);
	   }
	   system("cls");
	   box();
	   gotoxy(20,50);
	   printf("Press any key to go to REPORT MENU ...........");
	   lbox();
	   //textcolor(GREEN);
	   gotoxy(30,8);
	   ////textcolor(GREEN+BLINK);
	   printf("Sales Report");
	   //textcolor(WHITE);
	   gotoxy(7,10);
	   printf("ID. Medicine Name.  Customer Name.   Qty.  Rate.  Total.   Date");
	   gotoxy(7,12);
	   printf("===================================================================");
	   j=14;
	   while(fscanf(ptrs_r,"%s %s %s %d %f %f %d %d %d\n",s_r.medi_id,s_r.medir_name,s_r.cust_name,&s_r.qty,&s_r.rate,&s_r.total,&s_r.sDay,&s_r.sMonth,&s_r.sYear)!=EOF)
	   {
		gotoxy(6,j);
		printf("%s",s_r.medi_id);
		gotoxy(11,j);
		printf("%s",s_r.medir_name);
		gotoxy(28,j);
		printf("%s",s_r.cust_name);
		gotoxy(44,j);
		printf("%d",s_r.qty);
		gotoxy(50,j);
		printf("%.2f",s_r.rate);
		gotoxy(57,j);
		printf("%.2f",s_r.total);
		gotoxy(65,j);
		printf("%d-%d-%d",s_r.sDay,s_r.sMonth,s_r.sYear);
		j=j+2;
	   }
	   getche();
}
//======================= VIEW PURCHASE REPORT ===========================
void pur_rpt()
{
  char ch;
  int j;
  system("cls");
  t();
  box();
	   ptrp_r=fopen("purreport.dat","r");
	   if(ptrp_r==NULL)
	   {
		printf("\n\t Can not open File! ");
		exit(0);
	   }
	   gotoxy(20,50);
	   printf("Press Enter to go to REPORT MENU ...........");
	   lbox();
	   //textcolor(GREEN);
	   gotoxy(30,8);
	   printf("Purchase Report");
	   //textcolor(WHITE);
	   gotoxy(7,10);
	   printf("ID. Medicine Name.  Supplier Name.   Qty.  Rate.  Total.   Date");
	   gotoxy(7,12);
	   printf("===================================================================");
	   j=14;
	   while(fscanf(ptrp_r,"%s %s %s %d %f %f %d %d %d\n",p_r.medi_id,p_r.medir_name,p_r.supp_name,&p_r.qty,&p_r.rate,&p_r.total,&p_r.sDay,&p_r.sMonth,&p_r.sYear)!=EOF)
	   {
		gotoxy(6,j);
		printf("%s",p_r.medi_id);
		gotoxy(11,j);
		printf("%s",p_r.medir_name);
		gotoxy(28,j);
		printf("%s",p_r.supp_name);
		gotoxy(44,j);
		printf("%d",p_r.qty);
		gotoxy(50,j);
		printf("%.2f",p_r.rate);
		gotoxy(57,j);
		printf("%.2f",p_r.total);
		gotoxy(65,j);
		printf("%d-%d-%d",p_r.sDay,p_r.sMonth,p_r.sYear);
		j+=2;
	   }
	   getche();
}
//========================= report of profit ===========================
void profit_rpt()
{
  char ch;
  int j;
  system("cls");
  t();
  box();
	   ptrpr_r=fopen("profitRpt.dat","r");
	   if(ptrpr_r==NULL)
	   {
		printf("\n\t Can not open File! ");
	       //	exit(0);
	   }
	   gotoxy(20,50);
	   printf("Press Enter to go to REPORT MENU ...........");
	   lbox();
	   //textcolor(GREEN);
	   gotoxy(30,8);
	   printf("Profit Report");
	   //textcolor(WHITE);
	   gotoxy(7,10);
	   printf("ID. Medicine Name.   Date        Qty.  Unit Price  Sale Price. Profit. ");
	   gotoxy(7,12);
	   printf("===================================================================");
	   j=14;
	   while(fscanf(ptrpr_r,"%s %s %d %d %d %d %f %f %f \n",pr_r.medi_id,pr_r.medir_name,&pr_r.sDay,&pr_r.sMonth,&pr_r.sYear,&pr_r.qty,&pr_r.unit,&pr_r.rate,&pr_r.profit)!=EOF)
	   {
		gotoxy(6,j);

		printf("%s",pr_r.medi_id);
		gotoxy(11,j);
		printf("%s",pr_r.medir_name);
		gotoxy(28,j);
		printf("%d-%d-%d",pr_r.sDay,pr_r.sMonth,pr_r.sYear);
		gotoxy(40,j);
		printf("%d",pr_r.qty);
		gotoxy(48,j);
		printf("%.2f",pr_r.unit);
		gotoxy(60,j);
		printf("%.2f",pr_r.rate);
		gotoxy(70,j);
		printf("%.2f",pr_r.profit);
		gotoxy(10,j);
		printf("%c",124);
		j+=2;

	   }
	   getche();
}

void sale_rpt_daily()
{
  char ch;
  int j,d,m,y;
  float total=0.00;
  system("cls");
	   ptrs_r=fopen("saleRpt.dat","r");
	   if(ptrs_r==NULL)
	   {
		printf("\n\t Can not open File! ");
		exit(0);
	   }
	   system("cls");
	   gotoxy(15,10);
	   printf("Enter Date(dd-mm-yyyy):  ");
	   scanf("%d-%d-%d",&d,&m,&y);
	   system("cls");
	   gotoxy(20,50);
	   printf("Press any key to go to REPORT MENU ...........");
	   box();
	   lbox();
	   //textcolor(GREEN);
	   gotoxy(30,8);
	   ////textcolor(GREEN+BLINK);
	   printf("Sales Report");
	   //textcolor(WHITE);
	   gotoxy(7,10);
	   printf("ID. Medicine Name.  Customer Name.   Qty.  Rate.  Total.   Date");
	   gotoxy(7,12);
	   printf("===================================================================");
	   j=14;
	   while(fscanf(ptrs_r,"%s %s %s %d %f %f %d %d %d\n",s_r.medi_id,s_r.medir_name,s_r.cust_name,&s_r.qty,&s_r.rate,&s_r.total,&s_r.sDay,&s_r.sMonth,&s_r.sYear)!=EOF)
	   {
		if(d==s_r.sDay &&m== s_r.sMonth && y==s_r.sYear)
		{
		gotoxy(6,j);
		printf("%s",s_r.medi_id);
		gotoxy(11,j);
		printf("%s",s_r.medir_name);
		gotoxy(28,j);
		printf("%s",s_r.cust_name);
		gotoxy(44,j);
		printf("%d",s_r.qty);
		gotoxy(50,j);
		printf("%.2f",s_r.rate);
		gotoxy(57,j);
		printf("%.2f",s_r.total);
		gotoxy(65,j);
		printf("%d-%d-%d",s_r.sDay,s_r.sMonth,s_r.sYear);
		j=j+2;
		total=total+s_r.total;
		}
	   }
	   gotoxy(7,42);
	   printf("-------------------------------------------------------------------");
	   gotoxy(45,43);
	   printf("Total:        %.2f",total);
	   getche();
}
void pur_rpt_daily()
{
  char ch;
  int j,d,m,y;
  float total=0.00;

	   ptrp_r=fopen("purreport.dat","r");
	   if(ptrp_r==NULL)
	   {
		printf("\n\t Can not open File! ");
		exit(0);
	   }
	   system("cls");
	   gotoxy(15,10);
	   printf("Enter Date(dd-mm-yyyy):  ");
	   scanf("%d-%d-%d",&d,&m,&y);
	   system("cls");
	   gotoxy(20,50);
	   printf("Press Enter to go to REPORT MENU ...........");
	   t();
	   box();
	   lbox();
	   //textcolor(GREEN);
	   gotoxy(30,8);
	   printf("Purchase Report");
	   //textcolor(WHITE);
	   gotoxy(7,10);
	   printf("ID. Medicine Name.  Supplier Name.   Qty.  Rate.  Total.   Date");
	   gotoxy(7,12);
	   printf("===================================================================");
	   j=14;
	   while(fscanf(ptrp_r,"%s %s %s %d %f %f %d %d %d\n",p_r.medi_id,p_r.medir_name,p_r.supp_name,&p_r.qty,&p_r.rate,&p_r.total,&p_r.sDay,&p_r.sMonth,&p_r.sYear)!=EOF)
	   {
		if(d==p_r.sDay &&m== p_r.sMonth && y==p_r.sYear)
		{
		gotoxy(6,j);
		printf("%s",p_r.medi_id);
		gotoxy(11,j);
		printf("%s",p_r.medir_name);
		gotoxy(28,j);
		printf("%s",p_r.supp_name);
		gotoxy(44,j);
		printf("%d",p_r.qty);
		gotoxy(50,j);
		printf("%.2f",p_r.rate);
		gotoxy(57,j);
		printf("%.2f",p_r.total);
		gotoxy(65,j);
		printf("%d-%d-%d",p_r.sDay,p_r.sMonth,p_r.sYear);
		j+=2;
		total=total+p_r.total;
		}
	   }
	   gotoxy(7,42);
	   printf("-------------------------------------------------------------------");
	   gotoxy(45,43);
	   printf("Total:        %.2f",total);
	   getche();
}

//=============================================:) THE END :) =================================

