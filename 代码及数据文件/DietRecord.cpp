#include "DietRecord.h"
#include <iostream>

std::string DietRecord::getDate() const { return date.Now_Date_3(); }
std::string DietRecord::getFoodName() const { return food.getName(); }
std::string DietRecord::getCategory() const { return food.getCategory(); }
int DietRecord::getCalories() const { return food.getCalories(); }
int DietRecord::getWeight() const { return weight; }
void DietRecord::setFood(const Food& new_food) { food = new_food; }
void DietRecord::setQuantity(int new_weight) { weight = new_weight; }
int DietRecord::getTotalCalories() const {
	return (food.getCalories() * 0.01 ) * weight;
}

std::istream& operator>>(std::istream& is,DietRecord& record) {
    std::string line;
    if (std::getline(is, line)) {
        std::istringstream iss(line);
        std::string dateStr, cat, name, weightStr, calStr;

        if (std::getline(iss, dateStr, ',') &&
            std::getline(iss, cat, ',') &&
            std::getline(iss, name, ',') &&
            std::getline(iss, weightStr, ',') &&
            std::getline(iss, calStr)) {

            record.date.setDate(dateStr); 
            record.food.setCategory(cat);
            record.food.setName(name);

            try {
                record.setQuantity(std::stoi(weightStr));
                record.food.setCalories(std::stoi(calStr));
            }
            catch (const std::exception& e) {
                std::cerr << "Error parsing DietRecord: " << e.what() << std::endl;
            }
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const DietRecord& record) {
	os << record.date.Now_Date_3() << ','
		<< record.food.getCategory() << ','
		<< record.food.getName() << ','
		<< record.weight << ','
		<< record.getTotalCalories();
	return os;
}

DietRecord::DietRecord() {
    Date date = Date();
	food = Food();
	weight = 0;
}

DietRecord::DietRecord(const Food& food, int new_weight)
	: food(food), weight(new_weight) {
	Date date;
}