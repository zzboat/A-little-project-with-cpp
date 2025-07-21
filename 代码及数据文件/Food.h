#ifndef TERM_PROJECT_FOOD_H
#define TERM_PROJECT_FOOD_H
#include <string>

class Food {
private:
	std::string name;
	int calories;
	std::string category;
public:
	friend std::ostream& operator<< (std::ostream& os, const Food& food);
	friend std::istream& operator>>(std::istream& is, Food& food);

	Food();
	Food(const std::string& new_name, const int new_calories, const std::string new_category);
	std::string getName() const;
	int getCalories() const;
	std::string getCategory() const;
	void setName(const std::string& new_name);
	void setCalories(const int& new_Calories);
	void setCategory(const std::string& new_category);
	Food& operator=(const Food& food);
};

class Staple_Food : public Food {
private:
	std::string name;
	int calories;
public:
	Staple_Food();
	Staple_Food(const std::string& new_name, const int new_calories);
	std::string getCategory() const;
};

class Animal_Proteins :public Food {
private:
	std::string name;
	int calories;
public:
	Animal_Proteins();
	Animal_Proteins(const std::string& new_name, const int new_calories);
	std::string getCategory() const;
};

class Vegetables :public Food {
private:
	std::string name;
	int calories;
public:
	Vegetables(); 
	Vegetables(const std::string& new_name, const int new_calories);
	std::string getCategory() const;
};

class Fruits :public Food {
private:
	std::string name;
	int calories;
public:
	Fruits();
	Fruits(const std::string& new_name, const int new_calories);
	std::string getCategory() const;
};

class Beverages :public Food {
private:
	std::string name;
	int calories;
public:
	Beverages();
	Beverages(const std::string& new_name, const int new_calories);
	std::string getCategory() const;
};
#endif;