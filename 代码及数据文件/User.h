#ifndef TERM_PROJECT_USER_H
#define TERM_PROJECT_USER_H
#include <string>
#include <iostream>
#include <sstream>

class Users
{
private:
	std::string name;
	int age;
	char gender;
	int height;
	int weight;
public:
	friend std::istream& operator>>(std::istream& is, Users& u);
	friend std::ostream& operator<<(std::ostream& os, Users& u);

	Users();
	Users(const std::string& n, int a, char g, int h, int w);

	std::string getName() const;
	int getAge() const;
	char getGender() const;
	int getHeight() const;
	int getWeight() const;

	void setName(const std::string& newName);
	void setAge(const int& newAge);
	void setGender(const char& newGender);
	void setHeight(const int& newHeight);
	void setWeight(const int& newWeight);

	Users& operator=(const Users& u);

	double getBMI() const;

	std::string getStatus() const;

	int get_Suggested_Calorie() const;
	void Get_and_Save_Info();
};

#endif;