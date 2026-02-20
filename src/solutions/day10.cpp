#include <algorithm>
#include <bitset>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include <vector>
#include <unordered_set>

struct Button
{
    uint64_t mask = 0;
    uint64_t max_presses = UINT64_MAX;
    std::vector<uint64_t> indices;
};

struct Machine
{
    uint64_t lights = 0;
    std::vector<Button> buttons;
    std::vector<uint64_t> joltages;

    uint64_t initialize();
    uint64_t energize();

    static Machine create(std::string diagram);
};

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day10.txt" : argv[1]);
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
        Machine machine = Machine::create(line);

        result[0] += machine.initialize();
        result[1] += machine.energize();
    }

    input.close();

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}

Machine Machine::create(std::string diagram)
{
    diagram.erase(std::remove(diagram.begin(), diagram.end(), ' '), diagram.end());

    Machine machine;

    size_t lights_start = diagram.find('[') + 1;
    size_t lights_count = diagram.find(']') - lights_start;
    std::string lights = diagram.substr(lights_start, lights_count);

    uint64_t bitmask = 0x1;

    uint64_t size = 0;
    for(auto l : lights)
    {
        if(l == '#') machine.lights |= (bitmask << size);
        size++;
    }

    size_t joltages_start = diagram.find('{') + 1;
    size_t joltages_count = diagram.find('}') - joltages_start;
    std::string joltages = diagram.substr(joltages_start, joltages_count);

    {
        std::stringstream joltage_ss(joltages);
        std::string part;
        while (std::getline(joltage_ss, part, ','))
        {
            machine.joltages.push_back(std::stoul(part));
        }
    }

    size_t buttons_start = lights_start + lights_count + 1;
    size_t buttons_count = joltages_start - buttons_start - 1;
    std::string buttons = diagram.substr(buttons_start, buttons_count);
    
    buttons = std::regex_replace(buttons, std::regex("\\)\\("), "|");
    buttons = std::regex_replace(buttons, std::regex("\\)|\\("), "");

    {
        std::stringstream buttons_ss(buttons);
        std::string button;
        while (std::getline(buttons_ss, button, '|'))
        {
            Button btn;

            std::stringstream parts_ss(button);
            std::string part;
            while (std::getline(parts_ss, part, ','))
            {
                uint64_t bi = std::stoul(part);
                btn.mask |= (bitmask << bi);
                btn.indices.push_back(bi);
                btn.max_presses = std::min(btn.max_presses, machine.joltages[bi]);
            }

            machine.buttons.push_back(btn);
        }
    }

    std::sort(machine.buttons.begin(), machine.buttons.end(), [](const Button &a, const Button &b) {
        return a.max_presses < b.max_presses;
    });

    return machine;
}

uint64_t Machine::initialize()
{
    uint64_t depth = 0;

    std::vector<uint64_t> states { lights };
    std::vector<uint64_t> next_states;
    std::unordered_set<uint64_t> visited;

    while(depth < buttons.size())
    {
        depth++;

        for(auto state : states)
        {
            for(auto button : buttons)
            {
                if(!(state & button.mask)) continue;

                uint64_t next_state = state ^ button.mask;
                if(!next_state) return depth;
                if(!visited.contains(next_state))
                {
                    next_states.push_back(next_state);
                    visited.emplace(next_state);
                }
            }
        }

        std::swap(states, next_states);
        next_states.clear();
    }

    return 0;
}

uint64_t Machine::energize()
{
    return 0;
}