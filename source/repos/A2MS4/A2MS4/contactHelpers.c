//Name: Raymond Chu
//Contact Manager system Helper Functions 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "contactHelpers.h"
#include<stdlib.h>
#define MAXCONTACTS 5


void clearKeyboard(void) { // This function will clear the buffer

	while (getchar() != '\n');
}

void pause(void) { // This function will print out "Press enter to continue"
	printf("(Press Enter to Continue)");
	clearKeyboard();
}

int getInt(void) { // This function will test if an integer is being inputted

	int value, rc = 0;
	char NL;

	scanf(" %d%c", &value, &NL);

	do {
		if (NL != '\n') {
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
			scanf(" %d%c", &value, &NL);
		} // If a non - integer is inputted, then this error message will appear and ask the user to enter an integer

		else if (NL == '\n')
			rc = 1; // However, if an integer was inputted, then rc flag will be set to 1 and the user will escape out of this do-while loop

	} while (rc == 0);

	return value; // The integer value entered by the user will be returned to the main function
}

int getIntInRange(int min, int max) { // This function will test if a value was entered within a specific range

	int value, rc = 0, check;

	check = scanf("%d", &value); // If scanf returns a value of 1, that would indicate that scanf filled the first address successfully and that an integer was entered

	do {

		if (check != 1) { // First we check if the inputted value is an integer. If check is a value that's not 1, this would mean that scanf did not fill the first address successfully and a non-integer value was inputted. An error message would appear and ask the user to enter an integer
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
			check = scanf(" %d", &value);

		}

		else if (value < min || value > max) { // Another check is then done to see if the value inputted is within the range a specific min and max
			clearKeyboard();
			printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max); // If it is out of the range, then this error message will appear 
			check = scanf(" %d", &value);
		}

		else
			rc = 1; // Once the user finally inputs an integer within the range, rc flag is set to 1 and the user will escape out of this do-while loop

	} while (rc == 0);

	return value;
}

int yes(void) { // This function checks if the appropriate Y, y, N, n was answered 
	char ans, NL;
	int response = -1;

	scanf(" %c%c", &ans, &NL);

	while (!(NL == '\n' && (ans == 'Y' || ans == 'y' || ans == 'N' || ans == 'n'))) { // If any value that's not Y, y, N, n was entered, then an error message will appear
		clearKeyboard();
		printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		scanf("%c%c", &ans, &NL);

	}

	if (ans == 'N' || ans == 'n') // If the user enters N or n, then this function will return a value of 0 stored in the variable response
		response = 0;
	else if (ans == 'Y' || ans == 'y') // If the user enters Y or y, then this function will return a value of 0 stored in the variable response
		response = 1;

	return response;
}

int menu(void) {

	printf("Contact Management System\n"); // Menu of the contact management system
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n");
	printf("\n");
	printf("Select an option:> ");

	return getIntInRange(0, 6); // returns to getIntInRange function to make sure that user is entering a number within the menu selection

}

