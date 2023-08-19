#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
int main()
{
	srand(time(NULL));
	char guessword[][16]={"world","yellow",	"purple","happy",	"banana","programm"};
	
	int randomindex=rand()%6;
	int numoflives=5;
	int numcorrect=0;
	int oldcorrect=0; 
	
	int wordlength=strlen(guessword[randomindex]);
	int letterguessed[8]={0,0,0,0,0,0,0,0};
	
	int quit=0;
	
	int loopindex=0;
	
	char guess[16];
	char enteredletter;
	
    printf(".....HANGMAN.....");
   /*printf("guessword:%s randomindex:%d wordlength%d\n",guessword[randomindex],randomindex,wordlength);*/

	
	
	 while(numcorrect<wordlength)
    {

     for(loopindex=0;loopindex<wordlength;loopindex++)
	{
		if(letterguessed[loopindex]==1)
		{
			printf("%c",guessword[randomindex][loopindex]);
		} else{
			printf("-");
		}
	}
	  printf("\n");
	
	printf("correct guesses:%d\n",numcorrect);
	printf("guess any letter:");
	fgets(guess,16,stdin);
	
	if(strncmp(guess,"quit",4)==0)
	{
		quit=1;
		break;
	}
	
	enteredletter=guess[0];
	printf("guessedletter:%c",enteredletter);
	       oldcorrect=numcorrect;
	
	for(loopindex=0;loopindex<wordlength;loopindex++);
	{
		if(letterguessed[loopindex]==1)
		{
			continue;
		}
		
		 if(enteredletter==guessword[randomindex][loopindex])
		{
			letterguessed[loopindex]=1;
			numcorrect++;
		}
		
	}
	 if(oldcorrect==numcorrect)
	 {
	 	numoflives--;
	 	printf("  wrong guess\n");
	 }
	 	
		 if(numoflives==0){
		break;
		 }
	 	
	 
	  else{
	  	printf("correct guess \n");
	  }
}
    if(quit==1) {
	printf("OUT OF GAME");
} else if(numoflives==0){
	printf("tries over! the word was:%s \n",guessword[randomindex]);
} else{
	printf("FINISH");
}


return 0;









}