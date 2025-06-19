#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <array>

class Day12
{
private:

	std::vector<std::string> lines{ };


public:
	Day12()
	{
		std::string line{ };
		std::ifstream input("day6e.txt");
		while (std::getline(input, line))
			lines.push_back(line);
	}

	int partOne()
	{
		std::vector<std::vector<int>> energy{ };

		std::priority_queue<std::pair<int, int>> next{ };
		for (size_t i = 0; i < lines.size(); i++)
		{
			for (size_t j = 0; j < lines[i].size(); j++)
			{


			}
		}
		return -1;
	}

	int partTwo()
	{

		return -1;
	}
};