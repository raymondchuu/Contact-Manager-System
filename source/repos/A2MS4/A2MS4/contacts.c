//Name: Raymond Chu
//Contact Manager System Page for users to enter the contacts

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "contacts.h"
#include "contactHelpers.h"

void getName(struct Name* name) {
	int option;

	//Contact Name
	printf("Please enter the contact's first name: ");
	scanf(" %31[^\n]", name->firstName);

	printf("Do you want to enter a middle initial(s)? (y or n): ");
	option = yes();

	if (option == 1) {
		printf("Please enter the contact's middle initial(s): ");
		scanf(" %6[^\n]", name->middleInitial);
	}

	else if (option == 0) {
		name->middleInitial[0] = '\0';
	}


	printf("Please enter the contact's last name: ");
	scanf(" %36[^\n]", name->lastName); // The system will accept a space, and then scan through 36 characters until there is a break or when the user click's their enter key
	clearKeyboard();

	return; // This function will request user to input their information regarding their name and then return to main function
}


void getAddress(struct Address* address) {
	int SN = 0, AN = 0, option;

	//Contact Address
	printf("Please enter the contact's street number: ");
	SN = getInt();

	while (SN < 0) {
		printf("*** INVALID STREET NUMBER *** <must be a positive number>: ");
		SN = getInt();
	}

	address->streetNumber = SN;

	printf("Please enter the contact's street name: ");
	scanf(" %40[^\n]", address->street);
	clearKeyboard();

	printf("Do you want to enter an apartment number? (y or n): ");
	option = yes();

	if (option == 1) {
		printf("Please enter the contact's apartment number: ");
		AN = getInt();
	}

	else if (option == 0) {
		address->apartmentNumber = ' ';
	}

	while (AN < 0) {
		printf("*** INVALID APARTMENT NUMBER *** <must be a positive number>: ");
		AN = getInt();
	}

	address->apartmentNumber = AN;

	printf("Please enter the contact's postal code: ");
	scanf(" %7[^\n]", address->postalCode);
	clearKeyboard();

	printf("Please enter the contact's city: ");
	scanf(" %40[^\n]", address->city);


	return; // This function will request the user to input information regarding their address and then return to main function
}

void getNumbers(struct Numbers* numbers) {
	char option;

	//Contact Numbers
	printf("Please enter the contact's cell phone number: ");
	getTenDigitPhone(numbers->cell);

	printf("Do you want to enter a home phone number? (y or n): ");
	option = yes();

	if (option == 1) {
		printf("Please enter the contact's home phone number: ");
		getTenDigitPhone(numbers->home);
	}


	printf("Do you want to enter a business phone number? (y or n): ");
	option = yes();

	if (option == 1) {
		printf("Please enter the contact's business phone number: ");
		getTenDigitPhone(numbers->business);
	}

	return; // This function will request user to input information about their phone numbers and then return to main function
}

void getContact(struct Contact* contacts) {

	getName(&contacts->name);
	getAddress(&contacts->address);
	getNumbers(&contacts->numbers);

}