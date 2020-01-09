//Name: Raymond Chu
//Header file to help modularize general helper functions to reduce redundant coding for repetitive tasks

#include "contacts.h"

void clearKeyboard(void);

void pause(void);

int getInt(void);

int getIntInRange(int min, int max);

int yes(void);

int menu(void);

void contactManagerSystem(void);

//Milestone 3 function prototypes

//Generic function to get a ten-digit phone number:
void getTenDigitPhone(char[]);

//Function to return index of a contact:
int findContactIndex(const struct Contact[], int, const char[]);

//Displays contact header:
void displayContactHeader(void);

//Displays contact footer with a counter of how many contacts are saved:
void displayContactFooter(int);

//Displays information about a single contact:
void displayContact(const struct Contact*);

//Function to display all contacts and their information:
void displayContacts(const struct Contact[], int);

//Function to search for a specific contact by providing their cell phone number:
void searchContacts(const struct Contact[], int);

//Function to add a contact:
void addContact(struct Contact[], int);

//Function to update a contact:
void updateContact(struct Contact[], int);

//Function to delete a contact:
void deleteContact(struct Contact[], int);

//Function to sort the contact list numerically and ascending:
void sortContacts(struct Contact[], int);
