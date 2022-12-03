#include "page.h"
#include "status.h"
using namespace std;

const char* Page::getName() const
{
	return this->name;
}

Page::Page(const char* name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	followers = new User*;
	page_statuses = new Status*;
}

Page::~Page()
{
	delete[] name;
	delete[] followers;
	for (int i = 0; i < num_of_statuses; i++)
		delete page_statuses[i];
	delete[] page_statuses;
}

void Page::addFollower(User& new_follower)
{
	bool founded = false;
	for (int i = num_of_followers - 1; i >= 0 && !founded; i--) //Check if the new follower is already following the fan page
	{
		if (followers[i] == &new_follower)
			founded = true; 
	}
	if (!founded) // The new follower isn't in the list of followers
	{
		if (num_of_followers == max_followers) // Check if the array needs to be increased
		{
			max_followers *= 2;
			User** newArr = new User * [max_followers];
			for (int i = 0; i < num_of_followers; i++)
				newArr[i] = followers[i];

			delete[] followers;
			followers = newArr;
		}
		followers[num_of_followers] = &new_follower; // Adding the new follower to the array
		num_of_followers++;
		new_follower.addPage(*this); // Mutual action, the new follower will add the fan page to his list of pages
	}
}

void Page::deleteFollower(User& old_follower)
{
	int index = INVALID;
	for (int i = num_of_followers - 1; i >= 0 && index == INVALID; i--) //Check if the new follower is in the list of followers
	{
		if (strcmp(followers[i]->getName(), old_follower.getName()) == 0)
			index = i;
	}
	if (index != INVALID) // The old follower is in the list of followers and need to be deleted
	{
		for (int j = index; j < num_of_followers - 1; j++) 
			followers[j] = followers[j + 1];
		num_of_followers--;
		old_follower.deletePage(*this); //Mutual action, the old follower delete the fan page from his list of pages
	}
}

void Page::addStatusForPage(Status& new_status)
{
	if (num_of_statuses == max_statuses) // Check if the array needs to be increased
	{
		max_statuses *= 2;
		Status** newArr = new Status * [max_statuses];
		for (int i = 0; i < num_of_statuses; i++)
		{
			newArr[i] = page_statuses[i];
		}
		delete[] page_statuses;
		page_statuses = newArr;
	}
	page_statuses[num_of_statuses] = &new_status; // Adding the new status to the array
	num_of_statuses++;
}

void Page::printFollowers() const
{
	for (int i = 0; i < num_of_followers; i++)
	{
		cout << "" << i + 1 << ". " << followers[i]->getName() << endl;
	}
}

void Page::printStatusesOfPage() const
{
	cout << "" << name << "'s statuses:" << endl;
	for (int i = 0; i < num_of_statuses; i++)
	{
		cout << i + 1 << ".";
		page_statuses[i]->printStatus();
	}
}