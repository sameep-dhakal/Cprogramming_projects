#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
struct student
{
char name [20];
int age;
char sex;
int Class;
};
printf("\n STUDENT DATA MANAGEMENT SYSTEM \n");
struct student si;
FILE*fptr,*fptrTemp;
char student_name [15];
char choice;
char fileName[50]="student.txt";
int dataFound=0; 
int recordNo=0;
fptr=fopen(fileName,"r+b");
if(fptr==NULL)
{
fptr=fopen(fileName,"w+b") ;
if (fptr==NULL)
{
printf ("File can not be created!\n");
exit(1);
}
}
while(1)
{
printf("\n\nl.Add Record\n");
printf("2.List Record\n");
printf("3.Modify Record\n");
printf("4.Search Record\n");
printf("5.Delete Record\n");
printf("6.Exit\n");
printf("Enter Your choice\t");
fflush(stdin);
choice=getchar();
printf ("\n");
switch (choice )
{
case '1':
fseek(fptr,0,SEEK_END);
printf("Student Name:\t");
fflush(stdin);
gets(si.name);
printf("\nStudent age:\t");
scanf ("%d", &si.age) ;
printf("\nSex of student: \t");
fflush(stdin);
si.sex=getchar();
printf ("\nclass:\t");
scanf("%d",&si.Class);
fwrite (&si, sizeof(si), 1, fptr);
break;
case '2':
fseek(fptr, 0, SEEK_SET);
printf("Name\tAge\tSex\tClass\n");
while(fread (&si, sizeof(si),1,fptr)==1)
{
printf ("\n");
printf ("%s\t%d\t%c\t%d\n",si.name, si.age, si.sex, si.Class);
}
printf("\n");
break;
case '3':
printf("Enter the name of student which is to be modified!\t");
fflush(stdin);
gets(student_name);
rewind(fptr);
dataFound=0;
recordNo=0;
while(fread (&si, sizeof (si) ,1, fptr)==1)
{
if (strcmp (si.name, student_name)==0)
{
dataFound=1	;
printf("\nThe old record is:\n");
printf("Name\tAge\tSex\tClass\n");
printf ("\n");
printf("%s\t%d\t%c\t%d", si.name, si.age, si.sex, si.Class);
printf("\nEnter new name, age, sex and Class \t");
gets(si.name);
fflush(stdin);
si.sex=getchar();
fflush(stdin);
scanf("%d", &si.Class);
fseek(fptr,sizeof(si)*(recordNo),SEEK_SET);
if (fwrite (&si, sizeof(si),1,fptr)==1)
{
	printf("\n The record has been modified!!!!!\n");
break;
}
}
recordNo++;
}
if (dataFound==0)
printf ("\nMatching data not found!!!!!\n") ;
break;
case '4':
dataFound=0 ;
printf("Enter the name of student which is to be Searched!!!!\t");
fflush(stdin);
gets(student_name);
fseek ( fptr, 0, SEEK_SET);
while(fread(&si, sizeof(si) , 1, fptr)==1)
{
if (strcmp(si.name,student_name)==0)
{
dataFound=1;
printf("Name\tAge\tSex\tClass\n");
printf("\n");
printf("%s\t%d\t%c\t%d\n",si.name, si.age, si.sex, si.Class);
}
}
if(dataFound==0)
printf("No Data Found\n");
break;
case '5':
printf("\nEnter name of student to be deleted!!!!");
scanf("%s",student_name);
fptrTemp=fopen("d:\\temp.dat","wb");
rewind(fptr);
while(fread(&si,sizeof(si),1,fptr)==1)
{
if(strcmp(si.name, student_name)!=0)
{
fwrite(&si,sizeof(si),1,fptrTemp);
printf("\nDeleting......\n");
}
}
fclose(fptr);
fclose(fptrTemp);
remove("fileName");
rename("d:\\temp.dat",fileName);
fptr=fopen(fileName,"rb+");
printf("\nSuccessfully deleted...\n");
break;
case '6':
fclose(fptr);
printf ("\nExiting...");
getch ();
exit(1);
break;
default:
 printf("\nInvalid Character!!!!!!!!!");
}
}
return 0;
}
 