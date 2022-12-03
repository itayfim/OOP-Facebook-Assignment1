#pragma once
#include <iostream>
#include <string.h>

#pragma warning(disable: 4996)

#define TEN 10
#define MAX_NAME_LEN 100
#define MAX_STATUS_LEN 1000
#define INVALID -1
#define VALID 0
#define EXIT 12

struct Date {
	int day, month, year;
};

#include "user.h"
#include "page.h"
#include "Facebook.h"
#include "status.h"
#include "functions.h"
