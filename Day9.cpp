#include <string>
#include <vector>
#include <set>
#include <map>
#include <charconv>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <windows.h>


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
		auto my_rope = new Rope();
		for (auto instr : steps)
		{
			my_rope->move(std::get<0>(instr), std::get<1>(instr));
		}
		return -1;
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
			std::tie (x, y) = dir_offset.at(dir);
			while (n-- > 0)
			{
				head->x += x;
				head->y += y;
				tailFollow();
			}
		}

		void tailFollow()
		{

		}
	};
	
};