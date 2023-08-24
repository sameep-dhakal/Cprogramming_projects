#include<stdio.h>
#include<conio.h>

struct details{
	int sn;
    char name[50];
    char code[20];
    int qty;
    int price;
};

int create(struct details item);
int append(struct details item);
int read(struct details item);

int main()
{
    struct details item;
 int opt=0;
 printf("---------------------------------------------------------\n");
 printf("Welcome to the inventory management system\n");
  while(opt!=4)
 {
printf("---------------------------------------------------------\n");
 printf("What would you like to do?\n");
 printf("1.Create new list of items\n2.Add items to the list\n3.Read list\n4.Exit\n");
  printf("Option:");
 scanf("%d",&opt);
 printf("\n");
 switch(opt)
 {
    case 1:printf("CREATING NEW LIST\n");
    create(item);
    break;

    case 2:printf("EDITING IN SAME LIST\n");
    append(item);
    break;

    case 3:printf("READING LIST\n");
    read(item);
    break;

    case 4:printf("EXITING\n");
    break;

    default:printf("Invalid input\n");
 }
 }
printf("BYE BYE\n");
printf("---------------------------------------------------------\n");
printf("Made by:\nSiddhant Pant ACE079BCT064\nTrishal Srivastava ACE079BCT076");
 return 0;
}

int create(struct details item)
{
int n,i;
FILE *fp;
if(fp == NULL)
printf("FILE NOT CREATED\n");
else
printf("NEW FILE CREATED\n");
   printf("Enter the number of items you want to enter:");
   scanf("%d",&n);
   fflush(stdin);
   fp=fopen("inventory.txt","w");
   for(i=1;i<=n;i++)
   {
      fflush(stdin);
      printf("Item name:");
      scanf("%s",item.name);
      fflush(stdin);
      printf("Item code:");
      scanf("%s",item.code);
      fflush(stdin);
      printf("Quantity:");
      scanf("%d",&item.qty);
      fflush(stdin);
      printf("Price:");
      scanf("%d",&item.price);
      fflush(stdin);
  	  fwrite(&item,sizeof(item),1,fp);
  	  printf("\n");
   }
   printf("Items stored\n");
   fclose(fp);
}

int append(struct details item)
{
	char choice;
   int n,i;
FILE *fp;
if(fp == NULL)
printf("FILE NOT FOUND\n");
else
printf("FILE FOUND\n");
   fp=fopen("inventory.txt","a");
do{
      fflush(stdin);
      printf("Item name:");
      scanf("%s",item.name);
      fflush(stdin);
      printf("Item code:");
      scanf("%s",item.code);
      fflush(stdin);
      printf("Quantity:");
      scanf("%d",&item.qty);
      fflush(stdin);
      printf("Price:");
      scanf("%d",&item.price);
      fflush(stdin);
  	  fwrite(&item,sizeof(item),1,fp);
  	  printf("Do you want to continue?(Y/N)");
  	  choice=getche();
  	printf("\n");
   }while(choice=='Y'||choice=='y');
   fclose(fp);
}

int read(struct details item)	
{
	FILE *fp;
if(fp == NULL)
printf("FILE NOT FOUND\n");
else
printf("FILE FOUND\n");
	fp=fopen("inventory.txt","r");
printf("\nName\t\tCode\t\tQuantity\tPrice\n");
   printf("---------------------------------------------------------\n");
   while(fread(&item,sizeof(item),1,fp)==1)
      printf("\n%s\t\t%s\t\t%d\t\t%d\n",item.name,item.code,item.qty,item.price);
   getch();
   fclose(fp);
}
