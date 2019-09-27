// Programmed by Michael Coleman - G00347650 - using visual studio 2015

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<conio.h>

struct node
{
	int passportNumber;
	char firstName[15];
	char lastName[15];
	int yearBorn;
	char emailAddress[30];
	char areaTravelledFrom[15];
	char travelClass[15];
	int tripsPerYear;
	int durationOfStay;
	struct node* NEXT;
};

typedef struct
{
	//area travelled from variables
	float uk=0.0;
	float rOE=0.0;
	float asia=0.0;
	float americas=0.0;
	float australasia=0.0;
	//days in Ireland variables
	float OneDay = 0.0;
	float lessThan3 = 0.0;
	float lessThan7 = 0.0;
	float moreThan7 = 0.0;
}percentages;

typedef struct
{
	//login variables
	char username1[15] = " ";
	char password1[7] = " ";;
	char username2[15] = " ";;
	char password2[7] = " ";;
	char username3[15] = " ";;
	char password3[7] = " ";;
}login;

//functions
void loadLoginDetails(login details);
void loadPassengerDetails(struct node** top);
void passengersInOrder(struct node* top);
void addPassengerToListStart(struct node** top);
void addPassengerAtListEnd(struct node* top);
void displayPassengerDetails(struct node* top);
void displayPassengers(struct node* top);
void EditDetails(struct node* top);
void deletePassengerAtStart(struct node** top);
void deletePassengerAtPassNum(struct node* top, int passnum);
void deletePassengerAtEnd(struct node* top);
int length(struct node* top);
int uniquePassport(struct node* top, int passangerNumber);
void getPercents(struct node* top, percentages percents, int choice);
void printPassengerDetailsToFile(struct node* top,int size);
void travelClassPercents(struct node* top, float ecoCount, float pecoCount, float busCount, float firstClassCount);
void ukPassengersInOrder(struct node* top);
struct node *copyLinkedList(struct node *old);


//main
void main()
{
	struct node* headPtr = NULL;
	int listOption;
	int passNum;
	int i;
	int found = 2;
	percentages percent;
	login logindetails;

	//load login to validate user
	loadLoginDetails(logindetails);

	//load passenger details from txt file into linked list
	loadPassengerDetails(&headPtr);
	passengersInOrder(headPtr);

	//user menu options
	printf("1) Add passenger(Note: Passport Number must be unique)\n");
	printf("2) Display all passengers to screen\n");
	printf("3) Display passenger Details\n");
	printf("4) Update a passenger statistic\n");
	printf("5) Delete passenger\n");
	printf("6) Passanger Statistics\n");
	printf("7) Print all passenger details into a report file\n");
	printf("8) List all the passengers of the following the UK in order of year born \n");
	printf("9) Exit \n");
	scanf("%d", &listOption);

	while (listOption != -1)
	{
		switch (listOption)
		{
		case 1:
			//add passengers
			if (headPtr == NULL)
			{
				//add passenger at start
				addPassengerToListStart(&headPtr);
			}
			else
			{
				//add passenger at end
				addPassengerAtListEnd(headPtr);
			}
			passengersInOrder(headPtr);
			break;
		case 2:
			//display all passengers
			displayPassengers(headPtr);
			break;

		case 3:
			//display specified passenger
			displayPassengerDetails(headPtr);
			break;
		case 4:
			//update passenger statistic
			EditDetails(headPtr);
			break;
		case 5:
			//select passport number you wish to delete from linked list
			printf("Enter the passenger's passport number you wish to delete\n");
			scanf("%d", &passNum);

			//no passengers exist in list
			if (headPtr == NULL) {
				printf("There are no passengers\n");
			}
			else if (passNum <= 1) {
				//delete passenger at start
				deletePassengerAtStart(&headPtr);
			}
			else if (passNum >= length(headPtr)) {
				//delete passenger at end
				deletePassengerAtEnd(headPtr);
			}
			else {
				//delete passenger at passport number
				deletePassengerAtPassNum(headPtr, passNum);
			}
			break;
		case 6:
			//show stats based on user selection
			int statsChoice;
			printf("Which category of passenger would you like information on:\n 1) Travel Class\n 2) Born before 1980\n");
			scanf("%d", &statsChoice);

			if (statsChoice == 1) {
				getPercents(headPtr, percent, statsChoice);
			}
			else if (statsChoice == 2) {
				getPercents(headPtr, percent, statsChoice);
			}
			else {
				printf("Invalid Option\n");
			}
			break;
		case 7:
			//print to file
			printPassengerDetailsToFile(headPtr, length(headPtr));
			break;
		case 8:
			//show passengers in order of birth from uk
			ukPassengersInOrder(headPtr);
			break;
		case 9:
			//exit application and print passengers to file
			printPassengerDetailsToFile(headPtr, length(headPtr));
			exit(EXIT_SUCCESS);
			break;
		default:
			printf("\nInvalid Input\n\n");
			break;
		}

		//user menu options
		printf("1) Add passenger(Note: Passport Number must be unique)\n");
		printf("2) Display all passengers to screen\n");
		printf("3) Display passenger Details\n");
		printf("4) Update a passenger statistic\n");
		printf("5) Delete passenger\n");
		printf("6) Passanger Statistics\n");
		printf("7) Print all passenger details into a report file\n");
		printf("8) List all the passengers of the following the UK in order of year born \n");
		printf("9) Exit \n");
		scanf("%d", &listOption);
	}
}

