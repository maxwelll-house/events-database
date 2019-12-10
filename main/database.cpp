#include "database.h"

using namespace std;

void Database::AddEvent(const Date& date, const string& event) {
	bool needToAdd = true;
	for (auto item : eventsBase) {
		Date d = item.second;
		if (d == date) {
			if (event == item.first) {
				needToAdd = false;
				break;
			}
		}
	}
	if (needToAdd) {
		eventsBase.insert(pair<string, Date>(event, date));
	}
};
bool Database::DeleteEvent(const Date& date, const string& event) {
	for (auto item : eventsBase) {
		Date d = item.second;
		if (d == date) {
			if (item.first == event) {
				eventsBase.erase(item.first);
				return true;
			}
		}
	}
	return false;
};
int Database::DeleteDate(const Date& date) {
	int count = 0;
	for (auto item : eventsBase) {
		Date d = item.second;
		if (d == date) {
			++count;
			eventsBase.erase(item.first);
		}
	}
	return count;
};

set<string> Database::Find(const Date& date) const {
	set <string> result;
	for (auto item : eventsBase) {
		Date d = item.second;
		if (d == date) {
			result.insert(item.first);
		}
	}
	return result;
};

int countNumbers(int& number) {
	int count = (number == 0) ? 1 : 0;
	while (number != 0) {
		count++;
		number /= 10;
	}
	return count;
}

void Database::Print() const {
	vector <Date> dates;
	vector <string> events;
	for (auto item : eventsBase) {
		events.push_back(item.first);
		dates.push_back(item.second);
	}
	int i = 0;
	while (events.size() > 0) {
		cout << dates[i];
		cout << " " << events[i] << endl;
		if (events.size() > 1 && dates.size() > 1) {
			if (dates[i] < dates[i + 1]) {
				dates.erase(dates.begin() + i);
				events.erase(events.begin() + i);
			}
		}
		else {
			dates.erase(dates.begin());
			events.erase(events.begin());
		}
	}
}