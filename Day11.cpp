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
	std::queue<long> items;
	std::function<long long(long long)> task;
	std::pair<int, int> friends;
	int condition;

	Monke(char op, int op_const, std::queue<long> pack, std::pair<int, int> fds, int cond)
	{
		task = [op, op_const](long long item_worry)
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
		friends = fds;
		items = pack;
		condition = cond;
	}

	void catchItem(long item)
	{
		items.push(item);
	}

	int decideBuddy(long worry)
	{
		return (worry % condition == 0) ?
			friends.first : friends.second;
	}

	static Monke parseMonke(const std::vector<std::string_view> info)
	{
		std::queue<long> items{ parseItems(info[1]) };
		auto op = info[2][23];
		int constant{ parseNumber(info[2], 25, info[2].size()) };
		int condition{ parseNumber(info[3], 21, info[3].size()) };
		int first_friend{ parseNumber(info[4], 29, info[4].size()) };
		int secnd_friend{ parseNumber(info[5], 30, info[5].size()) };

		return Monke(op, constant, items, { first_friend, secnd_friend }, condition);
	}

private:
	static std::queue<long> parseItems(const std::string_view item_data)
	{
		std::queue<long> items{};

		size_t start = item_data.find(":");
		size_t num = 0;
		do
		{
			num = item_data.find(",", start + 1);

			if (num == std::string::npos)
				num = item_data.size();

			items.push(parseNumber(item_data, start + 2, num));
			start = num;
		} while (start != item_data.size());

		return items;
	}

	static int parseNumber(const std::string_view s, size_t start, size_t end)
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
	long global_mod{ 0 };
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

	long long getMonkeBusinessLevel()
	{
		long long first = 0;
		long long second = 0;
		for (auto &mky : crew)
		{
			if (mky.business >= first)
			{
				second = first;
				first = (long long)mky.business;
			}
			else if (mky.business > second)
			{
				second = (long long)mky.business;
			}
		}
		return first * second;
	}

	long long partOne()
	{
		setupCrew();
		int rounds{ 20 };
		while (rounds-- > 0)
		{
			for (auto &mky : crew)
			{
				while (!mky.items.empty())
				{
					long long current_item{ mky.task(mky.items.front()) / 3 };
					mky.business++;
					mky.items.pop();
					crew.at(mky.decideBuddy(current_item)).catchItem(current_item);
				}
			}
		}
		return getMonkeBusinessLevel();
	}

	long long partTwo()
	{
		setupCrew();
		int rounds{ 10000 };

		long global_mod{ 1 };
		for (Monke &mky : crew)
		{
			global_mod *= mky.condition;
		}

		while (rounds-- > 0)
		{
			for (Monke &mky : crew)
			{
				while (!mky.items.empty())
				{
					long long current_item{ mky.task(mky.items.front()) };
					current_item = current_item % global_mod;
					mky.business++;
					mky.items.pop();
					crew.at(mky.decideBuddy(current_item)).catchItem(current_item);
				}
			}
		}
		return getMonkeBusinessLevel();;
	}
};
