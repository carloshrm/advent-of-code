#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <charconv>
#include <iostream>
#include <Windows.h>

class Day10
{
	std::vector<std::string> lines{ };

public:
	Day10()
	{
		std::string line{ };
		std::ifstream input("day10.txt");
		while (std::getline(input, line))
			lines.push_back(line);
	}

	int partOne()
	{
		CRT monitor{ CRT() };
		int sig_str{ 0 };
		for (std::string_view line : lines)
		{
			auto op = line.find(" ");
			if (op == std::string::npos)
			{
				sig_str += monitor.pulse();
			}
			else
			{
				int val;
				auto [has_val, _] = std::from_chars(line.data() + op + 1, line.data() + line.size(), val);
				sig_str += monitor.pulse(val);
			}
		}
		return sig_str;
	}

	double partTwo()
	{
		return partOne();
	}

	class CRT
	{
	private:
		int sig_threshold;
		int clock;
		int x;

	public:
		CRT()
		{
			sig_threshold = 20;
			clock = 1;
			x = 1;
		}

		void draw()
		{
			char current_pixel = '.';
			int clock_val = (clock - 1) % 40;
			for (int i = -1; i <= 1; i++)
			{
				int sprite = x + i;
				if (clock_val == sprite)
					current_pixel = '#';
			}
			COORD c{ clock_val, ((int)clock / 40) };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			std::cout << current_pixel;
		}

		void addx(int val)
		{
			x += val;
		}

		int pulse(int v = 0)
		{
			draw();
			clock++;
			if (v != 0)
			{
				int inner = pulse();
				addx(v);
				return inner;
			}
			return checkSignalStrength();
		}

		int checkSignalStrength()
		{
			if (clock == sig_threshold)
			{
				sig_threshold += 40;
				return x * clock;
			}
			else
				return 0;
		}
	};
};