#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>

char sR=10, kR=20, tR=30, totRes=0;


void add();  //FUNCTIONS
void list();
void edit();  //GLOBALLY DECLARED FUNCTIONS N VARIABLE
void delete1();
void search();

void gotoxy(int x, int y )
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void login()
{

	int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char user[10]="admin";
    char pass[10]="admin";
    do
{
	system("cls");
    gotoxy(10,2);
    printf("+=========================================================+");
    gotoxy(10,3);
    printf("|                  THE GREART HOTEL                       |");
    gotoxy(10,4);
    printf("+=========================================================+");
    gotoxy(1,24);
    printf("_______________________________________________________________________________");
    gotoxy(15,25);
    printf(" Visit us at: 4th FLOOR @ ACEM");
	gotoxy(15,10);
    printf(" \n                       ENTER USERNAME:-");
	scanf("%s", &uname);
	gotoxy(15,13);
	printf(" \n                       ENTER PASSWORD:-");
	while(i<10)
	{
	    pword[i]=getch();
	    c=pword[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';
	//char code=pword;
	i=0;
	//scanf("%s",&pword);
		if(strcmp(uname,user)==0 && strcmp(pword,pass)==0)
	{
	printf("  \n\n\n       WELCOME !!!! LOGIN IS SUCCESSFUL");

	break;
	}
	else
	{
		printf("\n");
        printf("\n");
        printf("\n");
        printf("\n\t\t        SORRY !!!!  LOGIN IS UNSUCESSFUL");
		a++;

		
}
}while(a<=2);
	if (a>2)
	{
		printf("\n");
        printf("\n    Sorry you have entered the wrong username and password for four times!!!");
		printf("\n");
        printf("\n\t\t        Press any key to exit.....");
		
        getch();
        exit(0);

		}
		system("cls");
}

void welcome()
{
    system("cls");
    gotoxy(25,12);
    printf("WELCOME TO THE GREAT HOTEL, Nepal");
    gotoxy(25,15);
    printf("(Hotel for the great ones)");
    gotoxy(20,22);
    printf("\n Press any key to proceed with the reservation.........");
		getche();
		login();

}

void mainPage()
{
    gotoxy(5,5);
    printf("*********************************************************************");
	gotoxy(5,6);
	printf("*	    		HOTEL RESERVATION MANAGEMENT SYSTEM		 *");		
	gotoxy(5,7);
	printf("*	    								 *");
	gotoxy(5,8);
	printf("*	    								 *");
	gotoxy(5,9);
	printf("*	 This a C project jointly completed by NIRDESH BHATTARAI 	 *");
	gotoxy(5,10);
	printf("*	 and RUSHA MANANDHAR 					  	 *");	
	gotoxy(5,11);
	printf("*	    								 *");
	gotoxy(5,12);
	printf("*	    								 *");	
	gotoxy(5,13);
	printf("*	    								 *");
	gotoxy(5,14);
    printf("*********************************************************************");
    gotoxy(25,20);printf("\n Press any key to continue.");
		getche();
	 welcome();
	 
}

void headerfooter()
{
    gotoxy(10,2);
    printf("+=========================================================+");
    gotoxy(10,3);
    printf("|                  THE GREART HOTEL                       |");
    gotoxy(10,4);
    printf("+=========================================================+");
    gotoxy(1,24);
    printf("_______________________________________________________________________________");
    gotoxy(15,25);
    printf(" Visit us at: 4th Floor @ ACEM");
}

void setcolor(int ForgC)
{ WORD wColor;
HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
{
	wColor=(csbi.wAttributes & 0xB0)+(ForgC & 0x0B);
//	SetConsoleTextAttributes(hStdOut,wColor);
	SetConsoleTextAttribute(hStdOut,wColor);

}
}



char hotelInfo()    // FUNCTION TO DISPLAY ROOM INFO
{
system("cls");
char chc;
    headerfooter();
    gotoxy(5,7); printf("Available Room:");
    gotoxy(5,9); printf("SUITE: Total =%d",sR);
    gotoxy(5,10); printf("KING: Total =%d",kR);
    gotoxy(5,11); printf("TRAVEL: Total =%d",tR);

gotoxy(3,13); printf(" Room Price:");
gotoxy(3,14);printf("+----------------------------------------------------------------+");
gotoxy(3,15);printf("| Room Type |               Information               |  Price   |");
gotoxy(3,16);printf("+----------------------------------------------------------------+");
gotoxy(3,17);printf("|  SUIT     |  2Rooms, 1205q-Mtr, Sofa and King Bed   |Rs.10000/-|");
gotoxy(3,18);printf("+----------------------------------------------------------------+");
gotoxy(3,19);printf("|   KING    |  160Sq-Meter, Sofa, Table and King Bed  |Rs.5000/- |");
gotoxy(3,20);printf("+----------------------------------------------------------------+");
gotoxy(3,21);printf("|  Travel   |  405q-Meter, Table, Queen Bed           |Rs.2500/- |");
gotoxy(3,22);printf("+----------------------------------------------------------------+");
getch();
}

	

struct CustomerDetails   //STRUCTURE DECLARATION
{
	char roomnumber[10];
	char name[20];
	char address[25];
	char phonenumber[15];
	char nationality[15];
	char arrivaldate[10];
    char roomType;
    float billAmt;
    int perDay;
    int noOfPer, noOfRoom;
    
	
}strR[90];

int main(){     // MAIN FUNCTION
	mainPage();
    system("cls");

    int i=0;

	time_t t;
	time(&t);
	char customername;
	char choice;
    system("cls");
	while (1)      // INFINITE LOOP
	{
		system("cls");
		setcolor(10);
		 for(i=0;i<80;i++)
		printf("-");
		printf("\n");
		printf("   ***************************  |THE GREAT HOTEL|  ************************** \n");
		for(i=0;i<80;i++)
		printf("-");
        setcolor(3);
		 for(i=0;i<80;i++)
		printf("-");
		printf("\n");
		printf("   ******************************  |MAIN MENU|  ***************************** \n");
		for(i=0;i<80;i++)
		printf("-");
		printf("\n");
		setcolor(10);
		
		printf("\n\t\t-----------------------------------------");
		printf(" \n\t\t|\t1/2 -> Book a room/Show Avl Room|");
		printf("\n\t\t-----------------------------------------");
		printf(" \n \t\t|\t3 -> View Customer Record       |");
		printf("\n\t\t-----------------------------------------");
		printf(" \n \t\t|\t4 -> Delete Customer Record     |");
		printf("\n\t\t-----------------------------------------");
		printf(" \n \t\t|\t5 -> Search Customer Record     |");
		printf("\n\t\t-----------------------------------------");
		printf(" \n \t\t|\t6 -> Edit Record\t        |");
		printf("\n\t\t-----------------------------------------");
		printf(" \n \t\t|\t7 -> Exit\t\t        |");
		printf("\n\t\t-----------------------------------------");
		printf("\n");
		printf("\t\t *Please enter your choice for menu*:\n");
        for(i=0;i<80;i++)
		printf("-");
	    printf("\nCurrent date and time : %s",ctime(&t));
	    for(i=0;i<80;i++)
		printf("-");

		choice=getche();
		choice=toupper(choice);
		switch(choice)           // SWITCH STATEMENT
		{
			case '1':
				add();break;
            case '2':
				hotelInfo();break; 
			case '3':
				list();break;
			case '4':
				delete1();break;
			case '5':
				search();break;
			case '6':
				edit();break; 
			case '7':
				system("cls");
				gotoxy(25,12);
                                printf(" Thank You... Visit Again... %c", 2);
			getch();
            exit(0);
				break;
			default:
				system("cls");
				printf("Incorrect Input");
				printf("\n Press any key to continue");
				getch();
		}
	}


return 0;
}

void add()      // FUNCTION TO ADD RECORD
{
	FILE *f;
	char test;
	f=fopen("add.txt","a+");
	if(f==0)
	{   f=fopen("add.txt","w+");
		system("cls");
		printf("Please hold on while we set our database in your computer!!");
		printf("\n Process completed press any key to continue!! ");
		getch();
	}
	while(1)
	{
	
        int i=0;
            system("cls");
		printf("\n \t\t\tEnter Customer Details:\n");
		for(i ;i<80;i++)
        printf("*");
		printf("\n\tEnter Room number:\t");
		scanf("%s",strR[totRes].roomnumber);
		fflush(stdin);
		printf("\tEnter Name:\t");
		scanf("%s",strR[totRes].name);
        fflush(stdin);
		printf("\tEnter Address:\t");
		scanf("%s",strR[totRes].address);
        fflush(stdin);
		printf("\tEnter Phone Number:\t");
		scanf("%s",strR[totRes].phonenumber);
        fflush(stdin);
		printf("\tEnter Nationality:\t");
		scanf("%s",strR[totRes].nationality);
        fflush(stdin);
        printf("\tEnter Arrival date(dd\\mm\\yyyy):\t");
		scanf("%s",&strR[totRes].arrivaldate);
        fflush(stdin);
         printf("\tEnter No days: \t");
         scanf("%d", &strR[totRes].perDay); 
         fflush(stdin);
         printf("\tEnter Room Type(S/K/T): \t");
         scanf("%c", &strR[totRes].roomType); 
         fflush(stdin);
              printf("\tEnter No of Persons: \t");
         scanf("%d", &strR[totRes].noOfPer);
          fflush(stdin);
          

		
        strR[totRes].noOfRoom=1;
if(strR[totRes].noOfPer>3)
{
strR[totRes].noOfRoom=0;
strR[totRes].noOfRoom += (strR[totRes].noOfPer/3); 
if(strR[totRes].noOfPer%3 != 0)
strR[totRes].noOfRoom ++;
}
    float damt;
char ty[10];
    switch(strR[totRes].roomType)
    {
    case 's': case 'S':
    strcpy(ty,"SUITE"); damt=10000;
sR=sR-(strR[totRes].perDay*strR[totRes].noOfRoom);
break;

    case 'k': case 'K':
strcpy(ty, "King"); damt=5000,
kR=kR-(strR[totRes].perDay*strR[totRes].noOfRoom);
break;

    case 't': case 'T':
strcpy(ty, "Travel"); damt=2500;
tR=tR-(strR[totRes].perDay*strR[totRes].noOfRoom);
 break;
    default :
    strcpy(ty, "NULL"); damt=00;
    break;
    }

strR[totRes].billAmt=strR[totRes].perDay*damt*strR[totRes].noOfRoom;

gotoxy (3,13); printf("Bill: ");
gotoxy(3,14); printf("+---------------------------------------------------------------+");
gotoxy(3,15); printf("| Room Type | Total Days | Per day | No of Rooms |    Price     |");
gotoxy(3,16); printf("+-----------+------------+---------+-------------+--------------+");
gotoxy(3,17); printf("|%8s   |%10d  |  %5.0f  |  %5.0d      | Rs.%8.0f/-|",
ty, strR[totRes].perDay, damt, strR[totRes].noOfRoom, strR[totRes].billAmt);
gotoxy(3,18); printf("+_______________________________________________________________+");
gotoxy(3,19); printf("| Total Bill:                                    Rs.%8.0f/-  |",strR[totRes].billAmt);
gotoxy(3,20); ;printf("+_______________________________________________________________+");


        
     
        fwrite(&strR,sizeof(strR),1,f);
        fflush(stdin);
        
        printf("\n\n\t %d Room(3 per room) is successfully booked for %d days!!",strR[totRes].noOfRoom,strR[totRes].perDay);
		printf("\n \tPress esc key to exit,  any other key to add another customer detail:");
		test=getche();
		if(test==27)
			break;

	
    }
	fclose(f);
}

void list()     // FUNCTION TO SHOW ALL RECORD    
{
	FILE *f;
	int i;
	if((f=fopen("add.txt","r"))==NULL)
		exit(0);
	system("cls");
	printf("ROOM\t");
	printf("NAME\t ");
	printf("\tADDRESS ");
	printf("\t\tPHONENUMBER ");
	printf("\tNATIONALITY ");
    printf("\t ARRIVALDATE");
    printf("\tROOM TYPE ");
    printf("\tNO OF DAY");
    printf("\tNO OF PERSON");
    printf("\tBILL AMOUNT \n");
    
	for(i=0;i<118;i++)
		printf("-");
    printf("\n");
    char ty[10];
    while(fread(&strR,sizeof(strR),1,f)==1)
	{
        switch(strR[totRes].roomType)
    {
    case 's': case 'S':
    strcpy(ty,"SUITE");
    break;
    case 'k': case 'K':
    strcpy(ty, "King");
    break;
    case 't': case 'T':
    strcpy(ty, "Travel");
    break;
    
    }
                    
        printf(" %s \t %s \t\t %s \t\t  %s \t  %s \t  %s \t  %s \t%d \t %d \t %.2f\n ",
        strR[totRes].roomnumber,strR[totRes].name,strR[totRes].address,strR[totRes].phonenumber,strR[totRes].nationality,strR[totRes].arrivaldate,ty,strR[totRes].perDay,strR[totRes].noOfPer,strR[totRes].billAmt) ;


       }
	printf("\n");
	for(i=0;i<118;i++)
		printf("-");

	fclose(f);
	getch();
}

void delete1()      // FUNCTION TO REMOVE  RECORD
{
    
	FILE *f,*t;
	int i=1;
	char roomnumber[20];
	if((t=fopen("temp.txt","w"))==NULL)
	exit(0);
	if((f=fopen("add.txt","r"))==NULL)
	exit(0);
	system("cls");
	printf("Enter the Room Number of the hotel to be deleted from the database: \n");
	fflush(stdin);
	scanf("%s",roomnumber);
	while(fread(&strR,sizeof(strR),1,f)==1)
	{
		if(strcmp(strR[totRes].roomnumber,roomnumber)==0)
		{       i=0;
			continue;
		}
		else
			fwrite(&strR,sizeof(strR),1,t);
	}
	if(i==1)
	{
		printf("\n\n Records of Customer in this  Room number is not found!!");
		//remove("E:/file.txt");
	   //rename("E:/temp.txt","E:/file.txt");
		getch();
		fclose(f);
		fclose(t);
	
	}else{
	fclose(f);
	fclose(t);
	remove("add.txt");
	rename("temp.txt","add.txt");
	printf("\n\nThe Customer is successfully removed....");
	fclose(f);
	fclose(t);
	getch();
}
}

void search()        // FUNCTION TO SEARCH RECORD   
{
system("cls");
	FILE *f;
	char roomnumber[20];
    char ty[10];
	int flag=1;
	f=fopen("add.txt","r+");
	if(f==0)
		exit(0);
	fflush(stdin);
	printf("Enter Room number of the customer to search its details: \n");
	scanf("%s", roomnumber);
        while(fread(&strR,sizeof(strR),1,f)==1)
	{
		   switch(strR[totRes].roomType)
    {
    case 's': case 'S':
    strcpy(ty,"SUITE");
    break;
    case 'k': case 'K':
    strcpy(ty, "King");
    break;
    case 't': case 'T':
    strcpy(ty, "Travel");
    break;
    
    }
        if(strcmp(strR[totRes].roomnumber,roomnumber)==0){
			flag=0;
			            printf("\n\t\tRecord Found\n ");
			printf("\n\tRoom Number:\t%s",strR[totRes].roomnumber);
			printf("\n\tName:\t%s",strR[totRes].name);
			printf("\n\tAddress:\t%s",strR[totRes].address);
			printf("\n\tPhone number:\t%s",strR[totRes].phonenumber);
			printf("\n\tNationality:\t%s",strR[totRes].nationality);
        	printf("\n\tArrival date:\t%s",strR[totRes].arrivaldate);
             printf("\n\tRoom type:\t%s", ty);
            printf("\n\tNo of person:\t%d", strR[totRes].perDay);
            printf("\n\tNo of room :\t%d", strR[totRes].noOfPer);
            printf("\n\tAMOUNT: Rs.\t %.2f", strR[totRes].billAmt);
			flag=0;
		
		}
    }
	if(flag==1){
		printf("\n\tRequested Customer could not be found!");
	}
	getch();
	fclose(f);
}

void edit()         // FUNCTION TO EDIT RECORD
{
	FILE *f;
	int k=1;
	char roomnumber[20];
	long int size=sizeof(strR);
	if((f=fopen("add.txt","r+"))==NULL)
		exit(0);
	system("cls");
	printf("Enter Room number of the customer to edit:\n\n");
	scanf("%[^\n]",roomnumber);
	fflush(stdin);
	while(fread(&strR,sizeof(strR),1,f)==1)
	{
		if(strcmp(strR[totRes].roomnumber,roomnumber)==0)
		{
			k=0;
			
		printf("\n\tEnter Room number:\t");
		scanf("%s",strR[totRes].roomnumber);
		fflush(stdin);
		printf("\tEnter Name:\t");
		scanf("%s",strR[totRes].name);
        fflush(stdin);
		printf("\tEnter Address:\t");
		scanf("%s",strR[totRes].address);
        fflush(stdin);
		printf("\tEnter Phone Number:\t");
		scanf("%s",strR[totRes].phonenumber);
        fflush(stdin);
		printf("\tEnter Nationality:\t");
		scanf("%s",strR[totRes].nationality);
        fflush(stdin);
        printf("\tEnter Arrival date(dd\\mm\\yyyy):\t");
		scanf("%s",&strR[totRes].arrivaldate);
        fflush(stdin);
         printf("\tEnter No days: \t");
         scanf("%d", &strR[totRes].perDay); 
         fflush(stdin);
         printf("\tEnter Room Type(S/K/T): \t");
         scanf("%c", &strR[totRes].roomType); 
         fflush(stdin);
              printf("\tEnter No of Persons: \t");
         scanf("%d", &strR[totRes].noOfPer);
          fflush(stdin);
          

		
        strR[totRes].noOfRoom=1;
if(strR[totRes].noOfPer>3)
{
strR[totRes].noOfRoom=0;
strR[totRes].noOfRoom += (strR[totRes].noOfPer/3); 
if(strR[totRes].noOfPer%3 != 0)
strR[totRes].noOfRoom ++;
}
    float damt;
char ty[10];
    switch(strR[totRes].roomType)
    {
    case 's': case 'S':
    strcpy(ty,"SUITE"); damt=10000;
sR=sR-(strR[totRes].perDay*strR[totRes].noOfRoom);
break;

    case 'k': case 'K':
strcpy(ty, "King"); damt=5000,
kR=kR-(strR[totRes].perDay*strR[totRes].noOfRoom);
break;

    case 't': case 'T':
strcpy(ty, "Travel"); damt=2500;
tR=tR-(strR[totRes].perDay*strR[totRes].noOfRoom);
 break;
    default :
    strcpy(ty, "NULL"); damt=00;
    break;
    }

strR[totRes].billAmt=strR[totRes].perDay*damt*strR[totRes].noOfRoom;

gotoxy (3,13); printf("Bill: ");
gotoxy(3,14); printf("+---------------------------------------------------------------+");
gotoxy(3,15); printf("| Room Type | Total Days | Per day | No of Rooms |    Price     |");
gotoxy(3,16); printf("+-----------+------------+---------+-------------+--------------+");
gotoxy(3,17); printf("|%8s   |%10d  |  %5.0f  |  %5.0d      | Rs.%8.0f/-|",
ty, strR[totRes].perDay, damt, strR[totRes].noOfRoom, strR[totRes].billAmt);
gotoxy(3,18); printf("+_______________________________________________________________+");
gotoxy(3,19); printf("| Total Bill:                                    Rs.%8.0f/-  |",strR[totRes].billAmt);
gotoxy(3,20); ;printf("+_______________________________________________________________+");
            
            fseek(f,size,SEEK_CUR);  //to go to desired position infile
			fwrite(&strR,sizeof(strR),1,f);
			break;
		}
	}
	if(k==1){
		printf("\n\nTHE RECORD DOESN'T EXIST!!!!");
		fclose(f);
		getch();
	}else{
	fclose(f);
	printf("\n\n\t\tYOUR RECORD IS SUCCESSFULLY EDITED!!!");
	getch();
}
}
