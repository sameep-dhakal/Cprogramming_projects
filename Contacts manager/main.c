#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct Contacts{
    char name[40];
    int phone;
    char email[40];
};

void addContact(struct Contacts contact[],int *contactnum){
	system("cls");


	*contactnum=*contactnum+1;
	int n = *contactnum;
	struct Contacts newContact;

    printf("Enter Name: ");
    fflush(stdin);
    gets(newContact.name);
    printf("Enter phone number: ");
    fflush(stdin);
    scanf("%d",&newContact.phone);
    printf("Enter email: ");
    fflush(stdin);
    gets(newContact.email);

    contact[n]=newContact;


}

void deleteContact(struct Contacts contact[], int *contactnum){
    system("cls");

	char delName[40];
    printf("Enter full name of the contact to delete:\n");
    fflush(stdin);
    gets(delName);
    for(int i = 0; i < (*contactnum); i++){
    	if (strcmp(contact[i].name, delName)==0){
    		for(int j = i; j < (*contactnum) - 1; j++){
    			contact[j] = contact[j+1];
			}
			*contactnum = *contactnum-1;
			printf("\nContact deleted successfully!\n");
		}

	}
}


void viewContacts(struct Contacts contact[], int contactnum){
    system("cls");

    printf("Contacts\nName:\tPhone No.\tE-Mail\n");
    for(int i = 0; i < contactnum; i++){
        printf("%s\t%d\t%s\n",contact[i].name, contact[i].phone, contact[i].email);
    }
}

void saveContacts(struct Contacts contact[], int contactnum){
    FILE *file;
    file = fopen("contacts.txt", "w");
    for(int i=0;i<contactnum;i++){
        fwrite(&contact[i], sizeof(contact[i]), 1, file);
    }
    fclose(file);
}



int main(){
    FILE *fp;
    int option;
    fp = fopen("contacts.txt", "a+"); // open file in a+ mode so it is created if it doesn't exist
    struct Contacts contact[100] = {0};;
    int contactnum=0;

    if(fp==NULL){
        printf("\nUnable to open/create file.\n");
        exit(1);
    }
    else{
    	// load previous contacts of file into structure and count number of contacts
    	while(fscanf(fp, "%s %d %s", contact[contactnum].name, &contact[contactnum].phone, contact[contactnum].email)!= EOF){
    		contactnum++;
		}
	}
    fclose(fp);

    do{
    	system("cls");
        printf("\nMenu:\n");
        printf("[1] Add a Contact\n");
        printf("[2] Delete a Contact\n");
        printf("[3] View All Contacts\n");
        printf("[4] Exit\n");
        printf("\nSelect an option from the menu (1,2,3,4)\n");
        fflush(stdin);
        scanf("%d",&option);

        switch (option){
            case 1:
                addContact(contact, &contactnum);

                printf("Contact added successfully!\n\nPress any key to return to menu");

                getch();
                break;

            case 2:
                deleteContact(contact, &contactnum);

                printf("\nPress any key to return to menu");

                getch();
                break;

            case 3:
                viewContacts(contact, contactnum);

                printf("\nPress any key to return to menu");

                getch();
                break;

            case 4:
                saveContacts(contact, contactnum); // save contacts from structure to file before exiting
                printf("Exiting the program...\n");

                break;

            default:
                printf("Select a valid option\n");
        }


    }while(option!=4); // exit loop only when user gives exit command

    return 0;
    }

