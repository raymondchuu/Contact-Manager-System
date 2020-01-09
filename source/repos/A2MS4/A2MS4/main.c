//Name: Raymond Chu
//Contacts Manager System Main Page

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "contacts.h"
#include "contactHelpers.h"

void printSectionHeader(const char* testName);

int main(void)
{
	printSectionHeader("Final A#2-Milestone #4 (Sort)");

	contactManagerSystem();

	return 0;
}

// Display specified test section header
void printSectionHeader(const char* testName)
{
	printf("\n");
	printf("------------------------------------------\n");
	printf("Testing: %s\n", testName);
	printf("------------------------------------------\n");
}
