#ifndef TERM_PROJECT_DATE_H
#define TERM_PROJECT_DATE_H
#include <ctime>
#include <string>
#include <sstream>
#include <map>

class Date {
private:
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int second;
	int weekday;
public:
	friend std::ostream& operator<<(std::ostream& os, const Date& date);
	friend std::istream& operator>>(std::istream& is, Date& date);

	Date();
	std::string getMonth() const;
	std::string getDay() const;
	std::string getHour() const;
	std::string getMinute() const;
	std::string getSecond() const;
	std::string Now_Date_1() const;
	std::string Now_Date_2() const;
	std::string Now_Date_3() const;
	void setDate(const std::string&);
};

#endif;