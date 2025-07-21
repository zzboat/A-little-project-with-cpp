#ifndef TERM_PROJECT_DATABASE_H
#define TERM_PROJECT_DATABASE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

template <typename T>
class Database {
public:
	Database() {
		filename = "";
		std::vector<T>;
	}
	Database(std::string& s) : filename(s){
		std::ofstream ofs(s,std::ios::app);
		if (s == "user.csv" && std::filesystem::file_size(s)==0 )
			ofs << "Name" << ',' << "Age" << ',' << " Gender" << ',' << "Height" << ',' << "Weight\n";
		else if (s == "food_database.csv" && std::filesystem::file_size(s) == 0)
			ofs << "Food Name" << ',' << "Calories" << ',' << "Category" << std::endl;
		else if (s == "diet_record.csv" && std::filesystem::file_size(s) == 0 )
			ofs << "Date" << ',' << "Category" << ',' << "Name" << ',' << "Weight(g)" << ',' << "Calories(kcal)" << std::endl;
		ofs.close();
	}

	void Add_To_File(T& t,std::string& s) {
		std::ofstream ofs(s, std::ios::app);
		ofs << t << std::endl;
		ofs.close();
	}

	std::vector<T> Load_From_File(std::string& s) {
		std::ifstream ifs(s);
		std::vector<T> data;
		if (!ifs)
			return data;

		std::string headerLine;
		std::getline(ifs, headerLine);
		std::string line;
		while (std::getline(ifs, line)) {
			std::istringstream iss(line);
			T t;
			if (iss >> t) {
				data.push_back(t);
			}
		}
		ifs.close();
		return data;
	}
private:
	std::string filename;
	std::vector<T> data;
};
#endif