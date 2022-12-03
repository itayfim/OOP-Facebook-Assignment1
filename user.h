#ifndef __USER_H
#define __USER_H

#include "Header.h"

class Status;
class Page;

class User  // class of a friend in the Facebook system
{
private:
	char* name = nullptr;
	Date date_of_birth;
	User** friends = nullptr;
	int num_of_friends = 0, max_friends = 1;
	Status** my_statuses = nullptr;
	int num_of_statuses = 0, max_statuses = 1;
	Page** fan_pages = nullptr;
	int num_of_pages = 0, max_pages = 1;

public:
	User() = delete;
	User(const char* name, Date date_of_birth);
	User(const User& other) = delete; // It is not possible to copy a User
	~User();
	void addFriend(User& new_friend);
	void deleteFriend(User& old_friend);
	void addStatusForUser(Status& new_status);
	void addPage(Page& new_page);
	void deletePage(Page& old_page);
	const char* getName() const { return name; }
	const Date getDateOfBirth() const { return date_of_birth; }
	const int getNumOfStatuses() const { return num_of_statuses; }
	const Status* getStatus(int i) const { return my_statuses[i]; }
	void printFriends() const;
	void printStatusesOfUser() const;
	void printFriendsStatuses() const;
	void printFanPages() const;
};

#endif