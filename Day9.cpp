#include <string>
#include <vector>
#include <set>
#include <map>
#include <charconv>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

const std::map<char, std::tuple<int, int>> dir_offset{
	{'D', {	 0,  1}},
	{'U', {	 0,	-1}},
	{'L', {	-1,  0}},
	{'R', {	 1,	 0}},
};

class Day9
{
private:
	std::vector<std::tuple<char, int>> steps{ };

public:
	Day9()
	{
		std::string line{ };
		std::ifstream input("day9.txt");

		while (std::getline(input, line))
		{
			int step_count;
			auto parse = std::from_chars(line.data() + 2, line.data() + line.length(), step_count);
			steps.push_back(std::make_tuple(line[0], step_count));
		}
	}

	int partOne()
	{
		auto my_rope = new Rope();
		for (auto instr : steps)
		{
			my_rope->move(std::get<0>(instr), std::get<1>(instr));
		}
		return my_rope->history.size();
	}

	int partTwo()
	{
		return -1;
	}

	class Knot
	{
	public:
		int x;
		int y;
		Knot(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
	};

	class Rope
	{
	public:
		std::set<std::tuple<int, int>> history{ };
	private:
		Knot *head;
		Knot *tail;

	public:
		Rope()
		{
			head = new Knot(0, 0);
			tail = new Knot(0, 0);
		}

		void move(char dir, int n)
		{
			int x;
			int y;
			std::tie(x, y) = dir_offset.at(dir);
			while (n-- > 0)
			{
				int prev_x = head->x;
				int prev_y = head->y;

				head->x += x;
				head->y += y;
				follow(prev_x, prev_y);
				history.insert(std::make_tuple(tail->x, tail->y));
			}
		}

		void follow(int x, int y)
		{
			int x_distance = head->x - tail->x;
			int y_distance = head->y - tail->y;
			if (std::abs(x_distance) > 1 || std::abs(y_distance) > 1)
			{
				tail->x = x;
				tail->y = y;
			}
		}
	};

};