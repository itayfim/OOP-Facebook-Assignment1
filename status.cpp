#include "status.h"
#include "ctime"
using namespace std;

Status::Status(const char* content)
{
	text_status.content = new char[strlen(content) + 1];
	strcpy(text_status.content, content);
	time_t now = time(0);
	text_status.date_of_release = new char[strlen(ctime(&now)) + 1];
	strcpy(text_status.date_of_release, ctime(&now)); // Put in the release date the time now
}

Status::~Status()
{
	delete[]text_status.content;
	delete[]text_status.date_of_release;
}

void Status::printStatus() const
{
	cout << text_status.content << endl;
	cout << "Status creation date: " << text_status.date_of_release << endl;
}
