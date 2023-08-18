//TIC TAC TOE Game
//Also has the ability to store match history and display its gameboard

/*
AUTHORS
ACE079BCT006 Abhishek Pant
ACE079BCT020 Bimarsha Shrestha
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

//constant define
#define max 50
#define fname "gamedata.dat"

 int wincon[8][3] = {   {0, 1, 2},//2x2 array containing winning condition
                        {3, 4, 5},
                        {6, 7, 8},
                        {0, 3, 6},
                        {1, 4, 7},
                        {2, 5, 8},
                        {0, 4, 8},
                        {2, 4, 6}};

//global variables
int boardcon[9]={0}; //board array declaration

struct  gamedata //storage struct
{
    int matchno;
    char player1[30];
    char player2[30];
    int windata;
    int boarddata[9];
} game[max];

int currentmatchno()  //returns current match no
{
    int i=0;
    while (game[i].matchno!=0)
    {

        i++;
    }
    return i;
}

void iniboard() //initilize & reset board
    {
        int i;
        for (i=0;i<9;i++) boardcon[i] = 0;
    }

int moves() //return no of moves
{
    int n=0;
    int i;
    for (i=0;i<9;i++)
    {
        if (boardcon[i]==1 || boardcon[i]==2) n++;
    }
    return n;
}

char boardval(int n) //calculate O or X on board container array
{
    if (n==1) return 'O'; //O=PLAYER 1
    else if (n==2) return 'X'; //X=Player 2
    else return ' ';
}

void displayboard() //displays current board
{
    printf("---------------------\n");
    printf("| Game Board !!! |\n");
    printf("---------------------\n");
    printf("|%c|%c|%c|\n",boardval(boardcon[0]),boardval(boardcon[1]),boardval(boardcon[2]));
    printf("-------\n");
    printf("|%c|%c|%c|\n",boardval(boardcon[3]),boardval(boardcon[4]),boardval(boardcon[5]));
    printf("-------\n");
    printf("|%c|%c|%c|\n",boardval(boardcon[6]),boardval(boardcon[7]),boardval(boardcon[8]));
    printf("-------\n");
}

int inputcheck(int n) //check for input errors
{
    if(n>=1 && n<=9 && boardcon[n-1]==0)
    {
        return 1;
    }
    else
    {
            return 0;
    }
}

int checkwin() //check the win condition & result
{
    int i;
    for (i=0;i<8;i++)
    {
        int a = wincon[i][0];
        int b = wincon[i][1];
        int c = wincon[i][2];

        if (boardcon[a]==boardcon[b] && boardcon[b]==boardcon[c])
        {
            if (boardcon[a] == 1)
                return 1; // Player 'O' wins
            else if (boardcon[a] == 2)
                return 2; // Player 'X' wins
        }
    }

    return 0; // No winner or Draw
}

void loadfile() //creates and load data in file to struct
{
    FILE *fptr;
    fptr=fopen(fname,"rb");
    if(fptr==NULL) //for first time opening file
    {
        int i;
        for(i=0;i<max;i++) game[i].matchno=0;
        fptr=fopen(fname,"w+b");
        if(fptr==NULL)
        {
            printf("File no created!!!\n");
            exit(0);
        }
        else
        {
            fwrite(game,sizeof(struct gamedata),max,fptr);
            rewind(fptr);
            fread(game,sizeof(struct gamedata),max,fptr);
        }
    }
    else fread(game,sizeof(struct gamedata),max,fptr);
    fclose(fptr);
}

void storefile() //stores gamedata in struct to file
{
    FILE *fptr;
    fptr=fopen(fname,"wb");
    if(fptr==NULL)
    {
        printf("File not opened !!!");
        exit(0);
    }
    fwrite(game,sizeof(struct gamedata),max,fptr);
    fclose(fptr);
}

void clearfile() //clears file contents
{
    FILE *fptr;
    fptr=fopen(fname,"wb");
    if(fptr==NULL)
    {
        printf("File not created!!!\n");
        exit(0);
    }
    else fclose(fptr);
}

void printdata()
{
    int i;
    for (i=0;i<currentmatchno();i++)
    {
        printf("SN. %d\t%s Vs %s\tWinner is Player %d\n",game[i].matchno,game[i].player1,game[i].player2,game[i].windata);
    }
}

void printmatch(int n)
{
    printf("Match %d\n",n);
    printf("Player 1/O is %s\n",game[n-1].player1);
    printf("Player 2/X is %s\n",game[n-1].player2);
    printf("Winner is Player %d\n",game[n-1].windata);
    iniboard();
    for (int i=0;i<9;i++) boardcon[i]=game[n-1].boarddata[i];
    displayboard();
}
void gameon()
{
    int l0=0;
    int n=0;
    char p1[30];
    char p2[30];

    iniboard();

    printf("Enter Player 1(O) name: ");
    getchar();
    gets(p1);
    printf("Enter Player 2(X) name: ");
    gets(p2);

    while (l0!=1)
    {
            int l1=0;
            while(l1!=1)
            {

            displayboard();
            printf("Player 1/O turn [1-9] = ");
            scanf("%d",&n);
            system("cls");
            if (inputcheck(n)==1)
            {
            boardcon[n-1]=1;
            l1=1;
            }
            else
            {
            printf("Invalid Input.\n");
            }
            }
            if(checkwin()==1)
            {
                 printf("Player 1/O wins!\n");
                 displayboard();
                 l0=1;
                 continue;
            }
            if (moves()==9)
            {
                printf("Its Draw. \n");
                displayboard();
                l0=1;
                continue;
            }

            int l2=0;
            while(l2!=1)
            {

            displayboard();
            printf("Player 1/X turn [1-9] = ");
            scanf("%d",&n);
            system("cls");
            if (inputcheck(n)==1)
            {
            boardcon[n-1]=2;
            l2=1;
            }
            else
            {
            printf("Invalid Input.\n");
            }
            }
            if(checkwin()==2)
            {
                 printf("Player 2/X wins!\n");
                 displayboard();
                 l0=1;
                 continue;
            }
             if (moves()==9)
            {
                printf("Its Draw. \n");
                displayboard();
                l0=1;
                continue;
            }
    }

    loadfile();
    if (currentmatchno()==max) //check if file is filled
    {
        clearfile(); //resets if full
        loadfile();
    }
    int x=currentmatchno();
    game[x].matchno=x+1;
    game[x].windata=checkwin();
    strcpy(game[x].player1,p1);
    strcpy(game[x].player2,p2);
    for (int i=0;i<9;i++) game[x].boarddata[i]=boardcon[i];
    storefile();
    printf("Match Saved...\n");

}
int main()
{
    int loop0_terminate=0;
    int choice0;

    while (loop0_terminate!=1)
    {
        printf("--------------------------------\n");
        printf("| Tic Tac Toe !!!\n");
        printf("--------------------------------\n");
        printf("| 1. New Game\n");
        printf("| 2. View Game History\n");
        printf("| 3. Exit Game\n");
        printf("--------------------------------\n");
        printf(".....Enter your choice: ");

        scanf("%d", &choice0);

        switch (choice0)
        {
            case 1:
            system("cls");
            printf("Starting GAME .......\n");
            gameon();
            break;

            case 2:
            system("cls");
            int loop1_terminate=0;
            int choice1;
            while (loop1_terminate!=1)
            {
                printf("--------------------------------\n");
                printf("| HISTORY !!!\n");
                printf("--------------------------------\n");
                printf("| 1. View All History\n");
                printf("| 2. View Specific Game Board\n");
                printf("| 3. Clear History\n");
                printf("| 4. Exit to Main Menu\n");
                printf("--------------------------------\n");
                printf(".....Enter your choice: ");

                scanf("%d", &choice1);

                switch(choice1)
                {
                    case 1:
                    system("cls");
                    printf("Showing All History\n");
                    loadfile();
                    printdata();
                    break;

                    case 2:
                    int choice3;
                    system("cls");
                    printf("Showing All History\n");
                    loadfile();
                    printdata();
                    printf("Enter History No: ");
                    scanf("%d",&choice3);
                    system("cls");
                    printmatch(choice3);
                    break;

                    case 3:
                    system("cls");
                    printf("Clearing History......\n");
                    clearfile();
                    loop1_terminate=1;
                    break;

                    case 4:
                    system("cls");
                    loop1_terminate=1;
                    break;

                    default:
                    printf("Invalid choice. Try again.\n");
                    break;
                }
            }
            break;

            case 3:
            printf("Thanks For Playing...... \n");
            loop0_terminate=1;
            break;

            default:
            system("cls");
            printf("Invalid choice. Try again.\n");
            break;
        }
    }
    getch();
    return 0;
}

