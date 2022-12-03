#ifndef __FACEBOOK_H
#define __FACEBOOK_H

class User;
class Page;

class Facebook
{
private:
	int num_of_users = 0, max_users = 1;
	User** users = nullptr;
	int num_of_pages = 0, max_pages = 1;
	Page** pages = nullptr;

public:
	Facebook();
	Facebook(const Facebook& other) = delete; // It is not possible to copy the Facebook system
	~Facebook();
	void addFriend(User& user); 
	void addPage(Page& page);
	void printUsers() const;
	void printPages() const;
	const int getNumOfUsers() const { return num_of_users; }
	const int getNumOfPages() const { return num_of_pages; }
	User* getUser(int i) const { return users[i]; } // not returning const because somethimes we need to change the User
	Page* getPage(int i) const { return pages[i]; } // not returning const because somethimes we need to change the Page
};


#endif














