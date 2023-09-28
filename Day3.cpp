
#include <fstream>
#include <string>
#include <vector>
#include <set>

class Day3
{
	std::vector<std::string> lines{ };

public:
	Day3()
	{
		std::string line{ };
		std::ifstream input("day3.txt");
		while (std::getline(input, line))
			lines.push_back(line);
	}

	int partOne()
	{
		int priority_sum{ 0 };
		for (std::string_view ln : lines)
		{
			std::set<char> stuff{};
			int len{ static_cast<int>(ln.size() / 2) };
			int i{ 0 };
			while (i < len)
			{
				stuff.insert(ln[i++]);
			}

			while (i-- >= 0)
			{
				char current_item{ ln[len + i] };
				if (stuff.contains(current_item))
				{
					priority_sum += (current_item > 96) ? (current_item - 96) : (current_item - 38);
					break;
				}
			}		

		}
		return priority_sum;
	}

	double partTwo()
	{
		return 0;
	}

};