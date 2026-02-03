#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day5.txt" : argv[1]);
    if(!std::filesystem::exists(path))
    {
        std::cout << "File does not exist: " << path << std::endl;
        return 1;
    }
    std::ifstream input(path);

    uint64_t result[2] = {0, 0};

    std::vector<std::pair<uint64_t, uint64_t>> fresh;

    std::string line;
    while (std::getline(input, line))
    {
        if (line.empty())
        {
            break;
        }

        size_t split = line.find('-');
        uint64_t begin = std::stoul(line.substr(0, split));
        uint64_t end = std::stoul(line.substr(split + 1));

        for (auto it = fresh.begin(); it != fresh.end();)
        {
            if (
                (it->first >= begin && it->second <= end) ||
                (begin >= it->first && end <= it->second) ||
                (begin >= it->first && begin <= it->second) ||
                (end >= it->first && end <= it->second)
            )
            {
                begin = std::min(begin, it->first);
                end = std::max(end, it->second);
                it = fresh.erase(it);
                continue;
            }

            ++it;
        }

        fresh.push_back({begin, end});
    }

    while (std::getline(input, line))
    {
        uint64_t check = std::stoul(line);

        bool found = false;
        for (auto range : fresh)
        {
            if (!found && check >= range.first && check <= range.second)
            {
                result[0]++;
                found = true;
            }
        }
    }
    
    input.close();

    for (auto range : fresh)
    {
        result[1] += (range.second - range.first + 1);
    }

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}