//function to validate user credentials via username and password
void loadLoginDetails(login details)
{
	int found = 2;
	int passfound = 2;
	char usernameAttempt[15];
	char passwordAttempt[7];
	FILE* file1;
	int index = 0;
	char c;

	//open file to read
	file1 = fopen("login.txt", "r");

	if (file1 == NULL)
	{
		printf("The file could not be opened\n");
	}

	else
	{
		while (!feof(file1))
		{
			//load from file into login struct
			fscanf(file1, "%s %s %s %s %s %s", details.username1, details.password1, details.username2, details.password2, details.username3, details.password3);
		}
		//close file
		fclose(file1);
	}

	//ask for username and password from user
	do {
		printf("Enter Username (Enter Quit to Exit):\n");
		scanf("%s", &usernameAttempt);
		//if usernames match contine to password
		if (stricmp(usernameAttempt, details.username1) == 0) {
			found = 1;
			//show * for password - appended from http://www.techcrashcourse.com/2016/02/c-program-to-read-password-string-as-input.html
			printf("Enter Password (Enter Quit to Exit):\n");
			/* 13 is ASCII value of Enter key */
			while ((c = getch()) != 13) {
				if (index < 0)
					index = 0;
				/* 8 is ASCII value of BACKSPACE character */
				if (c == 8) {
					putch('\b');
					putch(NULL);
					putch('\b');
					index--;
					continue;
				}
				passwordAttempt[index++] = c;
				putch('*');

				if (index > 6) {
					printf("\nPassword too Long, 6 characters max\n");
					exit(EXIT_SUCCESS);
				}
			}
			passwordAttempt[index] = '\0';
			//if passwords match - go to user menu
			if (stricmp(passwordAttempt, details.password1) == 0) {
				printf("\n");
				return;
			}
			else {
				//terminate in case of an incorrect password(security feature)
				printf("\n(Incorrect password - Program terminating):\n");
				exit(EXIT_SUCCESS);
			}
		}
		else if (stricmp(usernameAttempt, details.username2) == 0) {
			found = 1;
			//adapted from - http://www.techcrashcourse.com/2016/02/c-program-to-read-password-string-as-input.html
			printf("Enter Password (Enter Quit to Exit):\n");
			/* 13 is ASCII value of Enter key */
			while ((c = getch()) != 13) {
				if (index < 0)
					index = 0;
				/* 8 is ASCII value of BACKSPACE character */
				if (c == 8) {
					putch('\b');
					putch(NULL);
					putch('\b');
					index--;
					continue;
				}
				passwordAttempt[index++] = c;
				putch('*');

				if (index > 6) {
					printf("\nPassword too Long, 6 characters max\n");
					exit(EXIT_SUCCESS);
				}
			}
			passwordAttempt[index] = '\0';

			if (stricmp(passwordAttempt, details.password2) == 0) {
				printf("\n");
				return;
			}
			else {
				printf("\n(Incorrect password - Program terminating):\n");
				exit(EXIT_SUCCESS);
			}
		}
		else if (stricmp(usernameAttempt, details.username3) == 0) {
			found = 1;
			//adapted from - http://www.techcrashcourse.com/2016/02/c-program-to-read-password-string-as-input.html
			printf("Enter Password (Enter Quit to Exit):\n");
			/* 13 is ASCII value of Enter key */
			while ((c = getch()) != 13) {
				if (index < 0)
					index = 0;
				/* 8 is ASCII value of BACKSPACE character */
				if (c == 8) {
					putch('\b');
					putch(NULL);
					putch('\b');
					index--;
					continue;
				}
				passwordAttempt[index++] = c;
				putch('*');

				if (index > 6) {
					printf("\nPassword too Long, 6 characters max\n");
					exit(EXIT_SUCCESS);
				}
			}
			passwordAttempt[index] = '\0';

			if (stricmp(passwordAttempt, details.password3) == 0) {
				printf("\n");
				return;
			}
			else {
				printf("\n(Incorrect password - Program terminating):\n");
				exit(EXIT_SUCCESS);
			}
		}
		else if (stricmp(usernameAttempt, "Quit") == 0) {
			exit(EXIT_SUCCESS);
		}
		else {
			found = 0;
			printf("Invalid Username(Please Try Again):\n\n");
		}
	} while (found != 1);
}

//function to load passengers into linked list
void loadPassengerDetails(struct node** top)
{
	struct node* newNode;
	struct node* curr = *top;
	int size = 0;
	int i = 0;
	FILE* file1;

	int passNum = 0;
	char fName[15] = " ";
	char lName[15] = " ";
	int yB = 0;
	char email[30] = " ";
	char areaTF[15] = " ";
	char travelC[15] = " ";
	int tripsPY = 0;
	int duration = 0;

	//curr = (struct node*)malloc(sizeof(struct node) * 1);
	file1 = fopen("Passenger.txt", "r");

	if (file1 == NULL)
	{
		printf("The file could not be opened to read\n");
	}
	else {
		fscanf(file1, "%d ", &size);

		for (i = 0; i < size; i++)
		{
			newNode = (struct node*)malloc(sizeof(struct node) * 1);

			fscanf(file1, "%d ", &passNum);
			newNode->passportNumber = passNum;


			fscanf(file1, "%s %s ", fName, lName);
			strcpy(newNode->firstName, fName);
			strcpy(newNode->lastName, lName);

			fscanf(file1, "%d ", &yB);
			newNode->yearBorn = yB;

			fscanf(file1, "%s ", email);
			strcpy(newNode->emailAddress, email);

			fscanf(file1, "%s ", areaTF);
			strcpy(newNode->areaTravelledFrom, areaTF);

			fscanf(file1, "%s ", travelC);
			strcpy(newNode->travelClass, travelC);

			fscanf(file1, "%d ", &tripsPY);
			newNode->tripsPerYear = tripsPY;

			fscanf(file1, "%d ", &duration);
			newNode->durationOfStay = duration;
			if (i == 0) {
				//1st node in list
				newNode->NEXT = *top;
				*top = newNode;

				curr = *top;

			}
			else {
				while (curr->NEXT != NULL)
				{
					curr = curr->NEXT;
				}
				curr->NEXT = newNode;
				newNode->NEXT = NULL;
			}
		}
	}
	//close files
	fclose(file1);
}

