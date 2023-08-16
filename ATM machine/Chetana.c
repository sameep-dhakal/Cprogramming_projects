#include <stdio.h>
 
unsigned long amount=1000, deposit, withdraw;
int choice, pin, k;
char transaction ='y';
 
void main()
{
	while (pin != 1520)
	{
		printf("ENTER YOUR SECRET PIN NUMBER:");
		scanf("%d", &pin);
		if (pin != 1520)
		printf("PLEASE ENTER VALID PASSWORD\");
	}
	do
	{
		printf("********Welcome to ATM Service**************\");
		printf("1. Check Balance\");
		printf("2. Withdraw Cash\");
		printf("3. Deposit Cash\");
		printf("4. Quit\");
		printf("****************?**************************?*\\");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("\ YOUR BALANCE IN Rs : %lu ", amount);
			break;
		case 2:
			printf("\ ENTER THE AMOUNT TO WITHDRAW: ");
			scanf("%lu", &withdraw);
			if (withdraw % 100 != 0)
			{
				printf("\ PLEASE ENTER THE AMOUNT IN MULTIPLES OF 100");
			}
			else if (withdraw >(amount - 500))
			{
				printf("\ INSUFFICENT BALANCE");
			}
			else
			{
				amount = amount - withdraw;
				printf("\\ PLEASE COLLECT CASH");
				printf("\ YOUR CURRENT BALANCE IS%lu", amount);
			}
			break;
		case 3:
			printf("\ ENTER THE AMOUNT TO DEPOSIT");
			scanf("%lu", &deposit);
                        amount = amount + deposit;
			printf("YOUR BALANCE IS %lu", amount);
			break;
		case 4:
			printf("\ THANK U USING ATM");
			break;
		default:
			printf("\ INVALID CHOICE");
		}
		printf("\\\ DO U WISH TO HAVE ANOTHER TRANSCATION?(y/n): \");
		fflush(stdin);
		scanf("%c", &transaction);
		if (transaction == 'n'|| transaction == 'N')
                    k = 1;
	} while (!k);
	printf("\\ THANKS FOR USING OUT ATM SERVICE");
}