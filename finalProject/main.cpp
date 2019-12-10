#include<iostream>
#include<sstream>
#include<fstream>
#include<set>
#include<map>
#include<vector>
#include<stdexcept>
#include<exception>
#include<iomanip>
#include<algorithm>
#include<cstdlib>
#include"date.h"
#include"database.h"


string getDatePart(string& dateStr, string & part) {
	int i = 0;
	while (dateStr.size() > 0 && i < dateStr.size()) {
		if (dateStr[i] != '-') {
			part += dateStr[i];
		}
		else {
			dateStr.erase(0, i + 1);
			break;
		}
		++i;
	}
	return part;
}

int checkDateFormat(string& partStr, int& dateUnit) {
	try {
		dateUnit = stoi(partStr);
	}
	catch (exception & err) {
		throw "Wrong date format: " + partStr;
	}
	return dateUnit;
}

int main() {
	Database db;
	string command;
	try {
		while (getline(cin, command)) {
			stringstream stream(command);
			string func;
			string event;
			stream >> func;
			if (func != "Add" && func != "Del" && func != "Print" && func != "Find" && func != "") {
				throw "Unknown command: " + func;
			}
			if (func == "Add")
			{
				try {
					int year, month, day;
					string correctStr;
					string dateStr;
					string firstPart = "";
					string secondPart = "";
					string thirdPart = "";
					stream >> dateStr;
					correctStr = dateStr;
					int i = 0;
					try {
						firstPart = getDatePart(dateStr, firstPart);
						if (firstPart != "") {
							year = checkDateFormat(firstPart, year);
						}
						else {
							throw "Wrong date format: " + correctStr;
						}
					}
					catch (exception & err) {
						cout << err.what()<<endl;
					}
					try {
						secondPart = getDatePart(dateStr, secondPart);
						if (secondPart != "") {
							month = checkDateFormat(secondPart, month);
						}
						else {
							throw "Wrong date format: " + correctStr;
						}
					} catch(exception& err) {
						cout << err.what()<<endl;
					}
					try {
						thirdPart = getDatePart(dateStr, thirdPart);
						if (thirdPart != "") {
							day = checkDateFormat(thirdPart, day);
						}
						else {
							throw "Wrong date format: " + correctStr;
						}
					} catch (exception & err) {
						cout << err.what()<<endl;
					}
					Date date(day, month, year);
					stream >> event;
					db.AddEvent(date, event);
				}
				catch (invalid_argument & err) {
					cout << err.what() << endl;
				}
			}
			else if (func == "Del")
			{
				try {
					int year, month, day;
					stream >> year;
					if (stream.peek() != '-') {
						throw exception();
					}
					stream.ignore(1);
					stream >> month;
					if (stream.peek() != '-') {
						throw exception();
					}
					stream.ignore(1);
					stream >> day;
					stream >> event;
					Date date(day, month, year);
					if (event == "") {
						int eventsCount = db.DeleteDate(date);
						cout << "Deleted " << eventsCount << " events" << endl;
					}
					else {
						bool deleted = db.DeleteEvent(date, event);
						if (deleted) {
							cout << "Deleted successfully" << endl;
						}
						else {
							cout << "Event not found" << endl;
						}
					}

				}
				catch (invalid_argument & err) {
					cout << err.what() << endl;
				}
			}
			else if (func == "Find")
			{
				try {
					int year, month, day;
					stream >> year;
					if (stream.peek() != '-') {
						throw exception();
					}
					stream.ignore(1);
					stream >> month;
					if (stream.peek() != '-') {
						throw exception();
					}
					stream.ignore(1);
					stream >> day;
					Date date(day, month, year);
					set<string> resultSet = db.Find(date);
					for (auto a : resultSet) {
						cout << a << endl;
					}
				}
				catch (invalid_argument & err) {
					cout << err.what() << endl;
				}
			}
			else if (func == "Print")
			{
				db.Print();
			}

		}
	}
	catch (string& e) {
		cout << e;
	}
	return 0;
}