#include "DietRecord.h"
#include "Database.h"
#include "Menu.h"
#include "Food.h"
#include <sstream>
#include <iomanip>
#include <filesystem>

using namespace std;


static bool needHeader(const string& s) {
	return std::filesystem::file_size(s) == 0;
}

void Greet() {
	string greeting = "Welcome to Calorie Track Daily";
	string frame(greeting.size() + 2, '*');
	string Space(greeting.size(), ' ');
	cout << frame << std::endl;
	cout << '*' << Space << '*' << endl;
	cout << '*' << greeting << '*' << endl;
	cout << '*' << Space << '*' << endl;
	cout << frame << std::endl;
}

void Show_SubMenu() {
	std::cout << "1. Configure Profile  2. Log Meals  3. Nutritional Insights   4. View Meal History  5.  Exit" << std::endl;
	std::cout << "Enter command(1-5):";
}

void Configure_Profile(Users& u) {
	std::cout << "1. Name  2. Age  3. Gender  4. Height  5. Weight  6. Exit" << std::endl;
	std::cout << "Enter command(1-6):";
	int sub_choice;
	std::cin >> sub_choice;

	std::string name;
	string age,gender,height,weight;

	while (sub_choice != 6) {
		switch (sub_choice) {
		case 1:
			std::cout << "Name: ";
			std::cin >> name;
			u.setName(name);
			break;
		case 2:
			std::cout << "Age: ";
			std::cin >> age;
			u.setAge(std::stoi(age));
			break;
		case 3:
			std::cout << "Gender";
			std::cin >> gender;
			u.setGender(gender[0]);
			break;
		case 4:
			std::cout << "Height: ";
			std::cin >> height;
			u.setHeight(std::stoi(height));
			break;
		case 5:
			std::cout << "Weight: ";
			std::cin >> weight;
			u.setWeight(std::stoi(weight));
			break;
		default: cout << "Invalid Command" << endl;
		}
		std::cout << "1. Name  2. Age  3. Gender  4. Height  5. Weight  6. Exit" << std::endl;
		std::cout << "Enter command(1-6):";
		std::cin >> sub_choice;
	}
	std::ofstream ofs("user.csv");
	ofs << "Name" << ',' << "Age" << ',' << "Gender" << ',' << "Height" << ',' << "Weight\n" << u << std::endl;
	ofs.close();
	std::cout << "User database saved." << std::endl;
}

static bool is_inFoodDatabase(const std::string& FoodName) {
	std::ifstream ifs("food_database.csv");
	std::string line;

	if (ifs.good()) 
		std::getline(ifs, line);

	while (std::getline(ifs, line)) {
		std::stringstream ss(line);
		std::string name;
		std::getline(ss, name, ',');

		if (name == FoodName) {
			return true;
		}
	}
	ifs.close();
	return false;
}


void Log_Meals() {
	string s = "food_database.csv";
	Database<Food> db_food(s);
	string s1 = "diet_records.csv";
	Database<DietRecord> db_diet(s1);

	ofstream ofs("diet_records.csv", std::ios::app);
	if (needHeader(s1)) {
		ofs << "Date" << ',' << "Category" << ',' << "Name" << ',' << "weight(g)" << ',' << "Calories(kcal)" << endl;
	}

	DietRecord record;
	char category;
	int calories = 0;
	std::string FoodName;

	std::cout << "Select a category (S/A/V/F/B: Staple Food/Animal Proteins/Vegetables/Fruits/Beverages): " << std::endl;
	std::cin >> category;
	while (category != 'S' && category != 'A' && category != 'V' && category != 'F' && category != 'B') {
		std::cout << "Invalid input." << std::endl;
		std::cout << "Select a category (S/A/V/F/B: Staple Food/Animal Proteins/Vegetables/Fruits/Beverages): " << std::endl;
		std::cin >> category;
	}
	std::cout << "Food name: ";
	std::cin >> FoodName;

	if (! is_inFoodDatabase(FoodName)) {
		std::cout << FoodName <<" " << "is not in the food database" << std::endl;
		std::cout << "Enter calories per 100g (kal/100g): ";
		std::cin >> calories;

		if (category == 'S') {
			Staple_Food food(FoodName, calories);
			record.setFood(food);
			db_food.Add_To_File(food, s);
		}
		else if (category == 'A') {
			Animal_Proteins food(FoodName, calories);
			record.setFood(food);
			db_food.Add_To_File(food, s);
		}
		else if (category == 'V') {
			Vegetables food(FoodName, calories);
			record.setFood(food);
			db_food.Add_To_File(food, s);
		}
		else if (category == 'F') {
			Fruits food(FoodName, calories);
			record.setFood(food);
			db_food.Add_To_File(food, s);
		}
		else {
			Beverages food(FoodName, calories);
			record.setFood(food);
			db_food.Add_To_File(food, s);
		}
	}
	else {
		std::vector<Food> foodList = db_food.Load_From_File(s);
		for (const auto& f:foodList) {
			if (f.getName() == FoodName) {
				record.setFood(f);
				break;
			}
		}
	}
	ofs.close();

	std::cout << "Food weight (g): ";
	int FoodWeight;
	std::cin >> FoodWeight;
	record.setQuantity(FoodWeight);
	
	db_diet.Add_To_File(record, s1);
	std::cout << "Food record saved." << endl;
}

