#include "user.h"
#include "status.h"
using namespace std;

User::User(const char* name, Date date_of_birth)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->date_of_birth = date_of_birth;
	this->friends = new User*;
	this->my_statuses = new Status*;
	this->fan_pages = new Page*;
}

User::~User()
{
	for (int i = 0; i < num_of_statuses; i++)
		delete my_statuses[i];
	delete[]name;
	delete[]friends;
	delete[]my_statuses;
	delete[]fan_pages;
}

void User::addFriend(User& new_friend)
{
	bool founded = false;
	for (int i = num_of_friends - 1 && !founded; i >= 0; i--) // Check if the new friend is already following the friend
	{
		if (friends[i] == &new_friend)
			founded = true;
	}
	if (!founded) // The new friend isn't in the list of friends of the current friend
	{
		if (num_of_friends == max_friends) // Check if the array needs to be increased
		{
			max_friends *= 2;
			User** newArr = new User * [max_friends];
			for (int i = 0; i < num_of_friends; i++)
				newArr[i] = friends[i];
			delete[]friends;
			friends = newArr;
		}
		friends[num_of_friends] = &new_friend; // Adding the new friend to the array of friends
		num_of_friends++;
		new_friend.addFriend(*this); // Mutual action, the new friend will add the current friend to his list of friends
	}
}

void User::deleteFriend(User& old_friend)
{
	int index = INVALID;
	for (int i = num_of_friends - 1; i >= 0 && index == INVALID; i--) // Check if the old friend is already deleted from the list of friends of the current friend
	{
		if (friends[i] == &old_friend)
			index = i;
	}
	if (index != INVALID) // The old friend wasn't deleted
	{
		for (int i = index; i < num_of_friends - 1; i++)
			friends[i] = friends[i + 1];
		num_of_friends--;
		old_friend.deleteFriend(*this); // Mutual action, the old friend will delete the current friend from his list of friends
	}
}

void User::addStatusForUser(Status& new_status)
{
	if (num_of_statuses == max_statuses)
	{
		max_statuses *= 2;
		Status** newArr = new Status * [max_statuses];
		for (int i = 0; i < num_of_statuses; i++)
			newArr[i] = my_statuses[i];
		delete[]my_statuses;
		my_statuses = newArr;
	}
	my_statuses[num_of_statuses] = &new_status;
	num_of_statuses++;
}

void User::addPage(Page& new_page)
{
	bool founded = false;
	for (int i = num_of_pages - 1; i >= 0 && !founded; i--) // Check if the new page is already in the friend's list of pages
	{
		if (fan_pages[i] == &new_page)
			founded = true;
	}
	if (!founded) // The new page isn't in the friend's list of pages
	{
		if (num_of_pages == max_pages)
		{
			max_pages *= 2;
			Page** newArr = new Page * [max_pages];
			for (int i = 0; i < num_of_pages; i++)
				newArr[i] = fan_pages[i];
			delete[]fan_pages;
			fan_pages = newArr;
		}
		fan_pages[num_of_pages] = &new_page;
		num_of_pages++;
		new_page.addFollower(*this); // Mutual action,the new page will add the current friend to his list of followers
	}
}

void User::deletePage(Page& old_page)
{
	int index = INVALID;
	for (int i = num_of_pages - 1; i >= 0; i--) // Check if the old page is already deleted from the list of pages of the current friend
	{
		if (fan_pages[i] == &old_page)
			index = i;
	}
	if(index != INVALID) // The old page wasn't deleted
	{
		for (int i = index; i < num_of_pages - 1; i++)
			fan_pages[i] = fan_pages[i + 1];
		num_of_pages--;
		old_page.deleteFollower(*this); // Mutual action, the old page will delete the current friend from his list of followers
	}
}

void User::printFriends() const
{
	cout << "" << name << "'s friends list:" << endl;
	for (int i = 0; i < num_of_friends; i++)
	{
		cout << "" << i + 1 << ". " << friends[i]->name << endl;
	}
}

void User::printStatusesOfUser() const
{
	cout << "" << name << "'s statuses:" << endl;
	for (int i = 0; i < num_of_statuses; i++)
	{
		cout << "" << i + 1 << ". ";
		my_statuses[i]->printStatus();
	}
}

void User::printFriendsStatuses() const
{
	cout << "" << name << "'s 10 last friends statuses:" << endl;
	for (int i = 0; i < num_of_friends; i++)
	{
		cout << friends[i]->getName() << "'s statuses: " << endl;
		for (int j = friends[i]->num_of_statuses - 1; j >= 0 && j > (friends[i]->num_of_statuses - 1) - 10; j--) // Prints the last 10 statuses or less if there are less than 10
			friends[i]->my_statuses[j]->printStatus();
	}
}

void User::printFanPages() const
{
	cout << "" << name << "'s fan pages:" << endl;
	for (int i = 0; i < num_of_pages; i++)
	{
		cout << "" << i + 1 << ". " << fan_pages[i]->getName() << endl;
	}
}