#include <fstream>
#include <string>
#include <vector>
#include <charconv>
#include <stack>
#include <map>
#include <sstream>

class Day5
{
private:

	std::vector<std::string> instructions{ };

	std::map<int, std::stack<char>> crates{ };

	void buildCrates(std::vector<std::string> info)
	{	
		std::string_view stack_nums{ info.back() };
		for (size_t i = 0; i < stack_nums.length(); i++)
		{
			if (isdigit(stack_nums[i]))
			{
				int current_stack{ stack_nums[i] - '0' };

				for (size_t j = info.size() - 1; j-- > 0;)
				{
					char current_crate{ info[j][i] };
					if (isalpha(current_crate))
					{
						crates[current_stack].push(current_crate);
					}						
				}
			}
		}		
	}

public:
	Day5()
	{
		std::string line{ };
		std::ifstream input("day5.txt");

		std::vector<std::string> crate_info{ };
		bool is_instruction = false;
		while (std::getline(input, line))
		{
			if (line.size() < 2)
			{
				is_instruction = true;
			}
			else
			{
				if (is_instruction)
					instructions.push_back(line);
				else
					crate_info.push_back(line);
			}
		}
		buildCrates(crate_info);
	}

	std::string partOne()
	{
		for (std::string i : instructions)
		{
			std::stringstream instr{ i };

			int n{ 0 }, from{ 0 }, to{ 0 };
			std::string tmp{};
			instr >> tmp >> n >> tmp >> from >> tmp >> to;
			while (n --> 0)
			{
				auto crate = crates[from].top();
				crates[from].pop();
				crates[to].push(crate);
			}
		}
		std::string result{};
		for (auto& [n, stack] : crates)
			result += stack.top();
		return result;
	}

	std::string partTwo()
	{
		for (std::string i : instructions)
		{
			std::stringstream instr{ i };

			int n{ 0 }, from{ 0 }, to{ 0 };
			std::string tmp{};
			instr >> tmp >> n >> tmp >> from >> tmp >> to;
			
			std::stack<char> temp{};
			while (n-- > 0)
			{
				auto crate = crates[from].top();
				crates[from].pop();
				temp.push(crate);
			}
			while (!temp.empty())
			{
				char c = temp.top();
				temp.pop();
				crates[to].push(c);
			}
		}

		std::string result{};
		for (auto &[n, stack] : crates)
			result += stack.top();
		return result;
	}
};