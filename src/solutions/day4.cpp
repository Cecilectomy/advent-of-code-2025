#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

void next_line(std::ifstream &stream, std::vector<std::string> &lines);
int roll_remover(std::ifstream &stream, bool proceed = false);

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day4.txt" : argv[1]);
    if (!std::filesystem::exists(path))
    {
        std::cout << "File does not exist: " << path << std::endl;
        return 1;
    }
    std::ifstream input(path);

    uint64_t result[2] = {0, 0};

    result[0] = roll_remover(input, false);

    input.clear();
    input.seekg(0, std::ios::beg);

    result[1] = roll_remover(input, true);

    input.close();

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}

void next_line(std::ifstream &stream, std::vector<std::string> &lines)
{
    std::string buf;
    std::getline(stream, buf);

    if (!buf.empty())
    {
        lines.push_back(buf);
    }
}

int roll_remover(std::ifstream &stream, bool proceed)
{
    std::vector<std::string> lines;

    next_line(stream, lines);
    next_line(stream, lines);

    int removed = 0;

    int line = 0;
    while (!lines[line].empty())
    {
        std::string *prev = line > 0 ? &lines[line - 1] : nullptr;
        std::string *curr = &lines[line];
        std::string *next = line < lines.size() - 1 ? &lines[line + 1] : nullptr;

        for (int x = 0; x < curr->length(); x++)
        {
            if (curr->at(x) != '@')
            {
                continue;
            }

            int acc = 0;

            acc += (prev && prev->at(x) == '@') ? 1 : 0;                               // N
            acc += (next && next->at(x) == '@') ? 1 : 0;                               // S
            acc += (x < curr->length() - 1 && curr->at(x + 1) == '@') ? 1 : 0;         // E
            acc += (x > 0 && curr->at(x - 1) == '@') ? 1 : 0;                          // W
            acc += (prev && x > 0 && prev->at(x - 1) == '@') ? 1 : 0;                  // NW
            acc += (next && x > 0 && next->at(x - 1) == '@') ? 1 : 0;                  // SW
            acc += (prev && x < prev->length() - 1 && prev->at(x + 1) == '@') ? 1 : 0; // NE
            acc += (next && x < next->length() - 1 && next->at(x + 1) == '@') ? 1 : 0; // SE

            if (acc < 4)
            {
                removed += 1;

                if (proceed)
                {
                    (*curr)[x] = 'x';
                }
            }
        }

        line = line + (proceed && curr->find('x') != std::string::npos && line > 0 ? -1 : 1);

        std::replace(curr->begin(), curr->end(), 'x', '.');

        next_line(stream, lines);
    }

    return removed;
}
