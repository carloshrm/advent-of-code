#include <string>
#include <vector>
#include <set>
#include <charconv>
#include <fstream>

class Day9
{
private:
	std::vector<std::tuple<char, int>> steps{ };
	std::set<std::tuple<int, int>> history{ };

public:
	Day9()
	{
		std::string line{ };
		std::ifstream input("day9e.txt");

		while (std::getline(input, line))
		{
			int step_count;
			auto parse = std::from_chars(line.data() + 2, line.data() + line.length(), step_count);
			steps.push_back(std::make_tuple(line[0], step_count));
		}
	}

	int partOne()
	{
		auto rope_head = new Rope();
		return -1;
	}

	int partTwo()
	{
		return -1;
	}

	struct Rope
	{
		int x;
		int y;
	};
};