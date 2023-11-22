#include <string>
#include <vector>
#include <set>
#include <map>
#include <charconv>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

const std::map<char, std::pair<int, int>> dir_offset{
	{'D', {	 0,  1}},
	{'U', {	 0,	-1}},
	{'L', {	-1,  0}},
	{'R', {	 1,	 0}},
};

class Day9
{
private:
	std::vector<std::pair<char, int>> steps{ };

public:
	Day9()
	{
		std::string line{ };
		std::ifstream input("day9.txt");

		while (std::getline(input, line))
		{
			int step_count;
			auto parse = std::from_chars(line.data() + 2, line.data() + line.length(), step_count);
			steps.push_back({ line[0], step_count });
		}
	}

	int partOne()
	{
		auto my_rope = new Rope();
		for (auto &instr : steps)
		{
			my_rope->move(instr);
		}
		return my_rope->getHistorySize();
	}

	int partTwo()
	{
		auto my_rope = new Rope(9);
		for (auto &instr : steps)
		{
			my_rope->move(instr);
		}
		return my_rope->getHistorySize();
	}

	class Knot
	{
	private:
		inline static int id{ 0 };
	public:
		int my_id;
		int x;
		int y;

		Knot *next;

		Knot(int x, int y)
		{
			this->x = x;
			this->y = y;
			next = nullptr;
			my_id = id++;
		}

		void follow(const Knot *ahead)
		{
			int x_distance = ahead->x - x;
			int y_distance = ahead->y - y;

			if (std::abs(x_distance) > 1 || std::abs(y_distance) > 1)
			{
				if (x_distance != 0)
					x += x_distance > 0 ? 1 : -1;

				if (y_distance != 0)
					y += y_distance > 0 ? 1 : -1;


				if (next)
					next->follow(this);
			}
		}
	};

	class Rope
	{
	private:
		std::set<std::pair<int, int>> tail_pos_log{ };
		Knot *head;
		Knot *tail;

	public:
		Rope()
		{
			head = new Knot(0, 0);
			head->next = new Knot(0, 0);
		}

		Rope(int tail_count)
		{
			head = new Knot(0, 0);
			Knot *current = head;
			while (tail_count-- > 0)
			{
				current->next = new Knot(0, 0);
				current = current->next;
			}
			tail = current;
		}

		void move(std::pair<char, int> instruction)
		{
			auto [x, y] = dir_offset.at(instruction.first);
			int n{ instruction.second };
			while (n-- > 0)
			{
				head->x += x;
				head->y += y;

				head->next->follow(head);
				tail_pos_log.insert({ tail->x, tail->y });
			}
		}

		int getHistorySize()
		{
			return tail_pos_log.size();
		}
	};

};