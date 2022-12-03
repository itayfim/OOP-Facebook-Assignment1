#include "functions.h"
#include "Facebook.h"
#include "status.h"
#include "page.h"
using namespace std;

void printMenu()
{
	cout << "What would you like to do? " << endl;
	cout << "1. add a friend to the system" << endl;
	cout << "2. add a fan page to the system" << endl;
	cout << "3. add status to a friend / fan page" << endl;
	cout << "4. print all statuses off a friend / fan page" << endl;
	cout << "5. print 10 last statuses of each friend of a specific user" << endl;
	cout << "6. connect 2 friends" << endl;
	cout << "7. cancel connection of 2 friends" << endl;
	cout << "8. add a friend to a fan page" << endl;
	cout << "9. remove a friend from a fan page" << endl;
	cout << "10. print all entities in the system" << endl;
	cout << "11. print all frineds of a specific user / all the followers of a specific fan page" << endl;
	cout << "12. exit" << endl;
}

void executeChoice(int choice, Facebook& system)
{
	switch (choice)
	{
	case 1:
		addFriendToTheSystem(system);
		break;
	case 2:
		addFanPageToTheSystem(system);
		break;
	case 3:
		addStatus(system);
		break;
	case 4:
		printStatus(system);
		break;
	case 5:
		print10LastStatuses(system);
		break;
	case 6:
		connectTwoFriends(system);
		break;
	case 7:
		disconnectTwoFriends(system);
		break;
	case 8:
		addFanToFanPage(system);
		break;
	case 9:
		deleteFanFromFanPage(system);
		break;
	case 10:
		printEntities(system);
		break;
	case 11:
		printFollowers(system);
		break;
	case 12:
		break;
	default:
		cout << "Wrong input, please enter a valid number between 1-12." << endl;
		break;
	}
}

void initSystem(Facebook& system)
{
	// hard-coded entities:
	User* u1 = new User("Shani", { 3,1,2001 });
	User* u2 = new User("Itay", { 4,1,1994 });
	User* u3 = new User("Liav", { 3,7,1999 });
	system.addFriend(*u1); system.addFriend(*u2); system.addFriend(*u3);
	Page* p1 = new Page("MTA");
	Page* p2 = new Page("Tel Aviv");
	Page* p3 = new Page("Even Yehuda");
	system.addPage(*p1); system.addPage(*p2); system.addPage(*p3);
	Status* s1 = new Status("Hi, my name is Shani and I live in Even Yehuda");
	Status* s2 = new Status("I like to eat salads");
	u1->addStatusForUser(*s1); u1->addStatusForUser(*s2);
	Status* s3 = new Status("Hi, my name is Itay and I live in Tel Aviv");
	Status* s4 = new Status("I like to eat Happy-Hippo's");
	u2->addStatusForUser(*s3); u2->addStatusForUser(*s4);
	Status* s5 = new Status("Hi, my name is Liav and I live in Oranit");
	Status* s6 = new Status("I like to eat a lot of scarambled eggs");
	u3->addStatusForUser(*s5); u3->addStatusForUser(*s6);
	Status* s7 = new Status("Important notice: there will be no classes in light of the beginning of the year happening");
	Status* s8 = new Status("Reminder: Please fill out the teaching survey");
	p1->addStatusForPage(*s7); p1->addStatusForPage(*s8);
	Status* s9 = new Status("Ayalon routes will be closed in light of the White Night events");
	Status* s10 = new Status("The sale has opened for discounted tours in the Carmel Market for the residents of the city");
	p2->addStatusForPage(*s9); p2->addStatusForPage(*s10);
	Status* s11 = new Status("A cat named Mitzi has been lost, anyone who comes across him - please contact Liora from the council");
	Status* s12 = new Status("Agricultural land in Evan Yehuda, please respond if you are interested");
	p3->addStatusForPage(*s11); p3->addStatusForPage(*s12);
	u1->addFriend(*u2); u1->addFriend(*u3); u2->addFriend(*u3);
	p1->addFollower(*u1); p2->addFollower(*u2); p3->addFollower(*u1);
}

void printFollowers(Facebook& system)
{
	int input;
	cout << "Select one of the followings:" << endl << "1. print all friends of a specific friend" << endl << "2. print all followers of a fan page" << endl;
	cin >> input;
	getchar();
	if (input == 1)
		printFriendFollowers(system);
	else if (input == 2)
		printPageFollowers(system);
}

void printFriendFollowers(Facebook& system)
{
	int index;
	cout << "Please enter the user's name whose friends you would like to see: " << endl;
	char name[MAX_NAME_LEN];
	cin.getline(name, MAX_NAME_LEN);
	index = searchUserByName(name, system);
	if (index == INVALID) // The user does not exist
		return;
	system.getUser(index)->printFriends();
}

void printPageFollowers(Facebook& system)
{
	int index;
	cout << "Please enter the fan page's name whose followers you would like to see: " << endl;
	char name[MAX_NAME_LEN];
	cin.getline(name, MAX_NAME_LEN);
	index = searchPageByName(name, system);
	if (index == INVALID) // The page does not exist
		return;
	system.getPage(index)->printFollowers();
}

