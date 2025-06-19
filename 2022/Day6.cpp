#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>

class Day6
{
private:

	std::vector<std::string> lines{ };


public:
	Day6()
	{
		std::string line{ };
		std::ifstream input("day6e.txt");
		while (std::getline(input, line))
			lines.push_back(line);
	}

	int partOne()
	{
		std::unordered_set<char> marker_tracker{};
		for (size_t i = 0; i < lines[0].size(); i++)
		{
			char c{ lines[0][i] };

			auto dupe = marker_tracker.find(c);
			if (dupe != marker_tracker.end())
				marker_tracker.erase(marker_tracker.begin(), dupe);
			else
				marker_tracker.insert(c);

			if (marker_tracker.size() == 4)
				return i + 1;
		}
		return -1;
	}

	int partTwo()
	{
		std::unordered_set<char> marker_tracker{};
		for (size_t i = 0; i < lines[0].size(); i++)
		{
			char c{ lines[0][i] };

			auto dupe = marker_tracker.find(c);
			if (dupe != marker_tracker.end())
				marker_tracker.erase(marker_tracker.begin(), dupe);
			else
				marker_tracker.insert(c);

			if (marker_tracker.size() == 14)
				return i + 1;
		}
		return -1;
	}
};