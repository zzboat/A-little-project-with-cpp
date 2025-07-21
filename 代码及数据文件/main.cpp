#include "Database.h"
#include "DietRecord.h"
#include "Menu.h"
#include <sstream>
#include <string>

using namespace std;

int main() {
	Greet();

	Users u;
	string s = "user.csv";
	string line;
	ifstream ifs(s);
	if (line != "Name,Age,Gender,Height,Weight") {
		getline(ifs, line);
	}
	getline(ifs, line);
	istringstream iss(line);
	iss >> u;
	ifs.close();

	if (u.getName().empty()) {
		u.Get_and_Save_Info();
		ofstream ofs(s, ios::app);
		ofs << "Name" << ',' << "Age" << ',' << "Gender" << ',' << "Height" << ',' << "Weight\n" 
			<< u << endl;
		ofs.close();
	}

	std::cout << "Hi " << u.getName() << "! Current time :" << Date().Now_Date_2() << std::endl;
	std::cout << std::endl;

	Show_SubMenu();

	int choice;
	std::cin >> choice;
	while ( choice != 5 ) {
		switch (choice) {
		case 1: Configure_Profile(u); 
			break;//更改个人信息
		case 2: Log_Meals();
			break;//记录饮食
		case 3: Nutritional_Insights(u);
			break;//营养分析
		case 4: View_Meal_History();
			break;//查看饮食记录
		default: std::cout << "Invalid Command" << std::endl;
		}
		Show_SubMenu();
		std::cin >> choice;
	}
	std::string line_1(50,'=');
	std::cout << line_1 << std::endl;
	std::cout << std::endl;
	std::cout << "Start Tracking → Start Shining. Goodbye, " << u.getName() << "^_^" << std::endl;
	std::cout << std::endl;
	std::cout << line_1 << std::endl;
	return 0;
}