#ifndef __PAGE_H
#define __PAGE_H

class User;
class Status;

class Page
{
private:
	char* name = nullptr;
	int num_of_followers = 0, max_followers = 1;
	User** followers = nullptr;
	int num_of_statuses = 0, max_statuses = 1;
	Status** page_statuses = nullptr;

public:
	Page() = delete; 
	Page(const char* name);
	Page(const Page& other) = delete; // It is not possible to copy a fan page
	~Page();
	void addFollower(User& new_follower); 
	void deleteFollower(User& old_follower); 
	void addStatusForPage(Status& new_status); 
	const char* getName() const; 
	const int getNumOfStatuses() const { return num_of_statuses; }
	const Status* getStatus(int i) const { return page_statuses[i]; }
	void printFollowers() const;
	void printStatusesOfPage() const;
};

#endif

