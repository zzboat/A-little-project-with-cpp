#include <iomanip>
#include <iostream>
#include "Food.h"

std::ostream& operator<< (std::ostream& os, const Food& food) {
	os << food.getName() << ',' << food.getCalories() << ',' << food.getCategory();
	return os;
};

std::istream& operator>>(std::istream& is, Food& food) {
	std::string name, caloriesStr, category;
	if (std::getline(is, name, ',') &&
		std::getline(is, caloriesStr, ',') &&
		std::getline(is, category)) {
		food.setName(name);
		food.setCalories(std::stoi(caloriesStr));
		food.setCategory(category);
	}
	return is;
};

std::string Food::getName() const { return name; }
int Food::getCalories() const { return calories; }
std::string Food::getCategory() const { return category; }
void Food::setName(const std::string& new_name) { name = new_name; }
void Food::setCalories(const int& new_Calories) { calories = new_Calories; }


Food::Food() {
	name = "Food Item";
	calories = 0;
	category = "Uncategorized";
};

Food::Food(const std::string& new_name, const int new_calories, const std::string new_category) :
	name(new_name), calories(new_calories), category(new_category) {
	name = new_name;
	calories = new_calories;
	category = new_category;
}

void Food::setCategory(const std::string& new_category) {
	category = new_category;
}

Food& Food::operator=(const Food& food) {
	if (this == &food) return *this; 
	name = food.name;
	calories = food.calories;
	category = food.category;
	return *this;
}

Staple_Food::Staple_Food() {
	name = "Staple Food";
	calories = 0;
}

Staple_Food::Staple_Food(const std::string& new_name, const int new_calories) :
	Food(new_name, new_calories, "Staple_Food") {
}

std::string Staple_Food::getCategory() const {
	return "Staple Food";
}

Animal_Proteins::Animal_Proteins() {
	name = "Animal Protein";
	calories = 0;
}

Animal_Proteins::Animal_Proteins(const std::string& new_name, const int new_calories) :
	Food(new_name, new_calories, "Animal_Proteins") {
}

std::string Animal_Proteins::getCategory() const {
	return "Animal_Proteins";
}


Vegetables::Vegetables() {
	name = "Vegetable";
	calories = 0;
}

Vegetables::Vegetables(const std::string& new_name, const int new_calories) :
	Food(new_name, new_calories, "Vegetables") {
}

std::string Vegetables::getCategory() const {
	return "Vegetables";
}

Fruits::Fruits() {
	name = "Fruits";
	calories = 0;
}

Fruits::Fruits(const std::string& new_name, const int new_calories) :
	Food(new_name, new_calories, "Fruits") {
}

std::string Fruits::getCategory() const {
	return "Fruits";
}

Beverages::Beverages() {
	name = "Beverages";
	calories = 0;
}

Beverages::Beverages(const std::string& new_name, const int new_calories) :
	Food(new_name, new_calories, "Beverages") {
}

std::string Beverages::getCategory() const {
	return "Beverages";
}