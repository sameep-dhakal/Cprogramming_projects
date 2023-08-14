//LIBRARY MANAGEMENT SYSYTEM
/*  BY APIL MARASENI and
       SANTOSH MAHATO KOIRI
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

struct Book
{
    int id;
    char bname[20];
    char author[20],date[12];
}b;

struct student
{
    char sname[20],bname[20],date[12];
    char faculty[15];
    int roll,id;

}s;
char filename[]="d://santosh/library.txt";
char filename1[]="d://santosh/issue.txt";
FILE *fp,*fptrTemp,*f;

void showoptions()
{
    printf("\tThe options are:\n");
    printf("\t1. Add new book \n");
    printf("\t2. Display all books\n");
    printf("\t3. Search a book\n");
    printf("\t4. Borrow(issue) a book\n");
    printf("\t5. Return a book\n");
    printf("\t6. Display issued books\n");
    printf("\t7. Remove a book\n");
    printf("\t8. Format the book file\n");
    printf("\t9. Modify a book's record\n");
    printf("\tf. Format the student file\n");
    printf("\t0. Exit\n");
}

int main()
{
    char choice;

    fp=fopen(filename,"r+b");
    if(fp==NULL)
    {
        fp=fopen(filename,"w+b");
        if(fp==NULL)
        {
            printf("\tBook File can not be created!!!!\n");
            exit(1);
        }
    }

    f=fopen(filename1,"r+b");
    if(f==NULL)
    {
        f=fopen(filename1,"w+b");
        if(f==NULL)
        {
            printf("\tStudent File can not be created!!!!\n");
            exit(1);
        }
    }

    while(1)
    {
        printf("\n\n***********Welcome to Library Management System*************\n");
        printf("\n\tWhat do you want to do ?\n");
        showoptions();
        printf("\n\tChoose your option:");
        choice=getch();
        printf("%c \n", choice);
        switch(choice)
        {
            case '0':
            return 0;
            break;

            case '1':
            addBook();
            break;

            case '2':
            displayBooks();
            break;

            case '3':
            searchBook();
            break;

            case '4':
            issueBook();
            break;

            case '5':
            returnBook();
            break;

            case '6':
            issuedBooks();
            break;

            case '7':
            del();
            break;

            case '8':
            formatbookfile();
			break;

			case '9':
            modify();
            break;

            case 'f':
            formatstudentfile();
            break;

            default :
            system("cls");
            printf("Invalid Choice. Please select a valid option.\n");
        }
    }
    return 0;
}

void addBook()
{
    system("cls");
    char date[12];
    time_t t=time(NULL);
    struct tm tm=*localtime(&t);
    sprintf(date,"%02d/%02d/%d",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
    strcpy(b.date,date);

    printf("Enter book id: ");
    scanf("%d",&b.id);
    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bname);
    printf("Enter author name: ");
    fflush(stdin);
    gets(b.author);
    fseek(fp,0,SEEK_END);
    fwrite(&b,sizeof(b),1,fp);
    printf("\nBook added successfully.\n\n");
}

void displayBooks()
{
    system("cls");
    fseek(fp,0,SEEK_SET);
    printf("\n----------------------------Available Books-----------------------------\n");
    printf("%-10s %-20s %-15s %s\n","Book id","Book Name","Author","Date");
    printf("-------------------------------------------------------------------------\n");
    while(fread(&b,sizeof(struct Book),1,fp)==1)
    {
        printf("%-10d %-20s %-15s %s\n",b.id,b.bname,b.author,b.date);
        printf("-------------------------------------------------------------------------\n");
    }
}

void del()
{
    int dataFound=0;
    char book_name[30];
    printf("\nEnter name of book to be deleted: ");
    fflush(stdin);
    scanf("%s",book_name);
    fptrTemp=fopen("d://santosh/temp.txt","wb");
    rewind(fp);
    while(fread(&b,sizeof(b),1,fp)==1)
    {
        if(strcmp(b.bname,book_name)!=0)
		{
			fwrite(&b,sizeof(b),1,fptrTemp);
			//printf("\nWriting..........\n");
		}
		else
            dataFound=1;
    }
    fclose(fp);
	fclose(fptrTemp);
	remove(filename);
	rename("d://santosh/temp.txt",filename);
	fp=fopen(filename,"r+b");
	if(dataFound==0)
		printf("NO Data found\n");
    else
        printf("\nSuccessfully deleted......\n");
}

void formatbookfile()
{
    fptrTemp=fopen("d://santosh/temp.txt","wb");
    fclose(fp);
    fclose(fptrTemp);
    remove(filename);
	rename("d://santosh/temp.txt",filename);
	fp=fopen(filename,"r+b");
	printf("\nSuccessfully deleted book file......\n");
}

void formatstudentfile()
{
    fptrTemp=fopen("d://santosh/temp.txt","wb");
    fclose(f);
    fclose(fptrTemp);
    remove(filename1);
	rename("d://santosh/temp.txt",filename1);
	f=fopen(filename1,"r+b");
	printf("\nSuccessfully deleted student file......\n");
}

void modify()
{
    int datafound=0,recordno=0,id;
    printf("Enter the id of book which is to be modified: ");
    scanf("%d",&id);
    rewind(fp);
    while(fread(&b,sizeof(b),1,fp)==1)
    {
        if(id==b.id)
        {
            datafound=1;
            printf("\n----------------------------Old_Record-----------------------------\n");
            printf("%-10s %-30s %-20s %s\n","Book id","Book Name","Author","Date");
            printf("---------------------------------------------------------------------\n");
            printf("%-10d %-30s %-20s %s\n",b.id,b.bname,b.author,b.date);
            printf("\nEnter new Book id, Book name, Author and Date:\t");
            scanf("%d",&b.id);
            fflush(stdin);
            gets(b.bname);
            fflush(stdin);
            gets(b.author);
            fseek(fp,sizeof(b)*(recordno),SEEK_SET);
            if(fwrite(&b,sizeof(b),1,fp)==1)
            {
                printf("\nThe record has been modified!!!\n");
                break;
            }
        }
        recordno++;
    }
    if(datafound==0)
        printf("Matching data not found!!!");
}

void searchBook()
{
    int dataFound=0,id;
    printf("\nEnter the id of book which is to be searched: ");
    scanf("%d",&id);
    fseek(fp,0,SEEK_SET);
    while(fread(&b,sizeof(b),1,fp)==1)
    {
        if(id==b.id)
        {
            dataFound=1;
            printf("\n***********************Book_Searched**********************\n");
            printf("%-10s %-20s %-20s %s\n","Book id","Book Name","Author","Date");
            printf("---------------------------------------------------------------------\n");
            printf("%-10d %-20s %-20s %s\n",b.id,b.bname,b.author,b.date);
            printf("---------------------------------------------------------------------\n");
        }
    }
    if(dataFound==0)
        printf("NO Data found\n");
}

void issueBook()
{
    int found = 0;
    char date[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(date, sizeof(date), "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, date);

    system("cls");
    fseek(fp, 0, SEEK_SET);

    printf("Enter book id to issue: ");
    scanf("%d", &s.id);

    while (fread(&b, sizeof(struct Book), 1, fp) == 1)
    {
        if (s.id == b.id)
        {
            found = 1;
            strcpy(s.bname,b.bname);
            //strncpy(s.bname, b.bname,sizeof(s.bname)-1);
            //s.bname[sizeof(s.bname) - 1] = '\0'; // Null-terminate the string
            break;
        }
    }

    if (!found)
    {
        printf("No book found with this id!!!\n");
        printf("Please try again!!!\n");
    }
    else
    {
        printf("Enter student name: ");
        fflush(stdin);
        gets(s.sname);
        //scanf("%s", s.sname); // Use scanf for single-word input

        printf("Enter student faculty: ");
        fflush(stdin);
        gets(s.faculty);
        //scanf("%s", s.faculty); // Use scanf for single-word input

        printf("Enter student roll: ");
        scanf("%d", &s.roll);

        fseek(f, 0, SEEK_END);
        fwrite(&s, sizeof(s), 1, f);

        printf("\nBook issued successfully.\n\n");
    }
}


void returnBook()
{
    int dataFound=0;
    int id;
    printf("\nEnter the id of book to be returned: ");
    scanf("%d",&id);
    fptrTemp=fopen("d://santosh/temp.txt","wb");
    rewind(f);
    while(fread(&s,sizeof(s),1,f)==1)
    {
        if(id!=s.id)
		{
			fwrite(&s,sizeof(s),1,fptrTemp);
			//printf("\nWriting..........\n");
		}
		else
            dataFound=1;
    }
    fclose(f);
	fclose(fptrTemp);
	remove(filename1);
	rename("d://santosh/temp.txt",filename1);
	f=fopen(filename1,"r+b");
	if(dataFound==0)
		printf("NO issued book found of this id!!!\n");
    else
        printf("\nBook returned......\n");
}

void issuedBooks()
{
    system("cls");
    fseek(f,0,SEEK_SET);
    printf("\n**************Issued_Book_List*******************\n");
    printf("%-10s %-15s %-15s %-10s %-20s %s\n","S.id","Name","Faculty","Roll","Book Name","Date");
    printf("------------------------------------------------------------------------------------\n");
    while(fread(&s,sizeof(struct student),1,f)==1)
    {
        printf("%-10d %-15s %-15s %-10d %-20s %s\n",s.id,s.sname,s.faculty,s.roll,s.bname,s.date);
        printf("---------------------------------------------------------------------------------\n");
    }
}