void addFanToFanPage(Facebook& system)
{
	int indexUser, indexPage;
	if (system.getNumOfUsers() < 1 || system.getNumOfPages() < 1) // Cannot connect user to fan page if there are no users or fan pages 
	{
		cout << "There are no users/pages in the system, cannot execute this order." << endl;
		return;
	}
	indexUser = takeInput(system, 1, true); // The user selects a fan to add to the fan page
	indexPage = takePageInput(system, true); // The user chooses which fan page the fan will be added to
	system.getPage(indexPage)->addFollower(*(system.getUser(indexUser))); 
}

void deleteFanFromFanPage(Facebook& system)
{
	int indexUser, indexPage;
	if (system.getNumOfUsers() < 1 || system.getNumOfPages() < 1) // Cannot disconnect user from fan page if there are no users or fan pages 
	{
		cout << "There are no users/pages in the system, cannot execute this order." << endl;
		return;
	}
	indexUser = takeInput(system, 1, false); // The user selects a fan to delete from the fan page
	indexPage = takePageInput(system, false); //The user chooses which fan page the fan will be deleted from
	system.getPage(indexPage)->deleteFollower(*(system.getUser(indexUser)));
}

int takePageInput(Facebook& system, bool add)
{
	int res;
	char name[MAX_NAME_LEN];
	bool goodName;
	do
	{
		goodName = true;
		cout << "Please enter the fan pages's name that the fan will be " << (add ? "added to" : "removed from") << endl;
		cin.getline(name, MAX_NAME_LEN);
		res = searchPageByName(name, system);
		if (res == INVALID) // The page does not exist
			goodName = false;
	} while (!goodName);
	return res; // The index in the array of the selected fan page
}

void disconnectTwoFriends(Facebook& system)
{
	int index1, index2;
	if (system.getNumOfUsers() < 2) // Cannot disconnect 1 or 0 users 
	{
		cout << "There is only " << system.getNumOfUsers() << " users in the system, cannot execute this order." << endl;
		return;
	}
	index1 = takeInput(system, 1, false); // The user selects the first friend to disconnect
	index2 = takeInput(system, 2, false); // The user selects the second friend to disconnect
	system.getUser(index1)->deleteFriend(*(system.getUser(index2))); 
}

void connectTwoFriends(Facebook& system)
{
	int index1, index2;
	if (system.getNumOfUsers() < 2) // Cannot connect 1 or 0 users 
	{
		cout << "There is only " << system.getNumOfUsers() << " users in the system, cannot execute this order." << endl;
		return;
	}
	index1 = takeInput(system, 1, true); // The user selects the first friend to connect
	index2 = takeInput(system, 2, true); // The user selects the second friend to connect
	system.getUser(index1)->addFriend(*(system.getUser(index2)));
}

int takeInput(Facebook& system, int num, bool connect)
{
	int res;
	char name[MAX_NAME_LEN];
	bool goodName;
	do
	{
		goodName = true;
		cout << "Please enter the " << (num == 1 ? "1st" : "2nd") << " member's name that you want to " << (connect ? "connect" : "disconnect") << endl;
		cin.getline(name, MAX_NAME_LEN);
		res = searchUserByName(name, system);
		if (res == INVALID) // in case of choosing a friends that doesnt exist in the system
			goodName = false;
	} while (!goodName);
	return res; // The index in the array of the selected User
}

int searchUserByName(char* name, Facebook& system)
{
	int n = system.getNumOfUsers();
	for (int i = 0; i < n; i++)
	{
		if (strcmp(system.getUser(i)->getName(), name) == 0)
			return i; // The index of the user in the users array
	}
	cout << "Couldn't find '" << name << "' in the system, please try again." << endl;
	return INVALID; // The user does not exist in the array
}

int searchPageByName(char* name, Facebook& system)
{
	int n = system.getNumOfPages();
	for (int i = 0; i < n; i++)
	{
		if (strcmp(system.getPage(i)->getName(), name) == 0)
			return i; // The index of the page in the pages array
	}
	cout << "Couldn't find '" << name << "' in the system, please try again." << endl;
	return INVALID; // The page does not exist in the array
}

void printEntities(Facebook& system)
{
	cout << "Printing all the entities in the system: " << endl;
	cout << "Printing all users: " << endl;
	system.printUsers();
	cout << "Printing all pages: " << endl;
	system.printPages();
}

void print10LastStatuses(Facebook& system)
{
	int index;
	cout << "Please enter the user's name you would like to see the 10 most recent statuses of each of its friends: " << endl;
	char name[MAX_NAME_LEN];
	cin.getline(name, MAX_NAME_LEN);
	index = searchUserByName(name, system);
	if (index == INVALID) // The user does not exist in the system
		return;
	system.getUser(index)->printFriendsStatuses();
}

