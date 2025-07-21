#ifndef TERM_PROJECT_DIET_RECORD_H
#define TERM_PROJECT_DIET_RECORD_H
#include "Food.h"
#include "Date.h"

class DietRecord {
private:
	Date date; 
	Food food;
	int weight; 
public:
	friend std::istream& operator>>(std::istream& is, DietRecord& record);
	friend std::ostream& operator<<(std::ostream& os, const DietRecord& record);

	DietRecord();
	DietRecord(const Food& food, int new_weight);
	std::string getDate() const;
	std::string getFoodName() const;
	std::string getCategory() const;
	int getCalories() const;
	int getWeight() const;
	void setFood(const Food& new_food);
	void setQuantity(int new_weight);
	int getTotalCalories() const;
};

#endif;