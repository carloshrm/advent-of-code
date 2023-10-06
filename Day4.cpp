
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <stack>

class Day4
{
	std::vector<std::string> lines{ };

public:
	Day4()
	{
		std::string line{ };
		std::ifstream input("day4.txt");
		while (std::getline(input, line))
			lines.push_back(line);
	}

	int partOne()
	{
		for (std::string_view section : lines)
		{
			size_t fp_div = 0;
			size_t sp_div = 0;

			for (size_t i = 0; i < section.size(); i++)
			{
				if (section[i] == '-')
				{
					if (fp_div == 0)
						fp_div = i;
					else
						sp_div = i;
				}	
			}

			int fp_start{ std::stoi(section, )};
		}
		return 0;
	}

	double partTwo()
	{
		return 0;
	}
};