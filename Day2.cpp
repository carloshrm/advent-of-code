
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Day2
{
	std::vector<std::string> lines{ };

	const std::map<char, int> hand_scores{ {'X', 1}, {'Y', 2}, {'Z', 3} };

public:
	Day2()
	{
		std::string line{ };
		std::ifstream input("day2.txt");
		while (std::getline(input, line))
			lines.push_back(line);
	}

	int partOne()
	{
		double score{ 0 };
		for (std::string_view ln : lines)
		{
			score += hand_scores.at(ln[2]);
			const char op_hand{ (ln[0] - '@') };
			const char my_hand{ (ln[2] - 'W') };

			if (my_hand == op_hand)
				score += 3;
			else
			{
				if ((my_hand == 1 && op_hand == 3) ||
					(my_hand == 2 && op_hand == 1) ||
					(my_hand == 3 && op_hand == 2))
				{
					score += 6;
				}
			}
		}
		return score;
	}

	double partTwo()
	{
		return 0;
	}

};