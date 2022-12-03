#include "Header.h"
#include "Facebook.h"
using namespace std;

void main()
{
	Facebook system;
	initSystem(system); // Hard-coded entities creation
	int choice;
	cout << "Hello and welcome to Facebook!" << endl;

	do
	{
		printMenu();
		cin >> choice;
		getchar();
		executeChoice(choice, system);
		cout << endl;
	} while (choice != EXIT);

	cout << "Thanks and good bye!" << endl;
}