#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day7.txt" : argv[1]);
    if (!std::filesystem::exists(path))
    {
        std::cout << "File does not exist: " << path << std::endl;
        return 1;
    }
    std::ifstream input(path);

    uint64_t result[2] = {0, 0};

    std::vector<uint64_t> beams;

    std::string line;
    while (std::getline(input, line))
    {
        if (beams.empty())
        {
            beams.resize(line.length());
            std::fill(beams.begin(), beams.end(), 0);
        }

        for (int x = 0; x < line.length(); x++)
        {
            if (line[x] == 'S')
            {
                beams[x] = 1;
            }

            if (line[x] == '^' && beams[x] > 0)
            {
                beams[x - 1] += beams[x];
                beams[x + 1] += beams[x];

                beams[x] = 0;

                result[0]++;
            }
        }
    }

    for (auto b : beams)
    {
        result[1] += b;
    }

    input.close();

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}