void printStatus(Facebook& system)
{
	int input;
	cout << "Select one of the followings:" << endl << "1. print statuses of a friend" << endl << "2. print statuses of a fan page" << endl;
	cin >> input;
	getchar();
	if (input == 1)
		printFriendStatuses(system);
	else if (input == 2)
		printFanPageStatuses(system);
}

void printFriendStatuses(Facebook& system)
{
	int index;
	cout << "Please enter the user's name whose statuses you would like to see: " << endl;
	char name[MAX_NAME_LEN];
	cin.getline(name, MAX_NAME_LEN);
	index = searchUserByName(name, system);
	if (index == INVALID) // The user does not exist in the system
		return;
	system.getUser(index)->printStatusesOfUser();
}

void printFanPageStatuses(Facebook& system)
{
	int index;
	cout << "Please enter the fan page's name whose statuses you would like to see: " << endl;
	char name[MAX_NAME_LEN];
	cin.getline(name, MAX_NAME_LEN);
	index = searchPageByName(name, system);
	if (index == INVALID) // The fan page does not exist in the system
		return;
	system.getPage(index)->printStatusesOfPage();
}

void addStatus(Facebook& system)
{
	int input;
	cout << "Select one of the followings:" << endl << "1. add status to a friend" << endl << "2. add status to a fan page" << endl;
	cin >> input;
	getchar(); // clean buffer
	if (input == 1)
		addStatusToFriend(system);
	else if (input == 2)
		addStatusToFanPage(system);
}

void addStatusToFanPage(Facebook& system)
{
	char newTextStatus[MAX_STATUS_LEN];
	int index;
	cout << "Please enter the fan page's name to which you would like to add a status: " << endl;
	char name[MAX_NAME_LEN];
	cin.getline(name, MAX_NAME_LEN);
	index = searchPageByName(name, system);
	if (index == INVALID) // The fan page does not exist in the system
		return;
	cout << "Write your status here: " << endl;
	cin.getline(newTextStatus, MAX_STATUS_LEN);
	Status* newStatus = new Status(newTextStatus); // Create a new status
	system.getPage(index)->addStatusForPage(*newStatus);
}

void addStatusToFriend(Facebook& system)
{
	char newTextStatus[MAX_STATUS_LEN];
	int index;
	cout << "Please enter the user's name to which you would like to add a status: " << endl;
	char name[MAX_NAME_LEN];
	cin.getline(name, MAX_NAME_LEN);
	index = searchUserByName(name, system);
	if (index == INVALID) // The user does not exist in the system
		return;
	cout << "Write your status here: " << endl;
	cin.getline(newTextStatus, MAX_STATUS_LEN);
	Status* newStatus = new Status(newTextStatus); // Create a new status
	system.getUser(index)->addStatusForUser(*newStatus);
}

void addFriendToTheSystem(Facebook& system)
{
	int index;
	bool goodInput;
	char str[MAX_NAME_LEN], birthday[MAX_NAME_LEN];
	char seps[] = "\/."; // Separators of the date input
	Date date_of_birth;
	do
	{
		index = VALID; 
		cout << "Please enter the friend's name: " << endl;
		cin.getline(str, MAX_NAME_LEN);
		for (int i = 0; i < system.getNumOfUsers() && index != INVALID; i++) // Check if there is a user with the same name
		{
			if (strcmp(system.getUser(i)->getName(), str) == 0)
				index = INVALID;
		}
		if (index == INVALID)
			cout << str << " is allready exist in the system, please choose another name." << endl;
	} while (index == INVALID);
	do {
		goodInput = true;
		cout << "Please enter the friend's birthday (by the format of dd.mm.yyyy): " << endl;
		cin.getline(birthday, 12);
		date_of_birth.day = atoi(strtok(birthday, seps));
		date_of_birth.month = atoi(strtok(NULL, seps));
		date_of_birth.year = atoi(strtok(NULL, seps));
		if (date_of_birth.day > 31 || date_of_birth.day < 1 || date_of_birth.month > 12 || date_of_birth.month < 1) //Check if the date input is correct
		{
			cout << "Wrong input, try again." << endl;
			goodInput = false;
		}
	} while (!goodInput);
	User* newUser = new User(str, date_of_birth); // Create a new user
	system.addFriend(*newUser); 
}

void addFanPageToTheSystem(Facebook& system)
{
	int index;
	char str[MAX_NAME_LEN];
	do
	{
		index = VALID;
		cout << "Please enter the page's name: " << endl;
		cin.getline(str, MAX_NAME_LEN);
		for (int i = 0; i < system.getNumOfPages() && index != INVALID; i++) // Check if there is a fan page with the same name
		{
			if (strcmp(system.getPage(i)->getName(), str) == 0)
				index = INVALID;
		}
		if (index == INVALID)
			cout << str << " is allready exist in the system, please choose another name." << endl;
	} while (index == INVALID);
	Page* newPage = new Page(str); // Create a new fan page
	system.addPage(*newPage);
}