int Cal_Intake(std::vector<DietRecord>& v) {
	int total_calories = 0;
	for (int i = 0; i < v.size(); i++) {
		total_calories += v[i].getTotalCalories();
	}
	return total_calories;
}

int getQuantity(vector<DietRecord>& vec, const string& s) {
	int quantity = 0;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i].getCategory() == s) {
			quantity += vec[i].getWeight();
		}
	}
	return quantity;
}

void Nutritional_Insights(Users& u) {
	string s = "diet_records.csv";
	Database<DietRecord> db_DietRecord;
	std::vector<DietRecord> Diet = db_DietRecord.Load_From_File(s);

	cout << endl;
	string line1(50, '=');
	string line2(50, '-');
	cout << line1 << endl;
	cout << "Daily Diet Analysis Report  (" << Date().Now_Date_1() << ")" << endl;
	cout << line2 << endl;
	cout << "Name: " << u.getName() << endl;
	cout << "Age: " << u.getAge() << endl;
	cout << "Gender(F/M): " << u.getGender() << endl;
	cout << "Height(cm): " << u.getHeight() << endl;
	cout << "Weight(kg): " << u.getWeight() << endl;
	cout << "BMI: " << setprecision(3) << u.getBMI() << endl;
	cout << "Physical Status:" << u.getStatus() << endl;
	cout << endl;
	cout << "Nutritional Intake Profile (daily recommendation in parentheses) : " << endl;
	cout << "Food Energy Intake: " << Cal_Intake(Diet) << " kcal (" << setprecision(3) << u.get_Suggested_Calorie() << " kcal)" << endl;
	cout << "Staple Food: " << getQuantity(Diet, "Staple_Food") << " (200-300g)" << endl;
	cout << "Animal Proteins: " << getQuantity(Diet, "Animal_Proteins") << " (120-200g)" << endl;
	cout << "Vegetables: " << getQuantity(Diet, "Vegetables") << " (300-500g)" << endl;
	cout << "Fruits: " << getQuantity(Diet, "Fruits") << " (200-350g)" << endl;
	cout << "Beverages: " << getQuantity(Diet, "Beverages") << " (300g)" << endl;

	Diet = db_DietRecord.Load_From_File(s);
	ofstream ofs("diet_report.txt");
	ofs << line1 << endl;
	ofs << "Daily Diet Analysis Report  (" << Date().Now_Date_1() << ")" << endl;
	ofs << line2 << endl;
	ofs << "Name: " << u.getName() << endl;
	ofs << "Age: " << u.getAge() << endl;
	ofs << "Gender(F/M): " << u.getGender() << endl;
	ofs << "Height(cm): " << u.getHeight() << endl;
	ofs << "Weight(kg): " << u.getWeight() << endl;
	ofs << "BMI: " << setprecision(3) << u.getBMI() << endl;
	ofs << "Physical Status:" << u.getStatus() << endl;
	ofs << endl;
	ofs << "Nutritional Intake Profile (daily recommendation in parentheses) : " << endl;
	ofs << "Food Energy Intake: " << Cal_Intake(Diet) << " kcal ( " << to_string(u.get_Suggested_Calorie()) << " kcal )"<< endl;
	ofs << "Staple Food: " << getQuantity(Diet, "Staple_Food") << " (200-300g)" << endl;
	ofs << "Animal Proteins: " << getQuantity(Diet, "Animal_Proteins") << "(120-200g)" << endl;
	ofs << "Vegetables: " << getQuantity(Diet, "Vegetables") << " (300-500g)" << endl;
	ofs << "Fruits: " << getQuantity(Diet, "Fruits") << " (200-350g)" << endl;
	ofs << "Beverages: " << getQuantity(Diet, "Beverages") << " (300g)" << endl;
	ofs.close();
}

void View_Meal_History() {
	cout << "Enter date(yyyy/mm/dd): " ;
	string date;
	cin >> date;

	string s = "diet_records.csv";
	Database<DietRecord> db_Diet;
	DietRecord record;
	std::vector<DietRecord> Diet = db_Diet.Load_From_File(s);

	std::vector<DietRecord> filteredDiet;
	for (const auto& d : Diet) {
		date;
		d.getDate();
		if (d.getDate() == date) {
			filteredDiet.push_back(d);
		}
	}

	if (filteredDiet.empty()) {
		cout << "No dietary records found for " << date << " in the database." << endl;
		return;
	}
	else {
		cout << setw(15) << right << "Date"
			<< setw(15) << right << "Category" 
			<< setw(20) << right << "Food Name" 
			<< setw(12) << right << "Weight(g)" 
			<< setw(15) << right << "Calories(kcal)" << endl;
		for (int i = 0; i < filteredDiet.size(); i ++) {
			cout << setw(15) << right << filteredDiet[i].getDate()
				<< setw(15) << right << filteredDiet[i].getCategory()
				<< setw(20) << right << filteredDiet[i].getFoodName()
				<< setw(12) << right << filteredDiet[i].getWeight()
				<< setw(15) << right << filteredDiet[i].getCalories() << endl;
		}
	}
}