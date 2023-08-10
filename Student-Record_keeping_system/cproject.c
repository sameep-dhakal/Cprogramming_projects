#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct student{
	char name[30];
	int roll;
	char level[30];
	char programme[30];
	char gender;
	char section;
	char address[30];
	int age;
}st;

void ShowOptions();
void addrecords();
void displayrecord(); //To display only the specific record
void modify();
void deleterecord();
void displayall(); //To display each and every record from the file
void exiting();

FILE *fptr,*fptrTemp;

int main()
{
	int choice;
	fptr=fopen("students.txt","r+");
	if (fptr==NULL)
	{
		fptr=fopen("students.txt","w+");
		if (fptr==NULL)
		{
			printf("Unable to create the file");
			exit(1);
		}
	}
	while(1)
	{
		printf("\n ..........Welcome to Student Record Keeping System ...........\n");
		ShowOptions();
		scanf("%d",&choice);
		switch (choice)
		{
			case 1:
				addrecords();
				break;
			case 2:
				modify();
				break;
			case 3:
				displayrecord();
				break;
			case 4:
				deleterecord();
				break;
			case 5:
				displayall();
				break;
			case 6:
				exiting();
				break;
			default:
				printf("Invalid option");
			 
		}
	}
	fclose(fptr);
	getch();
	return 0;
}

void ShowOptions()    //This function is only to display the options
{
	printf("\nChoose your option\n");
	printf("1 Add new record\n");
	printf("2 Modify record\n");
	printf("3 Display specific record\n");
	printf("4 Delete record\n");
	printf("5 Display all the records\n");
	printf("6 Exit\n");
}

void addrecords()
{
	printf("\nEnter name:");
	fflush(stdin);
	gets(st.name);
	printf("Enter roll number: ");
	scanf("%d",&st.roll);
	printf("Enter level:");
	fflush(stdin);
	gets(st.level);
	fflush(stdin);
	printf("Enter the programme:");
	gets(st.programme);
	printf("Enter the gender(M/F):");
	st.gender=getche();
	printf("\nEnter section:");
	st.section=getche();
	fflush(stdin);
	printf("\nEnter address:");
	gets(st.address);
	printf("Enter age:");
	scanf("%d",&st.age);
	fwrite(&st,sizeof(st),1,fptr); 
	printf("\nRecord has been added successfully.\n");
}

void modify()
{
	int data_found,record_no;
	char std_name[30];
	printf("Enter the name of the student which is to be modified:");
	fflush(stdin);
	gets(std_name);
	rewind(fptr);
	data_found=0;
	record_no=0;
	while((fread(&st,sizeof(st),1,fptr))==1)
	{
		if(strcmp(st.name,std_name)==0)  /*searches if there is any matching data*/
		{
			data_found=1;
			printf("\nThe old record is:\n");
			printf("Name\t  | Roll no. | Level | Programme | Gender | Section | Address\t |Age\n");
			printf("-----------------------------------------------------------------\n");
			printf("%s\t| %d\t | %s\t | %s\t | %c\t | %c\t | %s\t | %d",st.name,st.roll,st.level,st.programme,st.gender,st.section,st.address,st.age);
			printf("\nEnter new name:");
			fflush(stdin);
			gets(st.name);
			printf("Enter new roll number: ");
			scanf("%d",&st.roll);
			printf("Enter new level:");
			fflush(stdin);
			gets(st.level);
			printf("Enter new programme");
			fflush(stdin);
			gets(st.programme);
			fflush(stdin);
			printf("Enter new gender(M/F):");
			st.gender=getche();
			printf("\nEnter new section:");
			st.section=getche();
			fflush(stdin);
			printf("\nEnter new address:");
			gets(st.address);
			printf("Enter new age:");
			scanf("%d",&st.age);
			fseek(fptr,sizeof(st)*(record_no),SEEK_SET);  /*sets the pointer to the beginning of the file*/
			if(fwrite(&st,sizeof(st),1,fptr)==1) 
			{
				printf("\nRecord has been modified successfully!!!\n");
				break;
			}
		}
		record_no++;
	}
	if(data_found==0)
	printf("\n Record not found");
}

void displayrecord()
{
	char stud_name[30];
	int datafound=0;
	printf("Enter the name of student whose record is to be displayed:");
	fflush(stdin);
	gets(stud_name);
	rewind(fptr);
	while((fread(&st,sizeof(st),1,fptr))==1)
	{
		if(strcmp(st.name,stud_name)==0)
		{
			datafound=1;
			printf("Name\t | Roll no. | Level | Programme | Gender | Section | Address\t |Age\n");
			printf("\n-----------------------------------------------------------------\n");
			printf("%s\t| %d\t | %s\t | %s\t | %c\t | %c \t | %s\t | %d",st.name,st.roll,st.level,st.programme,st.gender,st.section,st.address,st.age);
		}
	}
	if(datafound==0)
	printf("\nRecord not found.");
}

void deleterecord()
{
	char st_name[30];
	fflush(stdin);
	printf("Enter the name of student whose record is to be deleted");
	gets(st_name);
	fptrTemp=fopen("temp.txt","w");  /*opens a temporary file to store all the records except the one to be deleted*/
	rewind(fptr);
	while(fread(&st,sizeof(st),1,fptr)==1)
	{
		if(strcmp(st.name,st_name)!=0)
		{
			fwrite(&st,sizeof(st),1,fptrTemp); /*writes all the records except the one to be deleted in a new temporary file*/
			printf("\nWriting...............\n");
		}
	}
	fclose(fptr);
	fclose(fptrTemp);
	remove("students.txt"); /*removes the original file*/
	rename("temp.txt","students.txt");  /*renames the temporary file with the original filename*/
	fptr=fopen("students.txt","r+");
	printf("\nSuccessfully deleted.....\n");
}

void displayall()
{
	rewind(fptr);
	printf("Name\t | Roll no. | Level | Programme  | Gender | Section | Address\t | Age\n");
	while(fread(&st,sizeof(st),1,fptr)==1)
	{
		printf("\n-------------------------------------------------------------------------------\n");
		printf("%s\t| %d\t | %s\t | %s\t | %c\t| %c \t | %s\t | %d",st.name,st.roll,st.level,st.programme,st.gender,st.section,st.address,st.age);
		
	}
	printf("\n-----------------------------------------------------------------------------------\n");
}

void exiting()
{
	fclose(fptr);
	printf("\nExiting........................\n");
	getch();  /*Takes a character before exiting the program*/
	exit(0); /*exits the program with return value 0*/
}
