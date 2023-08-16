#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

struct record
{
	int x,y,len,count;
	float res;
	char op;
};

void display(int c,int x,char ch,int y,float res,int len,int count)
{
	int i;
	clrscr();
	printf("Press R for Record and A to exit");
	printf("\n|");
	for(i=0;i<19;i++)
	printf("-");
	printf("|\n|");
	if(c==1)//display a
		printf("%d",x);
	else if(c==2)//display operator
		printf("%d%c",x,ch);
	else if(c==3||c==4)//display b
		printf("%d%c%d",x,ch,y);
	for(i=0;i<count;i++)
		printf(" ");
	printf("|\n|");
	for(i=0;i<19-len;i++)
		printf(" ");
	if(c==4)
	{
		printf("%.2f",res);
	}
	printf("|\n|");
	for(i=0;i<19;i++)
		printf("-");
	printf("|\n");
	printf("| 7 | 8 | 9 | (REC) |\n| 4 | 5 | 6 | X | / |\n| 1 | 2 | 3 | + | - |\n|");
	for(i=0;i<19;i++)
		printf("-");
	printf("|");
}

void displayres(struct record out)
{
	int i;
	printf("%d%c%d=%.2f",out.x,out.op,out.y,out.res);
	for(i=0;i<(out.count-out.len-1);i++)
	    printf(" ");
	printf("|\n");
	printf("|");
}

int main()
{
	char ch,op,string[10];
	int i,count=18,a=0,b=0,len,z=0,j;
	float r;
	struct record rec;
	FILE *fptr;
	fptr=fopen("record.txt","w+");
	if(fptr==NULL)
	    {
	        printf("File not found");
	        exit(0);
	    }
	else
		printf("File found successfully");
	label:
	count=18,a=0,b=0;
	display(0,0,0,0,0,0,19);
	while ((ch = getche()) >= '0' && ch <= '9')//input a
	{
		a=a*10+(ch-48);
    	display(1,a,0,0,0,0,count--);
    	printf("\n");
    }

    op=ch;//operator
	display(2,a,ch,0,0,0,count--);
    printf("\n");

    while ((ch = getche())!= '=')//input b
	{
		b=b*10+(ch-48);
		display(3,a,op,b,0,0,count--);
		printf("\n");
    }
	switch(op)
	{
		case'+':
				r=a+b;
				break;
		case'-':
				r=a-b;
				break;
		case'*':
				r=a*b;
				break;
		case'/':
				r=(float)a/b;
				break;
		default:
				printf("Error!");
	}
	sprintf(string,"%.2f",r);
	len=strlen(string);
	count++;
	fprintf(fptr,"\n%d\t%c\t%d\t%f\t%d\t%d",a,op,b,r,len,count);

    display(4,a,op,b,r,len,count);//display result
    if((ch=getche())!='a'&&ch!='A')
	{
    	if(ch=='R'||ch=='r')
		{
			clrscr();
			printf("\n|");
			for(i=0;i<19;i++)
			printf("-");
			printf("|\n|");
			z=0;
			rewind(fptr);
			while(fscanf(fptr,"\n%d\t%c\t%d\t%f\t%d\t%d",&rec.x,&rec.op,&rec.y,&rec.res,&rec.len,&rec.count)!=EOF)
				if(z<6)
				{	
					displayres(rec);//display record
					z++;
				}
			for(i=0;i<(6-z);i++)
			{
				for(j=0;j<19;j++)
					printf(" ");
				printf("|\n|");
			}
			for(i=0;i<19;i++)
				printf("-");
			printf("|");
			getche();
		}
    	goto label;
    }
    fclose(fptr);
	getch();
	return 0;
}