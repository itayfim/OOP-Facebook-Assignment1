#include "Facebook.h"
#include "page.h"
#include "user.h"
using namespace std;


Facebook::Facebook()
{
	this->pages = new Page*;
	this->users = new User*;
}

Facebook::~Facebook()
{
	for (int i = 0; i < num_of_pages; i++)
		delete pages[i];
	for (int i = 0; i < num_of_users; i++)
		delete users[i];
	delete[]users;
	delete[]pages;
}

void Facebook::addFriend(User& user)
{
	if (num_of_users == max_users)
	{
		max_users *= 2;
		User** newArr = new User * [max_users];
		for (int i = 0; i < num_of_users; i++)
			newArr[i] = users[i];
		delete[]users;
		users = newArr;
	}
	users[num_of_users] = &user; // Adding a new user to the system
	num_of_users++;
}

void Facebook::addPage(Page& page)
{
	if (num_of_pages == max_pages) // check if the array needs to be increased
	{
		max_pages *= 2;
		Page** newArr = new Page * [max_pages];
		for (int i = 0; i < num_of_pages; i++)
			newArr[i] = pages[i];
		delete[]pages;
		pages = newArr;
	}
	pages[num_of_pages] = &page; // Adding a new fan page to the system
	num_of_pages++;
}

void Facebook::printUsers() const
{
	for (int i = 0; i < num_of_users; i++)
	{
		cout << i + 1 << ". " << users[i]->getName() << endl;
		cout << users[i]->getName() << "'s statuses: " << endl;
		for (int j = 0; j < users[i]->getNumOfStatuses(); j++) 
			users[i]->getStatus(j)->printStatus(); // Print the user's statuses
	}
}

void Facebook::printPages() const
{
	for (int i = 0; i < num_of_pages; i++)
	{
		cout << i + 1 << ". " << pages[i]->getName() << endl;
		cout << pages[i]->getName() << "'s statuses: " << endl;
		for (int j = 0; j < pages[i]->getNumOfStatuses(); j++) // Print the fan page's statuses
			pages[i]->getStatus(j)->printStatus();
	}

}

