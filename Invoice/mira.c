#include<stdio.h>
#include<string.h>

struct list
{
    int id;
    char itemName[30];
    int price;
};

// creating fuction to display bill
   void display(struct list l[] , int size , char cName[] , char cAddress[]){
    int total = 0;
    printf("\n\n\n\n");
    printf("\t Bursting Basket's Store \n");
    printf("\t-------------- \n");
    printf("\n");
    printf("Name : %s \t Address : %s \n" , cName , cAddress);
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("Id : %d\t", l[i].id);
        printf("Name : %s\t", l[i].itemName);
        printf("Price : %d\n", l[i].price);
        printf("------------------------------------------------\n");
        total += l[i].price;

    }
    printf("\t\tTotal : %d" , total);
    printf("\n\n");
    printf("\t Thankyou for visiting:) \n");
    printf("\n\n");

}

    int main()
    {
        printf("Welcome!!!\n");
        char Name[30];
        char Address[30];
        int totalItems;
        printf("Enter your name:\t");
        scanf(" %s" , &Name);
        printf("Enter your address:\t");
        scanf(" %s" , &Address);
        printf("Enter total items:\t");
        scanf("%d" , &totalItems);
        printf("\n");

    struct list l[totalItems];
    //inserting items
    for (int i = 0; i < totalItems; i++)
    {
        l[i].id = (i+1);
        printf("Enter %d item name \t" , i+1);
        scanf(" %s" , &l[i].itemName);
        printf("Enter price \t");
        scanf("%d" , &l[i].price);
    }
    display(l , totalItems , Name , Address);
 
}