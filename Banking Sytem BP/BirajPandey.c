#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Account
{
	char bname[25];
	char bbranch[20];
	char name[30];
	char address[100];
	int accNo;
	float balance;
};
char filename[]="d:\\bank.txt";
struct Account acc;
void NewAccount();
void Deposit();
void Withdraw();
void Search();
void Logout();
void ShowOption();
FILE *fptr;
int main()
{
	struct Account acc;

	char option;
	int accSearch;
	fptr=fopen(filename,"r+b");
	if (fptr==NULL)
	{
		fptr=fopen(filename,"w+b");
		if(fptr==NULL)
		{
			printf("file cannot be created ");
		}
	}
	printf("\nYou are heartly welcome to our Banking Management System\n\n");
	ShowOption();
	scanf("%c",&option);
	printf("%c\n",option);
switch(option)
{
	case 'n':
		NewAccount();
		break;
		case'd':
			printf("Enter your account numberto deposit:\n");
			scanf("%d",&accSearch);
			Deposit(accSearch);
			break; 
			case'w':
				printf("Enter your account number to withdraw");
				scanf("%d",&accSearch);
				Withdraw(accSearch);
				break;
				case's':
					printf("Enter the account number you want to be searched");
					scanf("%d",&accSearch);
					
					break;
					
				default:
				printf("Sorry you have entered the wrong option");
				break;	
}
fclose(fptr);
return 0;

}










void ShowOption()
{
	printf("Please,kindly enter your option");
	printf("\n press n to create new account");
	printf("\n press d to deposite\n");
	printf("press w to withdraw your cash\n");
	printf("press s tob display your account information");
	
}
void NewAccount()
{
	struct Account acc;
	char bn[20];
	char bbr[20];
	char n[80];
	int aNo;
	char add[50];
	float bal=0;
	fflush(stdin);
	printf("\n Name of bank    :\n  branch   :  \n Account holder's name");
	scanf("%s%s%s",&bn,&bbr,&n);
	printf("Address of acc holder :");
	scanf("%s",&add);
	printf("\nAccount number\n");
	scanf("%d",&aNo);
	strcpy(acc.bname,bn);
	strcpy(acc.bbranch,bbr);
	strcpy(acc.name,n);
    acc.accNo=aNo;
	strcpy(acc.address,add);
	acc.balance=bal;
	fseek(fptr,0,SEEK_END);
	fwrite(&acc,sizeof(acc),1,fptr);
	printf("\n Your Account hass been created successfully\n");
	printf("\n*******Your given data are*****");
	printf("\n Name of branch:   %s",acc.bbranch);
	printf("\n Name of account holder  :%s",acc.name);
	printf("\n Account number : %d",acc.accNo);
	printf("\nAddress :%s",acc.address);
	printf("\nAVAILABLE BALANCE ;    %f",acc.balance);
	printf("\n**************************\n");
}
void Search(int accNoForSearch)
{
	int isFound=0;
	
	fseek(fptr,0,SEEK_SET);
	while (fread(&acc,sizeof(acc),1,fptr)==1)
	{
		if(acc.accNo==accNoForSearch)
		{
			printf("\n_______ACCOUNT INFORMATION_________");
			
				printf("\n name of bank   :%s",acc.bname);
				printf("\n name of branch   :%s",acc.bbranch);
				printf("\n  ACCOUNT NUMBER   :%d",acc.accNo);
				printf("\n AVAILABLE BALANCE   :%f",acc.balance);
				
				printf("\n ------------------------\n");
				isFound=1;
				break;
			
		}
	}
	if(isFound==0)
	{
		printf("\n the given data is not found");
	}
	
}
void Deposit(int accNoForSearch)
{
	
	int i=0;
	float dpstAmt;
	fseek(fptr,0,SEEK_SET);
	while(fread(&acc,sizeof(acc),1,fptr)==1)
	{
	
		i++;
		if(acc.accNo==accNoForSearch)
		{
			printf("\nthe current balance for account %d is %f\n",accNoForSearch,acc.balance);
			printf("\n Enter your amount");
			scanf("%f",&dpstAmt);
			acc.balance+=dpstAmt;
			fseek(fptr,(i-1)*sizeof(acc),SEEK_SET);
			fwrite(&acc,sizeof(acc),1,fptr);
			printf("\nThe new balance for your account is %f\n",acc.balance);
	break;
		}
	}
}
void Withdraw(int accNoForSearch)
{
	float wAmt;
	int i=0;
	fseek(fptr,0,SEEK_SET);
	while(fread(&acc,sizeof(acc),1,fptr)==1)
	{
		
		i++;
		if(acc.accNo==accNoForSearch)
		{
			
			 printf("\n The current balance is %f",acc.balance);
			 printf("\n Amount you want to enter");
			 scanf("%f",&wAmt);
			 acc.balance=acc.balance-wAmt;
			 fflush(stdin);
			 fseek(fptr,(i-1)*sizeof(acc),SEEK_SET);
			 fwrite(&acc,sizeof(acc),1,fptr);
			 printf("\n The new balance of account number %d is %f\n",accNoForSearch,acc.balance);
			 break;
			 
		}
	}
}
