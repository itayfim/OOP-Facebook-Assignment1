#ifndef __STATUS_H
#define __STATUS_H

#include "Header.h"

struct Text
{
	char* content;
	char* date_of_release;
};

class Status
{
private:
	Text text_status;

public:
	Status() = delete;
	Status(const char* content);
	Status(const Status& other) = delete; // It is not possible to copy a status
	~Status();
	void printStatus() const;
};

#endif