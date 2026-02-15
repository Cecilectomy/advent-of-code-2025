#include <algorithm>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <set>
#include <vector>

#include "common/vector3.hpp"

typedef math::Vector3l Junction;
typedef std::pair<Junction*, Junction*> Connection;
typedef std::set<Junction*> Circuit;

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day8.txt" : argv[1]);
    if(!std::filesystem::exists(path))
    {
        std::cout << "File does not exist: " << path << std::endl;
        return 1;
    }
    std::ifstream input(path);

    uint64_t limit = argc > 2 ? std::stoi(argv[2]) : 1000;

    uint64_t result[2] = {0, 0};

    std::vector<Junction> junctions;
    std::vector<Connection> connections;
    std::vector<Circuit> circuits;

    std::string line;
    while (std::getline(input, line))
    {
        Junction j;
        sscanf(line.c_str(), "%ld , %ld , %ld", &j.x, &j.y, &j.z);
        junctions.push_back(j);
    }

    input.close();

    for (auto j1 = junctions.begin(); j1 != junctions.end() - 1; ++j1)
    {
        for (auto j2 = j1 + 1; j2 != junctions.end(); ++j2)
        {
            connections.push_back({&(*j1), &(*j2)});
        }
    }

    std::sort(connections.begin(), connections.end(), [](const Connection& a, const Connection& b) {
        return a.first->distanceSq(*a.second) < b.first->distanceSq(*b.second);
    });
    
    for(int i = 0; i < connections.size(); i++)
    {
        if(i >= limit && !result[0])
        {
            std::sort(circuits.begin(), circuits.end(), [](const Circuit& a, const Circuit& b) {
                return a.size() > b.size();
            });

            result[0] = 1;
            for(int c = 0; c < 3 && c < circuits.size(); c++)
            {
                result[0] *= circuits[c].size();
            }
        }

        auto con = connections[i];

        Circuit* a = nullptr;
        Circuit* b = nullptr;

        for(auto &c : circuits)
        {
            a = c.find(con.first) != c.end() ? &c : a;
            b = c.find(con.second) != c.end() ? &c : b;

            if (a && b && a != b)
            {
                a->insert(b->begin(), b->end());
                circuits.erase(circuits.begin() + (b - circuits.data()));
                break;
            }
        }

        if(!b && !a) circuits.emplace_back(Circuit{con.first, con.second});
        else if ((a && b) || a == b) continue;
        else if (a) a->insert(con.second);
        else if (b) b->insert(con.first);

        if(circuits.size() == 1 && circuits[0].size() == junctions.size())
        {
            result[1] = con.first->x * con.second->x;
            break;
        }
    }

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}
