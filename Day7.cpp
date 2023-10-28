#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>

class Day7
{
private:
	struct ElfFolder
	{
		ElfFolder()
		{
			parent = nullptr;
		}

		ElfFolder(ElfFolder *p)
		{
			parent = p;
		}

		int content_size{ 0 };
		std::map<std::string, Day7::ElfFolder *> folders{ };
		ElfFolder *parent;
	};

	ElfFolder *root = nullptr;
	ElfFolder *current_folder = nullptr;

	int findLargest(ElfFolder *f, int limit)
	{
		int internal_sum{ 0 };
		if (f->content_size < limit)
			internal_sum += f->content_size;

		for (auto &[k, v] : f->folders)
			internal_sum += findLargest(v, limit);

		return internal_sum;
	}

	int findSmallestWithinLimits(ElfFolder *f, int free_space)
	{
		int dir_size{ f->content_size };
		for (auto &[k, v] : f->folders)
		{
			int size_check{ findSmallestWithinLimits(v, free_space) };
			if (size_check < dir_size && size_check != 0)
				dir_size = size_check;
		}

		if (free_space + dir_size >= 30000000)
			return dir_size;
		else
			return 0;
	}

public:
	Day7()
	{
		root = new ElfFolder();
		current_folder = root;
		std::string line{ };
		std::ifstream input("day7.txt");
		while (std::getline(input, line))
		{
			if (line[0] == '$')
			{
				auto pos = line.find("cd");
				if (pos != std::string::npos)
				{
					if (line.find("..") != std::string::npos)
					{
						current_folder->parent->content_size += current_folder->content_size;
						current_folder = current_folder->parent;
					}
					else
					{
						if (line.find("/") != std::string::npos)
							current_folder = root;
						else
							current_folder = current_folder->folders[line.substr(pos + 3, line.size() - pos)];
					}
				}
			}
			else
			{
				auto dir = line.find("dir");
				if (dir == std::string::npos)
				{
					int size{ std::stoi(line) };
					current_folder->content_size += size;
				}
				else
				{
					std::string folder_name{ line.substr(dir + 4, line.size() - 4) };
					current_folder->folders.insert_or_assign(folder_name, new ElfFolder(current_folder));
				}

			}
		}
		while (current_folder != root)
		{
			current_folder->parent->content_size += current_folder->content_size;
			current_folder = current_folder->parent;
		}
	}

	int partOne()
	{
		return findLargest(root, 100000);
	}



	int partTwo()
	{
		return findSmallestWithinLimits(root, 70000000 - root->content_size);
	}

};