void contactManagerSystem(void) {
	int option, ans;

	struct Contact contacts[MAXCONTACTS] = { { { "Rick", {'\0'}, "Grimes" },
											   { 11, "Trailer Park", 0, "A7A 2J2", "King City" },
											   { "4161112222", "4162223333", "4163334444" } },
											{
												{ "Maggie", "R.", "Greene" },
												{ 55, "Hightop House", 0, "A9A 3K3", "Bolton"},
												{ "9051112222", "9052223333", "9053334444" } },
											{
												{ "Morgan", "A.", "Jones" },
												{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
												{ "7051112222", "7052223333", "7053334444" } },
											{
												{ "Sasha", {'\0'}, "Williams" },
												{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
												{ "9052223333", "9052223333", "9054445555" } },
	};

	do {
		option = menu();

		switch (option) { // Switch function is used so user can navigate around the menu

		case 0:
			printf("\n");
			printf("Exit the program? (Y)es/(N)o: ");
			ans = yes(); // User will have to press 0 and then will call on yes() function to verify if user actually wants to quit

			if (ans == 1) {
				printf("\n");
				printf("Contact Management System: terminated\n");
				return;
			}
			else if (ans == 0) {
				printf("\n");
			}
			break;

		case 1:
			displayContacts(contacts, MAXCONTACTS);

			break;

		case 2:
			addContact(contacts, MAXCONTACTS);


			break;

		case 3:
			updateContact(contacts, MAXCONTACTS);

			break;

		case 4:
			deleteContact(contacts, MAXCONTACTS);

			break;

		case 5:
			searchContacts(contacts, MAXCONTACTS);

			break;

		case 6:
			sortContacts(contacts, MAXCONTACTS);

			break;

		default:
			printf("*** OUT OF RANGE *** <Enter a number between 0 and 6> \n");
			printf("\n");
			break;
		}
	} while (option >= 0 || option <= 6);

	return;
}


//Milestone 4--------------------

//This function will request the user to enter a 10 digit phone number and will only accept a number with 10 digits
void getTenDigitPhone(char phoneNum[]) {
	int needInput = 1;

	while (needInput == 1) {
		scanf(" %10[0-9]", phoneNum);
		clearKeyboard();


		if (strlen(phoneNum) == 10)
			needInput = 0;
		else
			printf("Enter a 10-digit phone number: ");

	}

}

//This function will check if the number entered matches with any number in the contacts structure and will return the index if it matches and returns -1 if it does not match
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[]) {
	int i;
	int found = 0;
	int index = -1;

	for (i = 0; i < size && found == 0; i++) {
		if (strcmp(contacts[i].numbers.cell, cellNum) == 0) {
			found = 1;
			index = i;
		}
			
	}

	return index;
}

//This function will display this contacts listing header
void displayContactHeader(void) {
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|                              Contacts Listing                               |\n");
	printf("+-----------------------------------------------------------------------------+\n");

}

//This function will display the footer and also the number of total contacts in the management system
void displayContactFooter(int count) {
	printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n\n", count);

}

//This function will display the information of a contact when called upon
void displayContact(const struct Contact* contact) {

	if (contact->name.middleInitial[0] == '\0')
		printf(" %s %s\n", contact->name.firstName, contact->name.lastName);
	else
		printf(" %s %s %s\n", contact->name.firstName, contact->name.middleInitial, contact->name.lastName);

	printf("    C: %-10s   H: %-10s   B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);

	if (contact->address.apartmentNumber > 0)
		printf("       %d %s, Apt# %d, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.apartmentNumber, contact->address.city, contact->address.postalCode);
	else
		printf("       %d %s, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.city, contact->address.postalCode);

}

//This function will display the header and footer and all the contacts in the contacts structure 
void displayContacts(const struct Contact contacts[], int size) {
	int i, count = 0;
	printf("\n");
	displayContactHeader();

	for (i = 0; i < size; i++) {
		if (contacts[i].numbers.cell[0] > 0) {
			displayContact(&contacts[i]);
			count++;
		}

	}

	displayContactFooter(count);
	pause();
	getchar();
	printf("\n");
}

//This function will call on the findContactIndex to check if the contact is in the structure
//If the number is found, then the function will display the contact information
void searchContacts(const struct Contact contacts[], int size) {
	char phoneNum[11];
	int result;

	printf("\n");
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(phoneNum);

	result = findContactIndex(contacts, size, phoneNum);

	if (result < 0) {
		printf("*** Contact NOT FOUND ***\n");
		printf("\n");
		pause();
		printf("\n");

	}
	else if (result >= 0) {
		printf("\n");
		displayContact(&contacts[result]);
		printf("\n");
		pause();
		printf("\n");
	}
}

//This funciton will add a contact if the contact list is not full
void addContact(struct Contact contacts[], int size) {
	int i, index = -1;

	printf("\n");

	for (i = 0; i < size; i++) {

		if (contacts[i].numbers.cell[0] == 0) {
			index = i;
		}
	}

	if (index < 0) {
		printf("*** ERROR: The contact list is full! ***\n");
		printf("\n");
		pause();
		getchar();
		printf("\n");
	}

	else if (index >= 0) {
		getContact(&contacts[index]);
		printf("--- New contact added! ---\n");
		printf("\n");
		pause();
		printf("\n");
	}

}

//This function will give the user the option to update any of the contacts
//If the user wants to update a contact, then a blank structure will be used so that the user can enter the new information
void updateContact(struct Contact contacts[], int size) {
	char cellNum[11];
	int result, response;
	struct Name blankName = { {'\0'} };
	struct Address blankAddress = { 0, {'\0'}, 0, {'\0'}, {'\0'} };
	struct Numbers blankNumbers = { {'\0'} };

	printf("\n");
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cellNum);
	result = findContactIndex(contacts, size, cellNum);

	if (result < 0) {
		printf("*** Contact NOT FOUND ***\n");
		printf("\n");
		pause();
		printf("\n");
	}

	else if (result >= 0) {
		printf("\n");
		printf("Contact found:\n");

		displayContact(&contacts[result]);
		printf("\n");

		printf("Do you want to update the name? (y or n): ");
		response = yes();

		if (response == 1) {
			contacts[result].name = blankName;
			getName(&contacts[result].name);
		}

		printf("Do you want to update the address? (y or n): ");
		response = yes();

		if (response == 1) {
			contacts[result].address = blankAddress;
			getAddress(&contacts[result].address);
		}

		printf("Do you want to update the numbers? (y or n): ");
		response = yes();

		if (response == 1) {
			contacts[result].numbers = blankNumbers;
			getNumbers(&contacts[result].numbers);
		}

		printf("--- Contact Updated! ---\n");
		printf("\n");
		pause();
		printf("\n");
	}
}

//This function will set a given index of the set the contact information to \0 if the user wants to delete a contact
void deleteContact(struct Contact contacts[], int size) {
	char cellNum[11];
	int result, response;
	struct Contact blank = { { {'\0'} }, {0, {'\0'}, 0, {'\0'}, {'\0'} }, { {'\0'} } };

	printf("\n");
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(cellNum);
	printf("\n");

	result = findContactIndex(contacts, size, cellNum);

	if (result < 0) {
		printf("*** Contact NOT FOUND ***\n\n");
		printf("\n");
		pause();
		printf("\n");
	}

	else if (result >= 0) {
		printf("Contact found:\n");

		displayContact(&contacts[result]);
		printf("\n");
		printf("CONFIRM: Delete this contact? (y or n): ");
		response = yes();

		if (response == 1) {
			contacts[result] = blank;
			printf("--- Contact deleted! ---\n");
			printf("\n");
			pause();
			printf("\n");
		}

		else if (response == 0) {
			printf("\n");
			pause();
			printf("\n");
		}
	}
}

//This function will sort the contacts ascending numerically by cell phone number 
void sortContacts(struct Contact contacts[], int size) {
	int i, j;
	struct Contact temp;

	for (i = 0; i < size - 1; i++) {
		for (j = i + 1; j < size; j++) {
			if (strlen(contacts[i].numbers.cell) != 0 && strlen(contacts[j].numbers.cell) != 0) {
				if (strcmp(contacts[i].numbers.cell, contacts[j].numbers.cell) > 0) {
					temp = contacts[i];
					contacts[i] = contacts[j];
					contacts[j] = temp;
				}
			}
		}
	}

	printf("\n");
	printf("--- Contacts sorted! ---\n");
	printf("\n");
	pause();
	getchar();
	printf("\n");
}

