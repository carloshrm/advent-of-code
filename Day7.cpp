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

		std::vector<int> files{ };
		std::map<std::string, Day7::ElfFolder *> folders{ };
		ElfFolder *parent;
	};

	ElfFolder *root = nullptr;
	ElfFolder *current_folder = nullptr;

public:
	Day7()
	{
		root = new ElfFolder();
		current_folder = root;
		std::string line{ };
		std::ifstream input("day7e.txt");
		while (std::getline(input, line))
		{
			if (line[0] == '$')
			{
				auto pos = line.find("cd");
				if (pos != std::string::npos)
				{
					if (line.find("..") != std::string::npos)
						current_folder = current_folder->parent;
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
					current_folder->files.push_back(size);
				}
				else
				{
					std::string folder_name{ line.substr(dir + 4, line.size() - 4) };
					current_folder->folders.insert_or_assign(folder_name, new ElfFolder(current_folder));
				}

			}
		}
	}

	int partOne()
	{

		return -1;
	}

	int partTwo()
	{

		return -1;
	}

};