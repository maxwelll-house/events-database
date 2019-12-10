#pragma once

#include"date.h"
#include <set>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;
class Database {
public:
	void AddEvent(const Date& date, const string& event);
	bool DeleteEvent(const Date& date, const string& event);
	int DeleteDate(const Date& date);

	set<string> Find(const Date& date) const;;

	void Print() const;
private:
	map<string, Date> eventsBase;
};