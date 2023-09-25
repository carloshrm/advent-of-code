
#include <fstream>
#include <string>
#include <vector>

class Day1
{
	std::vector<std::string> lines{ };

public:
	Day1()
	{
		std::string line{ };
		std::ifstream input("day1.txt");
		while (std::getline(input, line))
			lines.push_back(line);
	}

	int partOne()
	{
		double max_calories{ 0.0 };
		double current_elf{ 0.0 };

		for (std::string_view calorie_value : lines)
		{
			if (calorie_value.empty())
			{
				if (current_elf > max_calories)
				{
					max_calories = current_elf;
				}
				current_elf = 0.0;
			}
			else
			{
				current_elf += strtol(calorie_value.data(), NULL, 10);
			}
		}
		return max_calories;
	}

	double partTwo()
	{
		double first{ 0.0 };
		double second{ 0.0 };
		double third{ 0.0 };

		double current_elf{ 0.0 };
		for (std::string_view calorie_value : lines)
		{
			if (calorie_value.empty())
			{
				if (current_elf > first)
				{
					first = current_elf;
					second = first;
					third = second;
				}
				else if (current_elf > second)
				{
					second = current_elf;
					third = second;
				}
				else if (current_elf > third)
					third = current_elf;
				current_elf = 0.0;
			}
			else
			{
				current_elf += strtol(calorie_value.data(), NULL, 10);
			}
		}
		return first + second + third;
	}

};