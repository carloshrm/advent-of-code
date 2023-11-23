#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <charconv>

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
				sig_str += monitor.pulse();
				monitor.addx(val);
				sig_str += monitor.pulse();
			}
		}
		return sig_str;
	}

	// crt
	// clockPulse, setter ++
	// check str
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

		void addx(int val)
		{
			x += val;
		}

		int pulse()
		{
			clock++;
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
	double partTwo()
	{
		return -1;
	}
};