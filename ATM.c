#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 //defining structure
typedef struct
{

  char name[15];

  int id;

  char cardNum[16];

  int pin;

  double balance;

  int isAdmin;

  int isActive;

} User;


//initialising global variables
int totalUsers = 10;

User user[10];

int existingUsers = 3;

int choice, userchoice;

char cardNumber[16];

int pinNumber, amount, depositAmount, confirmPinNumber;

double machineBalance = 100000;

int validUser = 0;

int validUserId = 0;

int invalidPinCount = 0;

int isLoggedIn = -1;

int minUserBalance = 500;

int minMachineBalance = 10000;


void getChoice ();

void validateChoice ();


int
main ()
{

  printf ("\n\n\n");

  //Preset data for testing
  strcpy (user[0].name, "user1");

  user[0].id = 0;

  strcpy (user[0].cardNum, "1111222233334444");

  user[0].pin = 1111;

  user[0].balance = 10000;

  user[0].isAdmin = 1;

  user[0].isActive = 1;

    /*******/
  strcpy (user[1].name, "user2");

  user[1].id = 1;

  strcpy (user[1].cardNum, "1111000022220000");

  user[1].pin = 2222;

  user[1].balance = 10000;

  user[1].isAdmin = 0;

  user[1].isActive = 1;

    /*******/
  
     strcpy(user[2].name,"user3");
     user[2].id=2;
     strcpy(user[2].cardNum,"1111000033330000");
     user[2].pin=3333;
     user[2].balance=10000;
     user[2].isAdmin=0;
     user[2].isActive=1;

   

  //int sp = 111;
  /*for(int i=0; i<totalUsers; i++){
     user.cardNum[i] = i+100;
     user.pin[i] = sp;
     user.Balance[i] = 10000;
     sp +=111;
     } */
  getChoice ();

  return 0;

}




void writeFile ();


void
writeFile ()
{

  FILE *fptr;


//if ((fptr = fopen ("D:\\my_files.txt", "w")) == NULL)
  if ((fptr = fopen ("D:\\my_files.txt", "a")) == NULL)
    {

      printf ("Error! opening file");


      // Program exits if the file pointer returns NULL.
      exit (1);

    }

  fprintf (fptr, "\nID: ");

  fprintf (fptr, "%d", user[validUserId].id);

  fprintf (fptr, "\n");

  fprintf (fptr, "Name: ");

  fprintf (fptr, "%s", user[validUserId].name);

  fprintf (fptr, "\n");

  fprintf (fptr, "Balance: ");

  fprintf (fptr, "%lf", user[validUserId].balance);

  fclose (fptr);

}



void loginUser ();

int
verifyLogin (char *cardNumber, int pinNumber)	//to check card and pin number is present in the struct
{

  for (int i = 0; i < totalUsers; i++)	//to check all the users
    {

      if (strcmp (cardNumber, user[i].cardNum))

	{
	  validUserId = i;

	  if (pinNumber == user[i].pin)

	    {

	      validUser = 1;


	      if (user[i].isAdmin)

		{

		  validUser = 2;

		}

	      return validUser;

	    }

	  else

	    {

	      if (invalidPinCount < 3)

		{

		  printf ("Enter valid pin number\n");

		  invalidPinCount++;

		}

	      else

		{

		  printf
		    ("You have entered incorrect pin for three times.\n Your account has been locked.\n");
		    //writeFile(user[validUserId]);

		  user[i].isActive = 0;

		}

	    }

	}

      else

	{

	  printf ("Card number not found.\n");

	  loginUser ();

	}

    }

  return validUser;

}


