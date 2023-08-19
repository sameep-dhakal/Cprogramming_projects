#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<dos.h>
#include<windows.h>
//Display today's date
void today();
//take year and month for calender
int getyear();
int getmonth();
//checks leap year
int checkleapyear(int);
//gives number of days in a month
int daysinmonth(int,int);
//Zellers rule
int zeller(int,int);
//prints calender
void calender(int,int);
//Header
void header();
//Notes(Remainders)
void rem();
void main()
{
	int year,month,length,start;
	char ch;
	system("Color 30");
	header();
	year=getyear();
	month=getmonth();
	while(1)
	{
		system("cls");
			header();
			length=daysinmonth(month,year);
			start=zeller(month,year);
			calender(start,length);
		printf("\n\nEnter a choice\n\t'p' for previous month\n\t'n' for next month\n\t'a' to add remainder\n\t\t::");
		fflush(stdin);
		scanf("%c",&ch);
		if(ch=='n')
		{
			month++;
			if(month==13)
			{
				month=1;
				year++;
			}
		}
		if(ch=='p')
		{
			month--;
			if(month==0)
			{
				month=12;
				year--;
			}
		}
		if(ch=='a')
		{
			printf("\n\tRemainder\n");
			rem();
		}
			
	}
}
void today()
{

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("\n\t\t\t\t\tToday:%d-%d-%d AD", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}
int getyear()
{
	int x;
	readyear:
	printf("\n\t\t\t\tEnter year (1900-2100):\t");
	scanf("%d",&x);
	if((x<1900)||(x>2100))
	{
		printf("\t\t\t\tInvalid year");
		goto readyear;
	}
	else
	{
		return x;
	}
}
int checkleapyear(int y)
{
	if(((y%4==0)&&(y%100!=0))||(y%400==0))
		return 1;
	else
		return 0;
}
int getmonth()
{
	int x;
	readmonth:
	printf("\n\t\t\t\tEnter month (1-12):\t");
	scanf("%d",&x);
	if((x<1)||(x>12))
	{
		printf("\t\t\t\tInvalid month");
		goto readmonth;
	}
	else
	{
		return x;
	}
	
}

int daysinmonth(int x,int y)
{
	printf("\n\n\t\t\t\t\t\t %d",y);
	switch(x)
	{
		case 1:
			{
				printf("\n\t\t\t\t\t\tJanuary\n");
				return 31;
				break;
			}
		case 2:
			{
				printf("\n\t\t\t\t\t\tFebruary\n");
				if(checkleapyear(y)==1)
					return 29;
				else
					return 28;
				break;
			}
		case 3:
			{
				printf("\n\t\t\t\t\t\tMarch\n");
				return 31;
				break;
			}
		case 4:
			{
				printf("\n\t\t\t\t\t\tApril\n");
				return 30;
				break;
			}
		case 5:
			{
				printf("\n\t\t\t\t\t\tMay\n");
				return 31;
				break;
			}
		case 6:
			{
				printf("\n\t\t\t\t\t\tJune\n");
				return 30;
				break;
			}
		case 7:
			{
				printf("\n\t\t\t\t\t\tJuly\n");
				return 31;
				break;
			}
		case 8:
			{
				printf("\n\t\t\t\t\t\tAugust\n");
				return 31;
				break;
			}
		case 9:
			{
				printf("\n\t\t\t\t\t\tSeptember\n");
				return 30;
				break;
			}
		case 10:
			{
				printf("\n\t\t\t\t\t\tOctober\n");
				return 31;
				break;
			}
		case 11:
			{
				printf("\n\t\t\t\t\t\tNovember\n");
				return 30;
				break;
			}
		case 12:
			{
				printf("\n\t\t\t\t\t\tDecember\n");
				return 31;
				break;
			}
	}
}

int zeller(int m,int y)
{
	int h, d=1;
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
    h=( y + y/4 -y/100 + y/400 + t[m-1] + d) % 7; 
  	return h;
}

void calender(int s,int d)
	{
		printf("\t___________________________________________________________________________________________________");
		printf("\n\tSun\t\tMon\t\tTue\t\tWed\t\tThu\t\tFri\t\tSat\n")	;
		int arr[7][7],a=0,i,j;
		for(i=0;i<7;i++)
		{	
			for(j=0;j<7;j++)
			{
				if((i!=0)||(j>=s))
				{
					a++;
					printf("\t%d\t",a);
				}
				else
				{
					printf("\t\t");
				}
				if(a==d)
					break;
			}
			printf("\n");
			if(a==d)
				break;
		}
		printf("\t___________________________________________________________________________________________________");
		
	}
void header()
{
	printf("\n\n\t\t\t\t\tYEARLY CALENDAR(AD)\n\t\t\t\t===================================");
	today();
}
void rem()
{
	struct rem
	{
    	int yy,mm,dd;
    	char note[100];
	} list;
	char note[100];
	FILE *fop,*ftwo;
	int choice=1,i,n,l;
	while(choice!=0)
	{
	    
	    printf("\n1.Create a new Remainder\n2.Display all Remainders\n3.Delete a Remainder\n0.Exit\n");
	    printf("Enter the choice:");
	    scanf("%d",&choice);
	    switch(choice)
	    {
	    	case 0:					
	    {
	    	printf("End");
			break;
		}
	
	    case 1:
	    {
	        fop=fopen("Remainder.dll","a");
	       	while (1)
	       	{
	       		printf("Enter Date(yyyy-mm-dd)(0 to exit):");
	            scanf("%d-%d-%d",&list.yy,&list.mm,&list.dd);
	            if(list.yy==0)
	            {
					 break;
				}
	            fflush(stdin);
	            printf("\nNote:");
	            scanf(" %[^\n]",&list.note);								/*Scan everything before enter*/
	           	fflush(stdin);   /*imp:Clears garbage value*/
	            printf("\n");
	            fwrite(&list,sizeof(list),1,fop);
	        }
	       	fclose(fop);
	       	break;
	    }
	
	    case 2:
		{
	        printf("\tLIST OF Remainders\n");
	        for(i=97; i<=122; i=i+1)
	        {
	            fop=fopen("Remainder.dll","r");
	            fflush(stdin);
	            while(fread(&list,sizeof(list),1,fop)==1)
	            {
	                if(list.note[0]==i || list.note[0]==i-32)
	                {
	                    printf("\nDate\t: %d-%d-%d\nNote\t: %s\t\n",list.yy,list.mm,list.dd,list.note);
	                }
	            }
	        	fclose(fop);
	        }
	        break;
	    }
	    
		case 3:
		{
			fflush(stdin);
			printf("\n\tDELETE A Remainder\nEnter the note of remainder to delete:");
			scanf("%[^\n]",&note);
			fop=fopen("Remainder.dll","r");
			ftwo=fopen("temp.dat","w");
			while(fread(&list,sizeof(list),1,fop)!=0)
				if (stricmp(note,list.note)!=0)
					fwrite(&list,sizeof(list),1,ftwo);
			fclose(fop);
			fclose(ftwo);
			remove("Remainder.dll");
			rename("temp.dat","Remainder.dll");
			printf("Remainder Deleted");
			break;		
		}
	    default:
		{
	        printf("Invalid choice");
	        break;
	    }
	    }
	}
}
	
