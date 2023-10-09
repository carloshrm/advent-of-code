
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <charconv>
#include <utility>

class Day4
{
private:
	std::vector<std::string> lines{ };

	std::pair<int, int> parseRange(std::string_view part)
	{
		size_t div = part.find("-");

		std::string_view const fp_start_str{ part.substr(0, div) };
		int fp_start_num{ 0 };
		std::from_chars(fp_start_str.data(), fp_start_str.data() + fp_start_str.size(), fp_start_num);

		std::string_view const fp_end_str{ part.substr(div + 1, part.size() - div) };
		int fp_end_num{ 0 };
		std::from_chars(fp_end_str.data(), fp_end_str.data() + fp_end_str.size(), fp_end_num);

		return std::make_pair(fp_start_num, fp_end_num);
	}

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
		int overlap{ 0 };
		for (std::string_view section : lines)
		{
			size_t division = section.find(",");
			std::string_view const first_part{ section.substr(0, division) };
			std::string_view const secnd_part{ section.substr(division + 1, section.size() - division) };

			auto first_range = parseRange(first_part);
			auto second_range = parseRange(secnd_part);

			if (first_range.first == second_range.first)
				overlap++;
			else
			{
				if (first_range.first < second_range.first)
				{
					if (first_range.second >= second_range.second)
						overlap++;
				}
				else
				{
					if (first_range.second <= second_range.second)
						overlap++;
				}
			}
		}
		return overlap;
	}

	double partTwo()
	{
		int overlap{ 0 };
		for (std::string_view section : lines)
		{
			size_t division = section.find(",");
			std::string_view const first_part{ section.substr(0, division) };
			std::string_view const secnd_part{ section.substr(division + 1, section.size() - division) };
			auto first_range = parseRange(first_part);
			auto second_range = parseRange(secnd_part);

			if (first_range.first == second_range.first)
				overlap++;
			else
			{
				if (first_range.first > second_range.first)
				{
					if (second_range.second >= first_range.first)
						overlap++;
				}
				else
				{
					if (second_range.first <= first_range.second)
						overlap++;
				}
			}
		}
		return overlap;
	}
};