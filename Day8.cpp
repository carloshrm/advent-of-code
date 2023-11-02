#include <fstream>
#include <string>
#include <iostream>
#include <vector>

class Day8
{
private:
	int *map;
	size_t n_cols{ 0 };
	size_t n_rows{ 0 };

	bool checkWestVisibility(size_t i, size_t j, int target_height)
	{
		size_t col{ j };
		while (col-- > 0)
		{
			if (map[(i * n_rows) + col] >= target_height)
				return false;
		}
		return true;
	}

	bool checkEastVisibility(size_t i, size_t j, int target_height)
	{
		size_t col{ j };
		while (col++ < n_cols - 1)
		{
			if (map[(i * n_rows) + col] >= target_height)
				return false;
		}
		return true;
	}

	bool checkNorthVisibility(size_t i, size_t j, int target_height)
	{
		size_t row{ i };
		while (row-- > 0)
		{
			if (map[(row * n_rows) + j] >= target_height)
				return false;
		}
		return true;
	}

	bool checkSouthVisisbility(size_t i, size_t j, int target_height)
	{
		size_t row{ i };
		while (row++ < n_rows - 1)
		{
			if (map[(row * n_rows) + j] >= target_height)
				return false;
		} 
		return true;
	}

public:
	Day8()
	{
		std::string line{ };
		std::ifstream input("day8.txt");
		std::vector<int> parsed_nums{};
		while (std::getline(input, line))
		{
			for (char c : line)
				parsed_nums.push_back((int)c - 48);
		}

		n_cols = line.length();
		n_rows = parsed_nums.size() / n_cols;
		map = new int[n_cols * n_rows];
		for (size_t i = 0; i < n_rows; i++)
		{
			for (size_t j = 0; j < n_cols; j++)
			{
				size_t index{ (i * n_rows) + j };
				map[index] = parsed_nums[index];
			}
		}
	}

	int partOne()
	{
		int edge_trees{ static_cast<int>(((n_rows - 1) * 2) + ((n_cols - 1) * 2)) };
		int total_visible_trees{ edge_trees };
		for (size_t i = 1; i < n_rows - 1; i++)
		{
			for (size_t j = 1; j < n_cols - 1; j++)
			{
				int current_tree{ map[(i * n_rows) + j] };

				if (checkWestVisibility(i, j, current_tree) ||
					checkEastVisibility(i, j, current_tree) ||
					checkNorthVisibility(i, j, current_tree) ||
					checkSouthVisisbility(i, j, current_tree))
				{
					total_visible_trees++;
				}

			}
		}
		return total_visible_trees;
	}

	int partTwo()
	{

		return -1;
	}
};