void
withDraw ()
{

  printf ("Enter withdrawal amount:");

  scanf ("%d", &amount);

  printf ("\n");

  if (amount <= (user[validUserId].balance - minUserBalance)
      && (amount < (machineBalance - minMachineBalance)))

    {

      user[validUserId].balance -= amount;

      machineBalance -= amount;

      printf ("Amount Withdrawal successfull\n");

      printf ("Balance amount :Rs %lf\n", user[validUserId].balance);

    }

  else

    {

      if (amount < (user[validUserId].balance - minUserBalance))

	{

	  printf
	    ("Your last transaction was not processed. Your available balance is Rs%lf\n",
	     user[validUserId].balance);

	  printf ("Minimum balance expected is Rs 500\n");

	}

      else

	{

	  printf ("Machine balance is Low.\n");

	}

    }
    writeFile(user[validUserId]);

}



void
deposit ()
{

  printf ("Enter amount to be deposited:");

  scanf ("%d", &depositAmount);

  printf ("\n");

  user[validUserId].balance += depositAmount;

  printf
    ("Amount deposited successfully.\nYour available balance is Rs %lf\n",
     user[validUserId].balance);

    writeFile(user[validUserId]);
}

void
checkBalance ()
{

  printf ("Your available Balance : Rs %lf\n", user[validUserId].balance);
    writeFile(user[validUserId]);
}

void
transfer ()
{

  
     int toAccount;
     printf("Select account to transfer\n");
     scanf("%d", &toAccount);
     printf("Enter transfer amount:");
     scanf("%d", &amount);
     printf("\n");
     if(amount<=(user[validUserId].balance-minUserBalance) && (amount<(machineBalance-minMachineBalance)))
     {
     user[toAccount].balance += amount;
     user[validUserId].balance -= amount;

     printf("successfull transfer \n");
     printf("Balance amount in from account %lf\n", user[validUserId].balance);
     printf("Balance amount in to account %lf\n", user[toAccount].balance);


     //user[validUserId].balance-=amount;
     //machineBalance-=amount;
     //printf("Amount Withdrawal successfull\n");
     //printf("Balance amount :Rs %lf\n",user[validUserId].balance);
     }
     else
     {
      if((user[validUserId].balance)-minUserBalance)
     {
     printf("Your last transaction was not processed. Your available balance is Rs%lf\n",user[validUserId].balance);
     printf("Minimum balance expected is Rs 500\n");
     }
      else
     {
     printf("Machine balance is Low.\n");
     }
     } 
     writeFile(user[validUserId]);
}

void logOut ();


void
requestPinChange ()
{

  printf ("Enter your current pin : \n");

  scanf ("%d", &pinNumber);

  if (user[validUserId].pin == pinNumber)

    {

      printf ("Enter new pin number\n");

      scanf ("%d", &pinNumber);

      printf ("Confirm new pin number\n");

      scanf ("%d", &confirmPinNumber);

      if (pinNumber == confirmPinNumber)

	{

	  user[validUserId].pin = confirmPinNumber;

	  printf ("Pin number successfully changed\n");

	}

      else

	{

	  printf ("Pin number is not matched.\nTry again later\n");

	}

      //logOut();
    }

  else

    {

      printf ("Your current pin is not matched.\nYou have been logged out");

    }

  logOut ();


}



void
checkMachineBalance ()
{

  printf ("Machine Balance : %lf\n", machineBalance);

}

void
usersBalance ()
{

  printf ("Users Balance details\n");

  for (int i = 0; i < existingUsers; i++)

    {

      if (user[i].isAdmin == 0)

	{

	  printf ("ID : %d\t Name : %s\t Balance : %lf\n", user[i].id,
		  user[i].name, user[i].balance);

	}

    }

}


void
lockUser ()
{

  printf ("User ID to be locked : ");

  int temp;

  scanf ("%d", &temp);		// user number
  printf ("\n");

  if (user[temp].isActive == 1)

    {

      user[temp].isActive = 0;

      printf ("User with %d is locked\n", temp);

    }

  else

    {

      printf ("User is already locked\n");

    }

}


void
makeAdmin ()
{

  printf ("User ID to make admin : ");

  int temp;

  scanf ("%d", &temp);

  printf ("\n");

  if (user[temp].isAdmin == 0)

    {

      user[temp].isActive = 1;

      printf ("User with %d is now admin\n", temp);

    }

  else

    {

      printf ("User is already admin\n");

    }

}


