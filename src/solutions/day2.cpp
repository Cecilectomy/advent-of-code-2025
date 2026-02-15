#include <iostream>
#include <filesystem>
#include <fstream>

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day2.txt" : argv[1]);
    if (!std::filesystem::exists(path))
    {
        std::cout << "File does not exist: " << path << std::endl;
        return 1;
    }
    std::ifstream input(path);

    std::stringstream buffer;
    buffer << input.rdbuf();
    input.close();

    uint64_t result[2] = {0, 0};

    std::string line;
    while (std::getline(buffer, line, ','))
    {
        size_t split = line.find('-');
        uint64_t begin = std::stoul(line.substr(0, split));
        uint64_t end = std::stoul(line.substr(split + 1));

        for (uint64_t id = begin; id <= end; id++)
        {
            std::string check = std::to_string(id);
            size_t len = check.length();
            size_t hlen = len / 2;

            if (!(len & 1) && check.substr(0, hlen) == check.substr(hlen))
            {
                result[0] += stoul(check);
            }

            std::string pattern = check + check;
            std::string matched = pattern.substr(1, pattern.length() - 2);

            if (matched.find(check) != std::string::npos)
            {
                result[1] += stoul(check);
            }
        }
    }

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}