//function to add passenegr to list start
void addPassengerToListStart(struct node** top)
{
	struct node* newNode;
	newNode = (struct node*)malloc(sizeof(struct node) * 1);

		printf("Please enter the passenger's passport Number:\n");
		scanf("%d", &newNode->passportNumber);
		printf("Please enter the passenger's first name:\n");
		scanf("%s", &newNode->firstName);
		printf("Please enter the passenger's last name:\n");
		scanf("%s", &newNode->lastName);
		printf("Please enter the passenger's Birth Year\n");
		scanf("%d", &newNode->yearBorn);
		//ensure email contains an '@' and .com
		do {
			printf("Please enter the passenger's Email Address(Must contain @ and .com):\n");
			scanf("%s", &newNode->emailAddress);
		} while ((strstr(newNode->emailAddress, "@") == NULL || strstr(newNode->emailAddress, ".com") == NULL));

		printf("Please enter the area which passanger travelled from:\n");
		scanf("%s", &newNode->areaTravelledFrom);
		printf("Please enter the passenger's travel class:\n");
		scanf("%s", &newNode->travelClass);
		printf("Please enter the trips taken to Ireland per year for passanger\n");
		scanf("%d", &newNode->tripsPerYear);
		printf("Please enter the duration of passanger's stay\n");
		scanf("%d", &newNode->durationOfStay);

		newNode->NEXT = *top;
		*top = newNode;
}

//function to add passenegr to list end
void addPassengerAtListEnd(struct node* top)
{
	struct node* curr;
	struct node* newNode;
	int i;
	int found=2;
	int count=0;
	curr = top;

	newNode = (struct node*)malloc(sizeof(struct node) * 1);

	printf("Please enter the passenger's Passport Number:\n");
	scanf("%d", &newNode->passportNumber);
	//ensure passenger number is unique
	while (found != 0) {
		found = uniquePassport(curr,newNode->passportNumber);

		if (found == 1) {
			printf("Please enter the passenger's Passport Number:\n");
			scanf("%d", &newNode->passportNumber);
		}
	}
	printf("Please enter the passenger's First Name:\n");
	scanf("%s", &newNode->firstName);
	printf("Please enter the passenger's Last Name:\n");
	scanf("%s", &newNode->lastName);
	printf("Please enter the passenger's Birth Year\n");
	scanf("%d", &newNode->yearBorn);
	//ensure email contains an '@' and .com
	do {
		printf("Please enter the passenger's Email Address(Must contain @ and .com):\n");
		scanf("%s", &newNode->emailAddress);
	} while ((strstr(newNode->emailAddress, "@") == NULL || strstr(newNode->emailAddress, ".com") == NULL));
	printf("Please enter the the area which passenger travelled from:\n");
	scanf("%s", &newNode->areaTravelledFrom);
	printf("Please enter the passenger's travel class:\n");
	scanf("%s", &newNode->travelClass);
	printf("Please enter the trips taken to Ireland per year for passenger\n");
	scanf("%d", &newNode->tripsPerYear);
	printf("Please enter the duration of passenger's stay\n");
	scanf("%d", &newNode->durationOfStay);	

	curr = top;

	while (curr->NEXT != NULL)
	{
		curr = curr->NEXT;
	}
	curr->NEXT = newNode;
	newNode->NEXT = NULL;
}

//function to ensure that passport number entered is unique
int uniquePassport(struct node* top, int passangerNumber)
{
	struct node* curr;
	int found = 0;
	curr = top;

	while (curr)
	{
		if (passangerNumber == curr->passportNumber)
		{
			found = 1;
		}
		curr = curr->NEXT;

	}
	if (found == 1) {
		printf("Passanger already exists\n");
	}
	return found;
}