void
logOut ()
{

  isLoggedIn = -1;

  getChoice ();			// start 
}

void validateUserChoice (int userchoice);



void
normalUserLogin ()
{


  //void validateUserChoice();
  void validateUserChoice (userchoice)
  {

    switch (userchoice)

      {

      case 1:
	{

	  withDraw ();

	  normalUserLogin ();

	  break;

	}

      case 2:
	{

	  deposit ();

	  normalUserLogin ();

	  break;

	}

      case 3:
	{

	  checkBalance ();

	  normalUserLogin ();

	  break;

	}

      case 4:
	{

	  transfer ();

	  normalUserLogin ();

	  break;

	}

      case 5:
	{

	  requestPinChange ();

	  break;

	}

      case 6:
	{

	  logOut ();

	  break;

	}

      default:
	{

	  printf ("Enter valid Choice\n");

	  normalUserLogin ();

	  break;

	}

      }


  }


  printf
    ("User Menu \n 1. Withdraw\n 2. Deposit\n 3. Check balance\n 4. Transfer\n 5. Request PIN change\n 6. Logout\n");

  printf ("Enter the Choice\n");

  scanf ("%d", &userchoice);

  validateUserChoice (userchoice);

}



void validateAdminChoice (int userchoice);


void
adminUserLogin ()
{

  void validateAdminChoice (userchoice)
  {

    switch (userchoice)

      {

      case 1:
	{

	  usersBalance ();

	  adminUserLogin ();

	  break;

	}

      case 2:
	{

	  checkMachineBalance ();

	  adminUserLogin ();

	  break;

	}

      case 3:
	{

	  lockUser ();

	  adminUserLogin ();

	  break;

	}

      case 4:
	{

	  makeAdmin ();

	  adminUserLogin ();

	  break;

	}

      case 5:
	{

	  requestPinChange ();

	  break;

	}

      case 6:
	{

	  logOut ();

	  break;

	}

      default:
	{

	  printf ("Enter valid Choice\n");

	  adminUserLogin ();

	  break;

	}

      }


  }


  printf
    ("Admin Menu \n 1. Total Balance in each user.\n 2. Check Machine Balance.\n 3. Ability to lock user\n 4. Make admin\n 5. Request PIN change\n 6. Logout\n");

  printf ("Enter the Choice\n");

  scanf ("%d", &userchoice);

  validateAdminChoice (userchoice);

}





void
loginUser ()
{

  validUser = 0;		//to store the verifylogin value
  printf ("Enter valid card number to login\n");

  scanf ("%s", cardNumber);

  printf ("Enter pin number\n");

  scanf ("%d", &pinNumber);

  int isValid = verifyLogin (cardNumber, pinNumber);

  if (isValid)

    {

      printf ("Login successfull\n");

      // user with id = user[validUserId] has logged in.
      writeFile (user[validUserId]);

      isLoggedIn = user[validUserId].id;	// particular user (i) is logged in
      if (isValid == 1)

	{

	  //printf("inside one");
	  normalUserLogin ();

	}

      else

	{

	  adminUserLogin ();

	}

    }

  //if(cardNum == )
  //if(cardNum == User.cardNum){

  //}
  //writeFile();
}



void
quitfn ()
{

  printf ("Thank you for visiting\n");

}


void
getChoice ()
{

  if (machineBalance < minMachineBalance)

    {

      printf ("Sorry, Machine has low balance\n");

    }

  else

    {

      printf ("ATM - WELCOMES YOU\n");

      printf ("1) Login\n2) Quit\n");

      printf ("Enter the Choice\n");

      scanf ("%d", &choice);

      validateChoice (choice);

    }

}


void
validateChoice (int choice)
{

  switch (choice)

    {

    case 1:
      {

	loginUser ();

	break;

      }

    case 2:
      {

	quitfn ();

	break;

      }

    default:
      {

	printf ("Enter valid Choice\n");

	getChoice ();

	break;

      }

    }

}
