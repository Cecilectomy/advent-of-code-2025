#include <iostream>
#include <filesystem>
#include <fstream>

uint64_t max_joltage(std::string bank, int count);

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day3.txt" : argv[1]);
    if (!std::filesystem::exists(path))
    {
        std::cout << "File does not exist: " << path << std::endl;
        return 1;
    }
    std::ifstream input(path);

    uint64_t result[2] = {0, 0};

    std::string line;
    while (std::getline(input, line))
    {
        result[0] += max_joltage(line, 2);
        result[1] += max_joltage(line, 12);
    }

    input.close();

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}

uint64_t max_joltage(std::string bank, int count)
{
    int64_t joltage = 0;

    int last = 0;
    for (int b = 0; b < count; b++)
    {
        char bat = 0;
        for (int i = last; i < bank.length() - (count - b - 1); i++)
        {
            char cur = bank.at(i) - '0';

            if (cur > bat)
            {
                bat = cur;
                last = i + 1;
            }
        }

        joltage = joltage * 10 + bat;
    }

    return joltage;
}