//function to list passengers in order of passport number
void passengersInOrder(struct node* top)
{
	struct node *i, *j, *curr;
	int temp;
	char names[15];
	char emailAddress[30];
	char tempArAndClass[15];

	int tripsPerYear;
	int durationOfStay;

	curr = top;

	//swap elements of linked list based on passport number
	for (i = curr; i->NEXT != NULL; i = i->NEXT) {
		for (j = i->NEXT; j != NULL; j = j->NEXT) {
			//swap elements based on if passport number is larger than the other
			if (i->passportNumber > j->passportNumber) {

				//swap elements in lists
				temp = i->passportNumber;
				i->passportNumber = j->passportNumber;
				j->passportNumber = temp;

				strcpy(names, i->firstName);
				strcpy(i->firstName, j->firstName);
				strcpy(j->firstName, names);

				strcpy(names, i->lastName);
				strcpy(i->lastName, j->lastName);
				strcpy(j->lastName, names);

				temp = i->yearBorn;
				i->yearBorn = j->yearBorn;
				j->yearBorn = temp;

				strcpy(emailAddress, i->emailAddress);
				strcpy(i->emailAddress, j->emailAddress);
				strcpy(j->emailAddress, emailAddress);

				strcpy(tempArAndClass, i->areaTravelledFrom);
				strcpy(i->areaTravelledFrom, j->areaTravelledFrom);
				strcpy(j->areaTravelledFrom, tempArAndClass);

				strcpy(tempArAndClass, i->travelClass);
				strcpy(i->travelClass, j->travelClass);
				strcpy(j->travelClass, tempArAndClass);

				temp = i->tripsPerYear;
				i->tripsPerYear = j->tripsPerYear;
				j->tripsPerYear = temp;

				temp = i->durationOfStay;
				i->durationOfStay = j->durationOfStay;
				j->durationOfStay = temp;

			}
		}
	}
}

//function to display all passengers in list
void displayPassengers(struct node* top)
{
	struct node* curr;

	curr = top;
	if (curr == NULL)
	{
		printf("There are no Passengers\n");
		return;
	}
	printf("\nPassenger Details\n");
	printf("=============================\n");
	while (curr != NULL)
	{
		//display info associated with user
		printf("Passport Number: %d\n", curr->passportNumber);
		printf("Name: %s %s\n", curr->firstName, curr->lastName);
		printf("Birth Year: %d\n", curr->yearBorn);
		printf("E-Mail: %s\n", curr->emailAddress);
		printf("Travelled from: %s\n", curr->areaTravelledFrom);
		printf("Travel Class: %s\n", curr->travelClass);
		printf("Trips to Ireland per year: %d\n", curr->tripsPerYear);
		printf("Duration of Stay %d\n", curr->durationOfStay);

		printf("=============================\n");

		curr = curr->NEXT;
	}
}

//function to display specified passengers in list based on passenger number entered
void displayPassengerDetails(struct node* top) {
	struct node* curr;
	int passNo=0;
	int found=0;

	curr = top;

	if (curr == NULL)
	{
		printf("There are no Passengers\n");
		return;
	}

	printf("Please enter Passenger Passport Number:\n");
	scanf("%d", &passNo);

	//runs for duration of linked list
	while (curr)
	{
		if (passNo == curr->passportNumber)
		{
			//display info associated with users passport number
			printf("Passport Number: %d\n", curr->passportNumber);
			printf("Name: %s %s\n", curr->firstName, curr->lastName);
			printf("Birth Year: %d\n", curr->yearBorn);
			printf("E-Mail: %s\n", curr->emailAddress);
			printf("Travelled from: %s\n", curr->areaTravelledFrom);
			printf("Travel Class: %s\n", curr->travelClass);
			printf("Trips to Ireland per year: %d\n", curr->tripsPerYear);
			printf("Duration of Stay %d\n", curr->durationOfStay);
			found = 1;
			break;
		}
		curr = curr->NEXT;
	}
	if (found == 0) {
		printf("Passenger doesn't exist\n");
	}
}

//function to edit details of a user e.g. email address
void EditDetails(struct node* top)
{
	struct node* curr;
	int found=0;
	int passNo;

	curr = top;

	if (curr == NULL)
	{
		printf("There are no Passengers\n");
		return;
	}

	printf("Please enter Passenger Passport Number:\n");
	scanf("%d", &passNo);

	while (curr)
	{
		if (passNo == curr->passportNumber)
		{
			printf("Please enter the new email Address:\n");
			scanf("%s", &curr->emailAddress);
			printf("Please enter the new area travelled from:\n");
			scanf("%s", &curr->areaTravelledFrom);
			printf("Please enter the new travel class:\n");
			scanf("%s", &curr->travelClass);
			printf("Please enter the new duration of stay:\n");
			scanf("%d", &curr->durationOfStay);
			found = 1;
			break;
		}
		curr = curr->NEXT;

	}
	if (found==0) {
		printf("Passanger doesn't exist\n");
	}
}
//function to delete passenger at start
void deletePassengerAtStart(struct node** top)
{
	struct node* temp;

	temp = *top;

	*top = temp->NEXT;

	free(temp);
	printf("Passenger Deleted\n");
}
//function to delete passenger based on passport number
void deletePassengerAtPassNum(struct node* top, int passNum)
{
	struct node* temp;
	struct node* prev;
	int i;
	int found = 0;

	temp = top;

	while (temp)
	{
		//loop to see if passport number is in list
		if (temp->passportNumber == passNum) {
			found = 1;
		}
		temp = temp->NEXT;
	}
	//passport number not found
	if (found == 0) {
		printf("passport number not found");
		return;
	}

	temp = top;
	//loop until passNum encountered
	while(temp->passportNumber != passNum)
	{
		prev = temp;
		temp = temp->NEXT;
	}

	prev->NEXT = temp->NEXT;
	//release memory
	free(temp);
	printf("Passenger Deleted\n");
}

