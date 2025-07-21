#include "Date.h"
#include <iomanip>
#include <vector>

std::ostream& operator<<(std::ostream& os, const Date& date) {
	os << date.Now_Date_1();
	return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
	std::string line;
	std::getline(is, line);
	std::stringstream ss(line);
	ss >> date.year >> date.month >> date.day >> date.hour >> date.minute >> date.second >> date.weekday;
	return is;
}

Date::Date() {
	time_t now = time(nullptr);
	tm local_time;
	localtime_s(&local_time, &now);
	year = local_time.tm_year + 1900;
	month = local_time.tm_mon + 1;
	day = local_time.tm_mday;
	hour = local_time.tm_hour;
	minute = local_time.tm_min;
	second = local_time.tm_sec;
	weekday = local_time.tm_wday;
}

std::string Date::getMonth() const {
	const std::map<int, std::string> month_names = {
		{1, "January"}, {2, "February"}, {3, "March"},
		{4, "April"}, {5, "May"}, {6, "June"},
		{7, "July"}, {8, "August"}, {9, "September"},
		{10, "October"}, {11, "November"}, {12, "December"}
	};
	return month_names.at(month);
}

std::string Date::getDay() const {
	const std::map<int, std::string> day_names = {
		{0, "Sunday"}, {1, "Monday"}, {2, "Tuesday"},
		{3, "Wednesday"}, {4, "Thursday"}, {5, "Friday"},
		{6, "Saturday"}
	};
	return day_names.at(weekday);
}

std::string Date::getHour() const {
	return (hour < 10) ? "0" + std::to_string(hour) : std::to_string(hour);
}

std::string Date::getMinute() const {
	return (minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute);
}

std::string Date::getSecond() const {
	return (second < 10) ? "0" + std::to_string(second) : std::to_string(second);
}

std::string Date::Now_Date_1() const {
	return std::to_string(year) + '/' + getMonth() + '/' + getDay();
}

std::string Date::Now_Date_2() const {
	return getDay() + " " + std::to_string(month) + "  " + std::to_string(day) + " " + getHour() + ":" + getMinute() + ":" + getSecond() + " " + std::to_string(year);
}

std::string Date::Now_Date_3() const {
	std::stringstream ss;
	ss << year << '/'
		 << month << '/'
		 << day;
	return ss.str();
}

void Date::setDate(const std::string& s) {
	std::stringstream ss(s);
	std::string token;
	std::vector<std::string> parts;
	while (std::getline(ss, token, '/')) {
		parts.push_back(token);
	}
	if (parts.size() == 3) {
		year = std::stoi(parts[0]);
		month = std::stoi(parts[1]);
		day = std::stoi(parts[2]);
	}
	else {
		*this = Date();
	}
}