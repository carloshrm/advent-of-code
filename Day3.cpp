
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <stack>

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
					priority_sum += parsePriority(current_item);
					break;
				}
			}		

		}
		return priority_sum;
	}

	double partTwo()
	{
		int badge_priority{ 0 };
		for (size_t i = 0; i < lines.size(); i += 3)
		{
			std::vector<std::string_view> group{ lines[i], lines[i + 1], lines[i + 2] };
			badge_priority += findBadge(group);
		}
		return badge_priority;
	}

private:
	int parsePriority(char letter)
	{
		return (letter > 96) ? (letter - 96) : (letter - 38);
	}

	int findBadge(std::vector<std::string_view> &group)
	{
		for (char c : group[0])
		{
			if (group[1].find(c) != std::string::npos && group[2].find(c) != std::string::npos)
				return parsePriority(c);
		}
		return 0;
	}
};