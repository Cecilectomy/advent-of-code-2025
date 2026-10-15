#include <bitset>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>
#include <unordered_set>

struct Joltage
{
    uint64_t mask = 0;
    uint64_t parity = 0;

    std::vector<uint64_t> required;

    void calculate();
};

struct Machine
{
    std::vector<uint64_t> buttons;
    Joltage joltage;
    uint64_t lights = 0;

    std::vector<uint64_t> sequences(uint64_t parity);
    
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

void Joltage::calculate()
{
    mask = 0x0;
    parity = 0x0;

    for(size_t j = 0; j < required.size(); j++)
    {
        if(required[j] > 0) mask |= (1ULL << j);
        if(required[j] % 2) parity |= (1ULL << j);
    }
}

std::vector<uint64_t> Machine::sequences(uint64_t parity)
{
    std::unordered_set<uint64_t> valid;

    for (uint64_t sequence = 0; sequence < (1ULL << buttons.size()); sequence++)
    {
        uint64_t state = 0x0;
        
        for(size_t b = 0; b < buttons.size(); b++)
        {
            if((sequence & (1ULL << b)))
            {
                state ^= buttons[b];
            }
        }

        if(state == parity) valid.emplace(sequence);
    }

    return std::vector<uint64_t>(valid.begin(), valid.end());
}

uint64_t Machine::initialize()
{
    uint64_t min_depth = UINT64_MAX;

    std::vector<uint64_t> sequences = this->sequences(lights);

    for(uint64_t sequence : sequences)
    {
        min_depth = std::min(std::bitset<64>(sequence).count(), min_depth);
    }

    return min_depth;
}

uint64_t Machine::energize()
{
    joltage.calculate();

    if(!joltage.mask) return 0;

    uint64_t min_presses = UINT64_MAX;

    std::vector<uint64_t> sequences = this->sequences(joltage.parity);

    for(uint64_t sequence : sequences)
    {
        std::vector<uint64_t> sequence_values(joltage.required.size(), 0);
        uint64_t pressed = 0;

        for (size_t b = 0; b < buttons.size(); b++)
        {
            if ((sequence & (1ULL << b)))
            {
                pressed++;

                for (size_t j = 0; j < joltage.required.size(); j++)
                {
                    sequence_values[j] += (buttons[b] & (1ULL << j)) ? 1 : 0;
                }
            }
        }

        bool valid = true;
        Machine next_machine = (*this);

        for (size_t j = 0; j < next_machine.joltage.required.size(); ++j) {
            if (sequence_values[j] > next_machine.joltage.required[j]) {
                valid = false;
                break;
            }

            next_machine.joltage.required[j] = (next_machine.joltage.required[j] - sequence_values[j]) / 2;
        }

        if (!valid) continue;

        uint64_t cost = next_machine.energize();

        min_presses = (cost != UINT64_MAX) ? std::min(min_presses, pressed + 2 * cost) : min_presses;
    }

    return min_presses;
}

Machine Machine::create(std::string diagram)
{
    diagram.erase(std::remove(diagram.begin(), diagram.end(), ' '), diagram.end());

    Machine machine;

    size_t lights_start = diagram.find('[') + 1;
    size_t lights_count = diagram.find(']') - lights_start;
    std::string lights_str = diagram.substr(lights_start, lights_count);

    for(size_t i = 0; i < lights_str.length(); i++)
    {
        if(lights_str[i] == '#') machine.lights |= (1ULL << i);
    }

    size_t joltages_start = diagram.find('{') + 1;
    size_t joltages_count = diagram.find('}') - joltages_start;
    std::string joltages_str = diagram.substr(joltages_start, joltages_count);

    {
        std::stringstream joltages_ss(joltages_str);
        std::string part;
        while (std::getline(joltages_ss, part, ','))
        {
            machine.joltage.required.push_back(std::stoull(part));
        }
    }

    machine.joltage.calculate();

    size_t buttons_start = lights_start + lights_count + 1;
    size_t buttons_count = joltages_start - buttons_start - 1;
    std::string buttons_str = diagram.substr(buttons_start, buttons_count);
    
    buttons_str = std::regex_replace(buttons_str, std::regex("\\)\\("), "|");
    buttons_str = std::regex_replace(buttons_str, std::regex("\\)|\\("), "");

    {
        std::stringstream buttons_ss(buttons_str);
        std::string button_str;
        while (std::getline(buttons_ss, button_str, '|'))
        {
            uint64_t button = 0;

            std::stringstream parts_ss(button_str);
            std::string part;
            while (std::getline(parts_ss, part, ','))
            {
                button |= (1ULL << std::stoull(part));
            }

            machine.buttons.push_back(button);
        }
    }

    return machine;
}
