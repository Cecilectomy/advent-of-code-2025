#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

uint64_t part_1(std::ifstream &stream);
uint64_t part_2(std::ifstream &stream);

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day6.txt" : argv[1]);
    if(!std::filesystem::exists(path))
    {
        std::cout << "File does not exist: " << path << std::endl;
        return 1;
    }
    std::ifstream input(path);

    uint64_t result[2] = {0, 0};

    result[0] = part_1(input);

    input.clear();
    input.seekg(0, std::ios::beg);

    result[1] = part_2(input);

    input.close();

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}

uint64_t part_1(std::ifstream &stream)
{
    uint64_t res = 0;

    std::vector<std::vector<int>> inputs;
    std::vector<char> ops;

    std::string line;
    while (std::getline(stream, line))
    {
        std::stringstream wstream(line);
        std::string wrd;

        int i = 0;
        while (wstream >> wrd)
        {
            if (wrd == "*" || wrd == "+")
            {
                ops.push_back(wrd.at(0));
                continue;
            }

            if (i >= inputs.size())
            {
                inputs.push_back({});
            }

            inputs[i].push_back(stoi(wrd));

            i++;
        }
    }

    for (int i = 0; i < ops.size(); i++)
    {
        char op = ops[i];
        uint64_t acc = op == '*' ? 1 : 0;

        for (int j = 0; j < inputs[i].size(); j++)
        {
            int in = inputs[i][j];

            switch (op)
            {
                case '*':
                    acc *= in;
                    break;
                case '+':
                default:
                    acc += in;
                    break;
            }
        }

        res += acc;
    }

    return res;
}

uint64_t part_2(std::ifstream &stream)
{
    uint64_t res = 0;

    std::vector<std::vector<char>> inputs;
    std::vector<char> ops;

    std::string line;
    while (std::getline(stream, line))
    {
        for (int x = 0; x < line.length(); x++)
        {
            char chr = line.at(x);
            switch (chr)
            {
                case '*':
                case '+':
                    ops.push_back(chr);
                    break;
                default:
                    if (x >= inputs.size())
                    {
                        inputs.push_back({});
                    }
                    inputs[x].push_back(chr);
                    break;
            }
        }
    }

    int prbm = 0;
    int col = 0;
    uint64_t acc = 0;

    for (auto it = inputs.rbegin(); it != inputs.rend(); ++it)
    {
        char op = ops[ops.size() - 1 - prbm];
        acc = col == 0 ? (op == '*' ? 1 : 0) : acc;
        col++;

        std::stringstream buf;
        for (auto d : *it)
        {
            if (d != ' ')
            {
                buf << d;
            }
        }
        std::string num_str = buf.str();

        if (num_str.empty())
        {
            res += acc;
            col = 0;
            prbm++;
            continue;
        }

        switch(op)
        {
            case '*':
                acc *= stoul(num_str);
                break;
            case '+':
            default:
                acc += stoul(num_str);
                break;
        }
    }

    res += acc;

    return res;
}