//function to delete end passenger
void deletePassengerAtEnd(struct node* top)
{
	struct node* curr;
	struct node* prev_curr;

	curr = top;

	while (curr->NEXT != NULL)
	{
		prev_curr = curr;
		curr = curr->NEXT;
	}

	prev_curr->NEXT = NULL;
	free(curr);
	printf("Passenger Deleted\n");
}

//function to get statistics for users choice of passengers
void getPercents(struct node* top, percentages percents, int choice)
{
	struct node* curr;
	float areaCount = 0;
	float arUkCount = 0;
	float arROECount = 0;
	float arAsiaCount = 0;
	float arAmericasCount = 0;
	float arAustralasiaCount = 0;
	float arDayOneCount = 0;
	float arDayThreeCount = 0;
	float arDaySevenCount = 0;
	float arMoreThanSevenCount = 0;
	float arDaysInIrelandCount = 0;
	float travelClassCount = 0;
	float ecoCount=0;
	float pecoCount = 0;
	float busCount = 0;
	float firstClassCount = 0;

	curr = top;
	if (curr == NULL)
	{
		printf("There are no Passengers\n");
		return;
	}

	//Display stats based on users travel class
	if (choice == 1) {
		while (curr)
		{
			//found economy - increase count
			if (stricmp(curr->travelClass, "economy") == 0)
			{
				ecoCount++;
			}
			//found Premium - increase count
			else if (stricmp(curr->travelClass, "Premium") == 0)
			{
				pecoCount++;
			}
			//found business - increase count
			else if (stricmp(curr->travelClass, "business") == 0)
			{
				busCount++;
			}
			//found firstclass - increase count
			else if (stricmp(curr->travelClass, "firstclass") == 0)
			{
				firstClassCount++;
			}

			curr = curr->NEXT;
		}
		//use travelclass function to get results for users choice of travel class
		travelClassPercents(top, ecoCount, pecoCount, busCount, firstClassCount);
	}

	//Display stats based on users born before 1980
	else {
		while (curr)
		{
			if (curr->yearBorn < 1980)
			{
				//compare strings - case insensitive - Increase counts when found
				if (stricmp(curr->areaTravelledFrom, "UK") == 0)
				{
					arUkCount++;
					areaCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "RestofEurope") == 0)
				{
					arROECount++;
					areaCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Asia") == 0)
				{
					arAsiaCount++;
					areaCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Americas") == 0)
				{
					arAmericasCount++;
					areaCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Australasia") == 0)
				{
					arAustralasiaCount++;
					areaCount++;
				}
				else {
					areaCount++;
				}
				//calculate days staying per year percentages
				if (curr->durationOfStay == 1)
				{
					arDayOneCount++;
					arDaysInIrelandCount++;
				}
				else if (curr->durationOfStay <= 3 && curr->durationOfStay > 1) {
					arDayThreeCount++;
					arDaysInIrelandCount++;
				}
				else if (curr->durationOfStay <= 7 && curr->durationOfStay > 3) {
					arDaySevenCount++;
					arDaysInIrelandCount++;
				}
				else if (curr->durationOfStay > 7) {
					arMoreThanSevenCount++;
					arDaysInIrelandCount++;
				}
				else {
					arDaysInIrelandCount++;
				}
			}


			curr = curr->NEXT;
		}
		//calculate percentages
		percents.uk = (arUkCount / areaCount) * 100;
		percents.rOE = (arROECount / areaCount) * 100;
		percents.asia = (arAsiaCount / areaCount) * 100;
		percents.americas = (arAmericasCount / areaCount) * 100;
		percents.australasia = (arAustralasiaCount / areaCount) * 100;

		//output travel area percentages
		printf("Total Number of passenger born before 1980 is: %.0f\n", areaCount);
		printf("\nPercentages of passengers born before 1980 from:\n");
		printf("UK: %.2f\n", percents.uk);
		printf("Rest of Europe: %.2f\n", percents.rOE);
		printf("Asia: %.2f\n", percents.asia);
		printf("Americas: %.2f\n", percents.americas);
		printf("Australasia: %.2f\n", percents.australasia);
		
		//calculate percentages
		percents.OneDay = (arDayOneCount / arDaysInIrelandCount) * 100;
		percents.lessThan3 = (arDayThreeCount / arDaysInIrelandCount) * 100;
		percents.lessThan7 = (arDaySevenCount / arDaysInIrelandCount) * 100;
		percents.moreThan7 = (arMoreThanSevenCount / arDaysInIrelandCount) * 100;

		//output avg days percentages
		printf("\nPercentages of passengers born before 1980 - days in Ireland:\n");
		printf("One Day: %.2f\n", percents.OneDay);
		printf("Less than 3: %.2f\n", percents.lessThan3);
		printf("Less than 7: %.2f\n", percents.lessThan7);
		printf("More than 7: %.2f\n\n", percents.moreThan7);
	}
}

//function to calculate percents of statistics for passengers based on travel class user selects
void travelClassPercents(struct node* top, float ecoCount, float pecoCount, float busCount, float firstClassCount)
{
	struct node* curr;
	curr = top;
	float travelClassCount = 0;
	float UkCount = 0;
	float ROECount = 0;
	float AsiaCount = 0;
	float AmericasCount = 0;
	float AustralasiaCount = 0;
	float DayOneCount = 0;
	float DayThreeCount = 0;
	float DaySevenCount = 0;
	float MoreThanSevenCount = 0;
	float DaysInIrelandCount = 0;
	int statsClass=0;

	//request user choose a travel class
	do {
		printf("Please enter travel class you wish to view statistics on:\n 1)Economy \n 2)Premium Economy \n 3)Business \n 4)First Class\n");
		scanf("%d", &statsClass);
	} while (statsClass != 1 && statsClass != 2 && statsClass != 3 && statsClass != 4);

	// calculate economy stats
	if (statsClass == 1) {
		while(curr){
				if (stricmp(curr->travelClass, "Economy") == 0) {
						if (stricmp(curr->areaTravelledFrom, "UK") == 0)
						{
							UkCount++;
							travelClassCount++;
						}
						else if (stricmp(curr->areaTravelledFrom, "RestofEurope") == 0)
						{
							ROECount++;
							travelClassCount++;
						}
						else if (stricmp(curr->areaTravelledFrom, "Asia") == 0)
						{
							AsiaCount++;
							travelClassCount++;
						}
						else if (stricmp(curr->areaTravelledFrom, "Americas") == 0)
						{
							AmericasCount++;
							travelClassCount++;
						}
						else if (stricmp(curr->areaTravelledFrom, "Australasia") == 0)
						{
							AustralasiaCount++;
							travelClassCount++;
						}
						else {
							travelClassCount++;
						}

						//calculate days per year percentages
						if (curr->durationOfStay == 1)
						{
							DayOneCount++;
						}
						else if (curr->durationOfStay <= 3 && curr->durationOfStay > 1) {
							DayThreeCount++;
						}
						else if (curr->durationOfStay <= 7 && curr->durationOfStay > 3) {
							DaySevenCount++;
						}
						else if (curr->durationOfStay > 7) {
							MoreThanSevenCount++;
						}
						curr = curr->NEXT;
					}
				else {
					curr = curr->NEXT;
				}
			}
		//calculate percentages
		float uk = (UkCount / ecoCount) * 100;
		float rOE = (ROECount / ecoCount) * 100;
		float asia = (AsiaCount / ecoCount) * 100;
		float americas = (AmericasCount / ecoCount) * 100;
		float australasia = (AustralasiaCount / ecoCount) * 100;

		//output travel area percentages
		printf("Total Number of passengers in Economy is: %.0f\n" ,ecoCount);
		printf("\nPercentages of passengers from:\n");
		printf("UK: %.2f\n", uk);
		printf("Rest of Europe: %.2f\n", rOE);
		printf("Asia: %.2f\n", asia);
		printf("Americas: %.2f\n", americas);
		printf("Australasia: %.2f\n", australasia);

		//calculate percentages
		float oneDay = (DayOneCount / ecoCount) * 100;
		float lessThan3 = (DayThreeCount / ecoCount) * 100;
		float lessThan7 = (DaySevenCount / ecoCount) * 100;
		float moreThan7 = (MoreThanSevenCount / ecoCount) * 100;

		//output avg days percentages
		printf("\nPercentages of passengers - days in Ireland:\n");
		printf("One Day: %.2f\n", oneDay);
		printf("Less than 3: %.2f\n", lessThan3);
		printf("Less than 7: %.2f\n", lessThan7);
		printf("More than 7: %.2f\n\n", moreThan7);
	}

	// calculate premium stats
	else if (statsClass == 2) {
		while (curr) {
			if (stricmp(curr->travelClass, "Premium") == 0) {
				if (stricmp(curr->areaTravelledFrom, "UK") == 0)
				{
					UkCount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "RestofEurope") == 0)
				{
					ROECount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Asia") == 0)
				{
					AsiaCount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Americas") == 0)
				{
					AmericasCount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Australasia") == 0)
				{
					AustralasiaCount++;
					travelClassCount++;
				}
				else {
					travelClassCount++;

				}
				//calculate days per year percentages
				if (curr->durationOfStay == 1)
				{
					DayOneCount++;
				}
				else if (curr->durationOfStay <= 3 && curr->durationOfStay > 1) {
					DayThreeCount++;
				}
				else if (curr->durationOfStay <= 7 && curr->durationOfStay > 3) {
					DaySevenCount++;
				}
				else if (curr->durationOfStay > 7) {
					MoreThanSevenCount++;
				}
				curr = curr->NEXT;
			}
			else {
				curr = curr->NEXT;
			}
		}
		//calculate percentages
		float uk = (UkCount / pecoCount) * 100;
		float rOE = (ROECount / pecoCount) * 100;
		float asia = (AsiaCount / pecoCount) * 100;
		float americas = (AmericasCount / pecoCount) * 100;
		float australasia = (AustralasiaCount / pecoCount) * 100;

		//output travel area percentages
		printf("Total Number of passengers in Premium Economy is: %.0f\n", pecoCount);
		printf("\nPercentages of passengers from:\n");
		printf("UK: %.2f\n", uk);
		printf("Rest of Europe: %.2f\n", rOE);
		printf("Asia: %.2f\n", asia);
		printf("Americas: %.2f\n", americas);
		printf("Australasia: %.2f\n", australasia);

		//calculate percentages
		float oneDay = (DayOneCount / pecoCount) * 100;
		float lessThan3 = (DayThreeCount / pecoCount) * 100;
		float lessThan7 = (DaySevenCount / pecoCount) * 100;
		float moreThan7 = (MoreThanSevenCount / pecoCount) * 100;

		//output avg days percentages
		printf("\nPercentages of passengers - days in Ireland:\n");
		printf("One Day: %.2f\n", oneDay);
		printf("Less than 3: %.2f\n", lessThan3);
		printf("Less than 7: %.2f\n", lessThan7);
		printf("More than 7: %.2f\n\n", moreThan7);
	}

	// calculate business stats
	else if (statsClass == 3) {
		while (curr) {
			if (stricmp(curr->travelClass, "Business") == 0) {
				if (stricmp(curr->areaTravelledFrom, "UK") == 0)
				{
					UkCount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "RestofEurope") == 0)
				{
					ROECount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Asia") == 0)
				{
					AsiaCount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Americas") == 0)
				{
					AmericasCount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Australasia") == 0)
				{
					AustralasiaCount++;
					travelClassCount++;
				}
				else {
					travelClassCount++;

				}
				//calculate days per year percentages
				if (curr->durationOfStay == 1)
				{
					DayOneCount++;
				}
				else if (curr->durationOfStay <= 3 && curr->durationOfStay > 1) {
					DayThreeCount++;
				}
				else if (curr->durationOfStay <= 7 && curr->durationOfStay > 3) {
					DaySevenCount++;
				}
				else if (curr->durationOfStay > 7) {
					MoreThanSevenCount++;
				}
				curr = curr->NEXT;
			}
			else {
				curr = curr->NEXT;
			}
		}
		//calculate percentages
		float uk = (UkCount / busCount) * 100;
		float rOE = (ROECount / busCount) * 100;
		float asia = (AsiaCount / busCount) * 100;
		float americas = (AmericasCount / busCount) * 100;
		float australasia = (AustralasiaCount / busCount) * 100;

		//output travel area percentages
		printf("Total Number of passengers in Business Class is: %.0f\n", busCount);
		printf("\nPercentages of passengers from:\n");
		printf("UK: %.2f\n", uk);
		printf("Rest of Europe: %.2f\n", rOE);
		printf("Asia: %.2f\n", asia);
		printf("Americas: %.2f\n", americas);
		printf("Australasia: %.2f\n", australasia);

		//calculate percentages
		float oneDay = (DayOneCount / busCount) * 100;
		float lessThan3 = (DayThreeCount / busCount) * 100;
		float lessThan7 = (DaySevenCount / busCount) * 100;
		float moreThan7 = (MoreThanSevenCount / busCount) * 100;

		//output avg days percentages
		printf("\nPercentages of passengers - days in Ireland:\n");
		printf("One Day: %.2f\n", oneDay);
		printf("Less than 3: %.2f\n", lessThan3);
		printf("Less than 7: %.2f\n", lessThan7);
		printf("More than 7: %.2f\n\n", moreThan7);
	}

	// calculate first class stats
	else if (statsClass == 4) {
		while (curr) {
			if (stricmp(curr->travelClass, "firstClass") == 0) {
				if (stricmp(curr->areaTravelledFrom, "UK") == 0)
				{
					UkCount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "RestofEurope") == 0)
				{
					ROECount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Asia") == 0)
				{
					AsiaCount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Americas") == 0)
				{
					AmericasCount++;
					travelClassCount++;
				}
				else if (stricmp(curr->areaTravelledFrom, "Australasia") == 0)
				{
					AustralasiaCount++;
					travelClassCount++;
				}
				else {
					travelClassCount++;

				}
				//calculate trips per year percentages
				if (curr->durationOfStay == 1)
				{
					DayOneCount++;
				}
				else if (curr->durationOfStay <= 3 && curr->durationOfStay > 1) {
					DayThreeCount++;
				}
				else if (curr->durationOfStay <= 7 && curr->durationOfStay > 3) {
					DaySevenCount++;
				}
				else if (curr->durationOfStay > 7) {
					MoreThanSevenCount++;
				}
				curr = curr->NEXT;
			}
			else {
				curr = curr->NEXT;
			}
		}
		//calculate percentages
		float uk = (UkCount / firstClassCount) * 100;
		float rOE = (ROECount / firstClassCount) * 100;
		float asia = (AsiaCount / firstClassCount) * 100;
		float americas = (AmericasCount / firstClassCount) * 100;
		float australasia = (AustralasiaCount / firstClassCount) * 100;

		//output travel area percentages
		printf("Total Number of passengers in First Class is: %.0f\n", firstClassCount);
		printf("\nPercentages of passengers from:\n");
		printf("UK: %.2f\n", uk);
		printf("Rest of Europe: %.2f\n", rOE);
		printf("Asia: %.2f\n", asia);
		printf("Americas: %.2f\n", americas);
		printf("Australasia: %.2f\n", australasia);

		//calculate percentages
		float oneDay = (DayOneCount / firstClassCount) * 100;
		float lessThan3 = (DayThreeCount / firstClassCount) * 100;
		float lessThan7 = (DaySevenCount / firstClassCount) * 100;
		float moreThan7 = (MoreThanSevenCount / firstClassCount) * 100;
		
		//output avg days percentages
		printf("\nPercentages of passengers - days in Ireland:\n");
		printf("One Day: %.2f\n", oneDay);
		printf("Less than 3: %.2f\n", lessThan3);
		printf("Less than 7: %.2f\n", lessThan7);
		printf("More than 7: %.2f\n\n", moreThan7);
	}

}

//function to print passanger details to file
void printPassengerDetailsToFile(struct node* top, int size)
{
	struct node* curr;
	FILE* file1;
	curr = top;

	//open file
	file1 = fopen("Passenger.txt", "w");

	if (file1 == NULL)
	{
		//cant open file
		printf("The file could not be opened to write\n");
	}
	else {
		//list size - for loading back in passanger information
		fprintf(file1, "%d ", size);
		while (curr != NULL)
		{
			//print information to file
			fprintf(file1, "%d ", curr->passportNumber);
			fprintf(file1, "%s %s ", curr->firstName, curr->lastName);
			fprintf(file1, "%d ", curr->yearBorn);
			fprintf(file1, "%s ", curr->emailAddress);
			fprintf(file1, "%s ", curr->areaTravelledFrom);
			fprintf(file1, "%s ", curr->travelClass);
			fprintf(file1, "%d ", curr->tripsPerYear);
			fprintf(file1, "%d ", curr->durationOfStay);
			fprintf(file1, "\n");

			curr = curr->NEXT;
		}
		//close file
		fclose(file1);
		printf("\outputted details to Passenger.txt\n");
	}
}

//function to create a copy of linked list -- appended from https://stackoverflow.com/questions/13633182/c-program-to-make-a-second-copy-of-a-linked-list
//returns struct node (copied list)
struct node *copyLinkedList(struct node *old)
{
	struct node *newList = NULL, *previous = NULL;

	while (old != NULL)
	{
		//copy old linked list values to new 
		struct node * temp = (struct node *) malloc(sizeof(struct node));
		temp->passportNumber = old->passportNumber;
		strcpy(temp->firstName, old->firstName);
		strcpy(temp->lastName, old->lastName);
		temp->yearBorn = old->yearBorn;
		strcpy(temp->emailAddress, old->emailAddress);
		strcpy(temp->areaTravelledFrom, old->areaTravelledFrom);
		strcpy(temp->travelClass, old->travelClass);
		temp->tripsPerYear = old->tripsPerYear;
		temp->durationOfStay = old->durationOfStay;

		temp->NEXT = NULL;

		//set up new list
		if (newList == NULL)
		{
			newList = temp;
			previous = temp;
		}
		else
		{
			previous->NEXT = temp;
			previous = temp;
		}
		old = old->NEXT;
	}
	return newList;
}

void ukPassengersInOrder(struct node* top)
{
	struct node *i,*j,*curr;
	int temp;
	char names[15];
	char emailAddress[30];
	char tempArAndClass[15];

	int tripsPerYear;
	int durationOfStay;

	//create copy of linked list and return the new list into the value of curr
	curr = copyLinkedList(top);

	//swap elements in copy of linked list in order to maintain element positions in original linked list -- appended using https://www.youtube.com/watch?v=S0anUxnLgA8
	for (i = curr; i->NEXT != NULL; i = i->NEXT) {
		for (j = i->NEXT; j != NULL; j = j->NEXT) {
			//swap elements based on if yearborn is larger than the other
			if (i->yearBorn > j->yearBorn) {

				//swap elements in lists
				temp = i->passportNumber;
				i->passportNumber = j->passportNumber;
				j->passportNumber = temp;

				strcpy(names, i->firstName);
				strcpy(i->firstName, j->firstName);
				strcpy(j->firstName, names);

				strcpy(names, i->lastName);
				strcpy(i->lastName, j->lastName);
				strcpy(j->lastName, names);

				temp = i->yearBorn;
				i->yearBorn = j->yearBorn;
				j->yearBorn = temp;

				strcpy(emailAddress, i->emailAddress);
				strcpy(i->emailAddress, j->emailAddress);
				strcpy(j->emailAddress, emailAddress);

				strcpy(tempArAndClass, i->areaTravelledFrom);
				strcpy(i->areaTravelledFrom, j->areaTravelledFrom);
				strcpy(j->areaTravelledFrom, tempArAndClass);

				strcpy(tempArAndClass, i->travelClass);
				strcpy(i->travelClass, j->travelClass);
				strcpy(j->travelClass, tempArAndClass);

				temp = i->tripsPerYear;
				i->tripsPerYear = j->tripsPerYear;
				j->tripsPerYear = temp;

				temp = i->durationOfStay;
				i->durationOfStay = j->durationOfStay;
				j->durationOfStay = temp;

			}
		}
	}
	printf("\nPassengers in order of Year born from UK\n");
	printf("==========================================\n");

	while (curr)
	{
		//if passengers from uk - display
		if (stricmp(curr->areaTravelledFrom, "UK") == 0) {
			printf("Passport Number: %d\n", curr->passportNumber);
			printf("Name: %s %s\n", curr->firstName, curr->lastName);
			printf("Birth Year: %d\n", curr->yearBorn);
			printf("E-Mail: %s\n", curr->emailAddress);
			printf("Travelled from: %s\n", curr->areaTravelledFrom);
			printf("Travel Class: %s\n", curr->travelClass);
			printf("Trips to Ireland per year: %d\n", curr->tripsPerYear);
			printf("Duration of Stay %d\n\n", curr->durationOfStay);
		}
		curr = curr->NEXT;
	}

}

//function to find the length of the linked list
int length(struct node* top)
{
	struct node* curr;
	int count = 0;

	curr = top;

	//loop through list, increase count with every node
	while (curr->NEXT != NULL)
	{
		count++;
		curr = curr->NEXT;
	}
	count++;

	return count;
}