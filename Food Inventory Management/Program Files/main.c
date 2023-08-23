//Main Project
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include<stdlib.h>

struct food{
    int sn;
    char items[35];
    int price;
};
int i, sum, choice;
struct details{
    char name[20];
    double Phone_no;
    char address[30];
    char landmark[30];
};

void mainmenu();
void customer();
void aboutus();
void veg();
void non_veg();
void cus_details(int);
void admin();

int main(){
    mainmenu();
    return 0;
}

void mainmenu(){
    system("cls");
    char de;
    up:
    printf("  \t#***************************************************************#\n");
    printf("\t\t\t WELCOME TO FOOD ORDER SYSTEM\n");
    printf("  \t#***************************************************************#\n\n");
    printf("\t\t   1.Customer Section \n\t\t   2.Administration Section \n\t\t   3.About Us \n\t\t   4.Exit\n");
    printf("\t\tEnter your choice-->  ");
    scanf("%d", &choice);

    if(choice==1){
        customer();
    }
    else if(choice==3){
        aboutus();
     }
    else if(choice==2){
        admin();
    }
    else if(choice==4){
    system("cls");
    printf("\n\n\n\n  \t\t#************************************************#\n");
    printf("\t\t\t\t THANK YOU !!!!\n");
    printf("\t\t\t\t Visit us Again\n");
    printf("  \t\t#************************************************#\n\n");
    getchar();
    getchar();
    }
    else{
        system("cls");
        printf("\n\t      Wrong Input!!");
        printf("\tPlease input correct option\n\n\n");
        goto up;
    }
}

void customer(){
    system("cls");
    printf("\n\tWELCOME TO CUSTOMER SECTION\n");
    printf("\n\tWe have following services for you::\n");
    printf("\t\t1.Veg food items\n\t\t2.Non-Veg food Items\n\t\t3.Back to main menu\n");
    printf("\t   Enter your choice-->  ");
    scanf("%d", &choice);

    if(choice==1){
        veg();
    }
    else if(choice==2){
       non_veg();
     }
    else if(choice==3){
        system("cls");
         mainmenu();
    }
    else{
        system("cls");
        printf("\n\t      Wrong Input!!");
        printf("\tPlease input correct option\n\n\n");
        customer();
    }
}

void veg(){
    system("cls");
    int qn, i=0, sum=0, pf[11];
    char ch;
    FILE *fps;
    struct food s1[11];
    printf("\t\t##WELCOME TO VEG SECTION##\n");
    cont:
    fps=fopen("Veg_list.txt","r");
    i=0;
    printf("\n\tWe have following veg items:");
    printf("\n\t   SN FOOD ITEMS        PRICE(Rs.)\n");
    while(!feof(fps)){
        fread(&s1,sizeof(struct food),1,fps);
        printf("\t   %d %s     %d\t\n", s1->sn, s1->items, s1->price);
        pf[i]=s1->price;
        i++;
    }
    printf("\t   Enter your choice-->  ");
    scanf("%d", &choice);
    if (choice>9){
        printf("\n\n\t\tWrong Input!!!\n\tPlease re-enter correct option.\n");
        goto cont;
    }
    printf("\t   Enter quantity-->  ");
    scanf("%d", &qn);
    sum= sum + pf[choice-1]*qn;
    fclose(fps);
    printf("\tDo you wanna order more?(Y)");
    getchar();
    scanf("%c", &ch);
    if(ch=='y'|| ch=='Y'){
        goto cont;
    }
        else
    printf("\n   Your total amount is %d. Please enter following details. \n", sum);
    cus_details(sum);
}

void non_veg(){
    system("cls");
    int qn, pf[11], sum=0;
    char ch;
    FILE *fps;
    struct food s1[11];
    printf("\t\t##WELCOME TO NON-VEG SECTION##\n");
    cont:
    i=0;
    fps=fopen("Non_Veg_list.txt","r");
    printf("\n\tWe have following non-veg items:");
    printf("\n\t   SN FOOD ITEMS        PRICE(Rs.)\n");
    while(!feof(fps)){
        fread(&s1,sizeof(struct food),1,fps);
        printf("\t   %d %s     %d\t\n", s1->sn, s1->items, s1->price);
        pf[i]=s1->price;
        i++;
    }
    printf("\t   Enter your choice-->  ");
    scanf("%d", &choice);
    if (choice>6){
        printf("\n\n\t\tWrong Input!!!\n\tPlease re-enter correct option.\n");
        goto cont;
    }
    printf("\t   Enter quantity-->  ");
    scanf("%d", &qn);
    sum= sum + pf[choice-1]*qn;
    fclose(fps);
    printf("\tDo you wanna order more?(Y)");
    getchar();
    scanf("%c", &ch);
    if(ch=='y'|| ch=='Y'){
        goto cont;
    }
    else
    printf("\n   Your total amount is %d. Please enter following details.\n", sum);
    cus_details(sum);
}
void cus_details(int total){
    struct details s1;
    printf("\tPlease Enter Your Name\t:");
    getchar();
    scanf("%[^\n]s", s1.name);
    //printf("%s", s1.name);
    printf("\tYour Phone Number::\t");
    getchar();
    scanf("%lf", &s1.Phone_no);
    printf("\tYour address::\t");
    getchar();
    scanf("%[^\n]s", s1.address);
    printf("\tYour landmark::\t");
    getchar();
    scanf("%[^\n]s", s1.landmark);
    FILE *nt;
    nt=fopen("details.txt","a");
    fprintf(nt,"Name: %s\nPhone no: %.0lf\nAddress: %s\nLandmark: %s\nTotal Sum: %d\n\n", s1.name,s1.Phone_no, s1.address,s1.landmark, total);
    fclose(nt);
    printf("\n \t\t Your order will be delivered within 30 minutes.!!");
    printf("\n\n We are going back to main menu. THANK YOU!!!\n Press enter key to continue\n");
    getchar();
    getchar();
    system("cls");
    mainmenu();
}

void aboutus(){
    system("cls");
    printf("\n\t\t\t  Hungry???\n");
    printf("\t\tGood, We are here to serve you..\n\t   Fresh and Hygenic food at your services .\n");
    printf("\tWe offer veg, non-veg food items at your door.!!");
    printf("\n\n\n\n\t\t\t  Contact us:\n");
    printf("\t\t WORLD OF UNPARALLELED FLAVORS\n");
    printf("\t\t   Phone no.= 01-2547282\n");
    printf("\t  Visit our website: www.foodworld.com.np\n");
    printf("\n\n\nPress enter key to go to mainmenu\n");
    getchar();
    getchar();
    mainmenu();
}

void admin(){
        char de;
        system("cls");
        up:
        printf("\t    ADMINISTRATION SECTION\n");
        printf("\n\t1.Customer Details \n\t2.Back to main menu\n");
        printf("\t Choose an option-->   ");
        scanf("%d", &i);
        if(i==1){
            FILE *np;
            np=fopen("details.txt","rt");
            while((de=getc(np))!=EOF){
                printf("%c",de);
            }
            printf("Press enter key to go to administration section\n");
        getchar();
        getchar();
        system("cls");
       // goto up;
       admin();
        }
        else if(i==2){
            mainmenu();
        }
        else{
            system("cls");
        printf("\n\t      Wrong Input!!");
        printf("\tPlease input correct option\n\n\n");
        goto up;
        }
}

