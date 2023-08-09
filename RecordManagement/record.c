#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct family{
        char first_name[20];
        char last_name[20];
        char gender[6];
}fam;

typedef struct record{
    char first_name[20];
    char last_name[20];
    char dob[3][9];
    char gender[6];
    char religion[20];
    char address[3][20];
    long long phone_no;
    char email[100];
    char occupation[50];
    char married;
    int no_of_children;

    fam *parent,*spouse,*children;


}record;

record name(record);

record dob(record );

record address(record);

void record_family(fam *);

record record_all(record);

void display_info(record);



int main()
{

    record person;
    FILE *f;
    int cmd,found=0;
    char full_name[2][20];



    while (1){

        printf("\n1.Add record\n");
        printf("2.Show record(Enter 'Sambal Shrestha' or 'Raj Shrestha' when asked full name for sample records)\n");
        printf("3.Exit\n");

        printf("Which command(Input the corresponding S.N 1,2,3):");
        scanf("%d",&cmd);

        switch(cmd)
        {
        case 1:
            f = fopen("./records.txt","a");
            person = record_all(person);
            fwrite(&person,sizeof(record),1,f);
            fclose(f);
            break;

        case 2:
            f = fopen("./records.txt","r");

            printf("Enter full name of the person: ");
            scanf("%s %s",full_name[0],full_name[1]);

            while (fread(&person,sizeof(record),1,f))
            {
                if ((strcmp(person.first_name,full_name[0])==0) && (strcmp(person.last_name,full_name[1])==0)){
                    display_info(person);
                    found=1;
                }
            }
            if (!found)
                printf("No such record!");

            fclose(f);
            break;

        case 3:
            return 0;

        default:
            printf("Invalid command!");
            break;

    }
    }
    return 0;
}

record name (record p)
{
    printf("\nEnter your first name:");
    scanf("%s",p.first_name);

    printf("Enter your last name:");
    scanf("%s",p.last_name);

    return p;

}

record dob (record p)
{
    printf("\nEnter the month of your birth:");
    scanf("%s",p.dob[0]);

    printf("Enter the day of your birth:");
    scanf("%s",p.dob[1]);

    printf("Enter the year of your birth:");
    scanf("%s",p.dob[2]);

    return p;

}

record address(record p)
{
    printf("\nEnter the place:");
    scanf("%s",p.address[0]);

    printf("Enter the district:");
    scanf("%s",p.address[1]);

    printf("Enter the zone:");
    scanf("%s",p.address[2]);

    return p;

}

void record_family(fam *f)
{
    printf("Enter his/her first name:");
    scanf("%s",f->first_name);


    printf("Enter his/her last name:");
    scanf("%s",f->last_name);

    printf("Enter his/her gender:");
    scanf("%s",f->gender);

}

record record_all(record p){
    p = name(p);

    p = dob(p);

    printf("\nEnter your gender:");
    scanf("%s",p.gender);

    printf("Enter your religion:");
    scanf("%s",p.religion);

    p = address(p);

    printf("\nEnter your phone no:");
    scanf("%lld",&p.phone_no);

    printf("Enter your email:");
    fflush(stdin);
    scanf("%s",p.email);

    printf("Enter your occupation:");
    scanf("%s",p.occupation);

    p.parent = malloc(sizeof(fam));
    printf("\nEnter one of your parent data:\n");
    record_family(p.parent);


    printf("\nAre you married(y/n):");
    fflush(stdin);
    scanf("%c",&p.married);

    if (p.married == 'n')
        p.spouse = NULL;
    else{
        p.spouse = malloc(sizeof(fam));
        printf("Enter your wife data:\n");
        record_family(p.spouse);

    }

    printf("\nHow many children:");
    scanf("%d",&p.no_of_children);

    if (p.no_of_children == 0)
        p.children = NULL;
    else{
        p.children = malloc(sizeof(fam)*p.no_of_children);

        for (int i=0;i<p.no_of_children;i++){
            printf("\nEnter the data of your child %d:\n",i+1);
            record_family(&p.children[i]);
        }

    }

    return p;
}

void display_info(record p){

    printf("\n------------------------------------------------------------------------------------------------\n");
    printf("\nName: %s %s\n",p.first_name,p.last_name);
    printf("Born on: %s %s, %s\n",p.dob[0],p.dob[1],p.dob[2]);
    printf("Gender: %s and Religion: %s\n",p.gender,p.religion);
    printf("Lives at: %s %s, %s\n",p.address[0],p.address[1],p.address[2]);
    printf("Phone no: %lld, Email: %s and Occupation: %s\n",p.phone_no,p.email,p.occupation);

    printf("\nParent name: %s %s and Gender: %s\n",p.parent->first_name,p.parent->last_name,p.parent->gender);

    if (p.married == 'y')
        printf("\nWife name: %s %s and Gender: %s\n\n",p.spouse->first_name,p.spouse->last_name,p.spouse->gender);
    else
        printf("\nIs not married\n\n");

    if (p.no_of_children == 0)
        printf("No children\n");
    else{
        for (int i=0;i<p.no_of_children;i++){
            printf("Child %d name: %s %s and Gender: %s\n",i+1,p.children[i].first_name,p.children[i].last_name,p.children[i].gender);
        }
    }
    printf("\n------------------------------------------------------------------------------------------------\n");


}







