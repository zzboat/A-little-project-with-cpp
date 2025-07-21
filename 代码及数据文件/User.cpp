#include "User.h"
#include <vector>

Users::Users() : age(0), gender(' '), height(0), weight(0) {}

Users::Users(const std::string& n, int a, char g, int h, int w)
	: name(n), age(a), gender(g), height(h), weight(w) {
}

std::string Users::getName() const { return name; }
int Users::getAge() const { return age; }
char Users::getGender() const { return gender; }
int Users::getHeight() const { return height; }
int Users::getWeight() const { return weight; }
void Users::setName(const std::string& newName) { name = newName; }
void Users::setAge(const int& newAge) { age = newAge; }
void Users::setGender(const char& newGender) { gender = newGender; }
void Users::setHeight(const int& newHeight) { height = newHeight; }
void Users::setWeight(const int& newWeight) { weight = newWeight; }

std::ostream& operator<<(std::ostream& os, Users& u) {
	os << u.getName() << ','
		<< u.getAge() << ','
		<< u.getGender() << ','
		<< u.getHeight() << ','
		<< u.getWeight();
	return os;
}

std::istream& operator>>(std::istream& is, Users& u) {
	std::string rec;
	std::vector<std::string> vec;
	while (std::getline(is, rec, ',')) {
		vec.push_back(rec);
	}
	if (vec.size() == 5) {
		u.setName(vec[0]);		u.setAge(std::stoi(vec[1]));
		u.setGender(vec[2][0]);	u.setHeight(std::stoi(vec[3]));
		u.setWeight(std::stoi(vec[4]));
	}
	return is;
}

double Users::getBMI() const {
	double BMI = weight * 10000 / (height * height);
	return BMI;
}

std::string Users::getStatus() const {
	double BMI = getBMI();
	if (BMI < 18.5) {
		return "Underweight";
	}
	else if (BMI >= 18.5 && BMI < 24) {
		return "Normal";
	}
	else if (BMI >= 24 && BMI < 28) {
		return "Overweight";
	}
	else {
		return "Obesity";
	}
}

int Users::get_Suggested_Calorie() const {
	double basalMetabolism = 0;

	if (gender == 'M' || gender == 'm') {
		basalMetabolism = 10.0 * weight + 6.25 * height - 5.0 * age + 5.0;
	}
	else if (gender == 'F' || gender == 'f') {
		basalMetabolism = 10.0 * weight + 6.25 * height - 5.0 * age - 161.0;
	}
	else {
		basalMetabolism = 1500.0; 
	}

	double suggestedCalories = basalMetabolism * 1.2;
	return static_cast<int>(suggestedCalories + 0.5);
}

void Users::Get_and_Save_Info() {
	std::cout << "Enter your personal data:" << std::endl;
	std::cout << "Name:";
	std::string Name;
	std::cin >> Name;
	name = Name;

	std::cout << "Age:";
	int Age;
	std::cin >> Age;
	age = Age;

	std::cout << "Gender(F/M):";
	char Gender;
	std::cin >> Gender;
	gender = Gender;

	std::cout << "Height(cm):";
	int Height;
	std::cin >> Height;
	height = Height;

	std::cout << "Weight(kg):";
	int Weight;
	std::cin >> Weight;
	weight = Weight;

	std::cout << "User record saved" << std::endl;
}