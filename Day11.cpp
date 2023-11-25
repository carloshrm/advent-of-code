#include <fstream>
#include <string>
#include <vector>
#include <charconv>
#include <queue>
#include <iostream>
#include <functional>

#define N_MOKES 7

class Monke
{

public:
	int business{ 0 };
	std::queue<int> items;
	std::function<int(int)> task;
	std::function<int(int)> decision;

	Monke(char op, int op_const, std::queue<int> pack, std::pair<int, int> friends, int condition)
	{
		task = [op, op_const](int item_worry)
			{
				int selected_const = op_const == 0 ? item_worry : op_const;
				switch (op)
				{
				case '+':
					return item_worry + selected_const;
				case '*':
					return item_worry * selected_const;
				default:
					throw;
				}
			};

		decision = [friends, condition](int item_worry)
			{
				return (item_worry % condition == 0) ?
					friends.first : friends.second;
			};

		items = pack;
	}

	void catchItem(int item)
	{
		items.push(item);
	}

	static Monke parseMonke(const std::vector<std::string_view> info)
	{
		std::queue<int> items{ parseItems(info[1]) };
		auto op = info[2][23];
		int constant{ parseNumber(info[2], 25, info[2].size()) };
		int condition{ parseNumber(info[3], 21, info[3].size()) };
		int first_friend{ parseNumber(info[4], 29, info[4].size()) };
		int secnd_friend{ parseNumber(info[5], 30, info[5].size()) };

		return Monke(op, constant, items, { first_friend, secnd_friend }, condition);
	}
private:
	static std::queue<int> parseItems(const std::string_view item_data)
	{
		std::queue<int> items{};

		size_t start = item_data.find(":");
		size_t num = 0;
		do
		{
			num = item_data.find(",", start + 1);
			if (num == std::string::npos)
				num = item_data.size();

			int val{ 0 };
			auto [has_val, _] = std::from_chars(item_data.data() + start + 2, item_data.data() + num, val);
			if (has_val)
				items.push(val);

			start = num;
		} while (start != item_data.size());

		return items;
	}

	static int parseNumber(std::string_view s, size_t start, size_t end)
	{
		int number{ 0 };
		auto [ok, ct_] = std::from_chars(s.data() + start, s.data() + end, number);
		if (ok)
			return number;
		else
			throw;
	};
};

class Day11
{
	std::vector<std::string> lines{ };
	std::vector<Monke> crew{ };

public:
	Day11()
	{
		std::string line{ };
		std::ifstream input("day11.txt");
		while (std::getline(input, line))
			lines.push_back(line);
	}

	void setupCrew()
	{
		crew.clear();
		std::vector<std::string_view> current_monke_info{};
		for (std::string_view ln : lines)
		{
			if (ln.empty())
			{
				crew.push_back(Monke::parseMonke(current_monke_info));
				current_monke_info.clear();
			}
			else
				current_monke_info.push_back(ln);
		}
	}

	int getMonkeBusinessLevel()
	{
		Monke first = crew.at(0);
		Monke second = first;
		for (auto &mky : crew)
		{
			if (mky.business >= first.business)
			{
				second = first;
				first = mky;
			}
			else if (mky.business >= second.business)
				second = mky;
		}
		return first.business * second.business;
	}

	int partOne()
	{
		setupCrew();
		int rounds{ 20 };
		while (rounds-- > 0)
		{
			for (auto &mky : crew)
			{
				while (!mky.items.empty())
				{
					int current_item{ mky.task(mky.items.front()) / 3 };
					mky.business++;
					mky.items.pop();
					crew.at(mky.decision(current_item)).catchItem(current_item);
				}
			}
		}
		return getMonkeBusinessLevel();
	}

	double partTwo()
	{
		return -1;
	}
};
