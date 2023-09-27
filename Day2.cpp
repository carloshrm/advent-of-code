
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Day2
{
	std::vector<std::string> lines{ };



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
		const std::map<char, int> hand_scores{ {'X', 1}, {'Y', 2}, {'Z', 3} };
		double score{ 0 };
		for (std::string_view ln : lines)
		{
			score += hand_scores.at(ln[2]);
			const char elf_hand{ (ln[0] - '@') };
			const char my_hand{ (ln[2] - 'W') };

			if (my_hand == elf_hand)
				score += 3;
			else
			{
				if ((my_hand == 1 && elf_hand == 3) ||
					(my_hand == 2 && elf_hand == 1) ||
					(my_hand == 3 && elf_hand == 2))
				{
					score += 6;
				}
			}
		}
		return score;
	}

	double partTwo()
	{
		const std::map<char, int> hand_scores{ {'A', 1}, {'B', 2}, {'C', 3} };
		double score{ 0 };
		for (std::string_view ln : lines)
		{
			const char outcome{ ln[2] };
			const char elf_hand{ ln[0] };

			if (outcome == 'X')
			{
				if (elf_hand == 'A')
					score += 3;
				else if (elf_hand == 'B')
					score += 1;
				else
					score += 2;
			}
			else if (outcome == 'Z')
			{
				score += 6;
				if (elf_hand == 'A')
					score += 2;
				else if (elf_hand == 'B')
					score += 3;
				else
					score += 1;
			}
			else
			{
				score += 3 + hand_scores.at(elf_hand);
			}
		}
		return score;
	}

};