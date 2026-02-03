#include <iostream>
#include <filesystem>
#include <fstream>

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day1.txt" : argv[1]);
    if(!std::filesystem::exists(path))
    {
        std::cout << "File does not exist: " << path << std::endl;
        return 1;
    }
    std::ifstream input(path);

    uint64_t result[2] = {0, 0};
    
    int position = 50;
    
    std::string line;
    while (std::getline(input, line))
    {
        int clicks = std::stoi(line.substr(1));
        int next = (position + (line[0] == 'R' ? clicks : -clicks));

        result[1] += (std::abs(next / 100) + (position && next < 0) + !next);

        position = next % 100;
        position = position < 0 ? 100 + position : position;

        result[0] += !position;
    }

    input.close();

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}
