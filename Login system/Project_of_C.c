#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
void men();
int loge();
int prof();
void edit();
char cpwd[30],pwd[10],ckpwd[10],un[30],unc[30],ad[30],co[30],n[30],ln[30];
int count=0,lg;
void sign();
int main() {
	FILE *fp;
   int i=3,a,c,p,o;
   int lg;
   int result;
   char pwd[10],ckpwd[10],un[30],unc[30];
   printf("This is the Project of C-programming lab\n");
  			printf("enter\n\t[1].login \n\t[2].forget(password or username)\n\t[3].sign up(for new one)\n");
   			scanf("%d",&p);
   system("cls");
   
if(p==1)
	{
reach :
	   	fp=fopen("pwd.bin","rb");
do
   {
   			printf("user name\n");
   			scanf("%s",un);
       		printf("enter the password\n");
       		scanf("%s",pwd);
while((fscanf(fp,"%s%s",unc,cpwd))!=EOF)
	{count++;
if(strcmp(cpwd,pwd)==0 && strcmp(unc,un)==0)
	{
goto a;
    }
	}
		rewind(fp);
goto b;
    	result=strcmp(ckpwd,pwd);
a: 
if(result==0)
    {
           printf("you just logged in\n");
           printf("\t*********enter 1 to start******");
           scanf("%d",&c);
    system("cls");
        a=1;
        i=-1;
        a=1;
    }
else
 	{
b:      
			printf("you enterd wrong password\n (option left %d)\n",i);
        --i;
        count=0;
        rewind(fp);
        a=0;
    }
    }
while(i!=-1);
    }
else if(p==3)
	{
		sign(&fp);
goto reach;
    system("cls");
	}
else if(p==2){
 	printf("no such option");
	 exit(0);
    }
    else
    {exit (0);
	}
if(a==0)
   {
    system("cls");
            printf("you are not the authorized person sry for that\n");
    }
else
	{
    men(&fp,count);
    	
    	if(lg==1)
    	{goto reach;
		}
    }
   	
return 0;
	} 
	
	
void men(FILE*fp ,int count)
{
	int k,h,i;
	opt :
		men:
printf("1.About the developer\n");
printf("2.about this project\n");
printf("3.your data\n");
printf("4.logout\n");
printf("5.exit\n");
scanf("%d",&k);

switch(k)
{
	case 1:
		edit(&fp);
		printf("\n enter [1] to return back");
	    	  	scanf("%d",&h);
				  if(h==1){
				  	system("cls");
				    goto men;}
		break;
	case 3:
	    i=prof(&fp,count);
		if(i==1)
		{goto opt;
		}
	    break;
	case 4:
	    loge();    
	    goto men;
	    break;
	    case 2:
	    	system("cls");
	    	printf("this is about the basic idea of login system.\n enter [1] to return back");
	    	  	scanf("%d",&h);
				  if(h==1){
				  	system("cls");
				    goto men;
	    	  }break;
		default:
			printf("Thank You!!!");
}
}
void sign(FILE*fp){
	
	int con;
		fp=fopen("data.bin","ab");
		printf("fill the form\n");
		gets(n);
		printf("name\n");
		gets(n);
		printf("last name\n");
		gets(ln);
		printf("country\n");
		gets(co);
		printf("address\n");
		gets(ad);	
		printf("username\n");
		scanf("%s",unc);
		printf("password\n");
		scanf("%s",cpwd);
		system("cls");
		printf("name:\t%s\t\tlast name:%s\t\tcountry:\t%s\t\taddress:\t%s\t\t\nusername:\t%s\tpassword:\t%s\t\t\n",n,ln,co,ad,unc,cpwd);
		printf("[1].conform\t\t[2].exit\n");
		scanf("%d",&con);
		if(con==1){
		fprintf(fp,"%s %s %s %s\n",n,ln,co,ad);
		fclose(fp);
		fp=fopen("pwd.bin","ab");
		fprintf(fp,"%s %s\n",unc,cpwd);
		}else{
		exit(0);
		}
		fclose(fp);
		
}
void edit()
{
	char e ;
	int u;
		system("cls");
			printf("this is the project made by \n Prasiddha Raj Neupane(ACE079BCT043)\n Mahendra Raj Neupane(ACE079BCT036)");
		
			
}

int prof(FILE*fp,int count)
{
	char e,l ;
	int c;
		system("cls");
			printf("this is your login and other detail");
			fp=fopen("data.bin","rb");
		while((fscanf(fp,"%s %s %s %s\n",n,ln,co,ad))!=EOF)
			{
				c++;
	
	if(count==c){
	
			printf("\nname:%s %s \ncountry:%s \naddress:%s\t\n",n,ln,co,ad);
			c=0;
	}

			
	}
	fclose(fp);
printf("enter [1].home");
	scanf("%d",&l);
	if(l==1);
	{
	system("cls");
	return 1;
	}
	return 0;	
}
int loge()
{
return 1;
}
