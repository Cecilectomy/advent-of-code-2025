#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>
#include <unordered_map>
#include <vector>

struct ServerRack
{
    std::map<std::string, uint64_t> map;
    std::vector<std::vector<uint64_t>> devices;
    std::unordered_map<uint64_t, uint64_t> path_cache;

    void processDevice(const std::string &definition);
    uint64_t getDeviceID(const std::string &device);
    uint64_t countPaths(uint64_t in, uint64_t out);
    uint64_t countPaths(uint64_t in, uint64_t out, uint64_t dac, uint64_t fft, bool has_dac = false, bool has_fft = false);
};

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day11.txt" : argv[1]);
    if (!std::filesystem::exists(path))
    {
        std::cout << "File does not exist: " << path << std::endl;
        return 1;
    }
    std::ifstream input(path);

    uint64_t result[2] = {0, 0};

    ServerRack server;

    std::string line;
    while (std::getline(input, line))
    {
        server.processDevice(line);
    }

    server.path_cache.clear();
    result[0] = server.countPaths(
        server.getDeviceID("you"),
        server.getDeviceID("out")
    );

    server.path_cache.clear();
    result[1] = server.countPaths(
        server.getDeviceID("svr"),
        server.getDeviceID("out"),
        server.getDeviceID("dac"),
        server.getDeviceID("fft")
    );

    input.close();

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}

void ServerRack::processDevice(const std::string &definition)
{
    auto trim = [](std::string &s)
    {
        s.erase(0, s.find_first_not_of(" \t\n\r\f\v"));

        size_t end = s.find_last_not_of(" \t\n\r\f\v");
        if (end == std::string::npos)
        {
            s.clear();
            return;
        }

        s.erase(end + 1);
    };

    size_t split = definition.find(':');
    std::string device_str = definition.substr(0, split);
    std::string outputs_str = definition.substr(split + 1);

    trim(device_str);
    trim(outputs_str);

    uint64_t did = getDeviceID(device_str);

    std::stringstream outputs_ss(outputs_str);
    std::string output_str;
    while (std::getline(outputs_ss, output_str, ' '))
    {
        uint64_t oid = getDeviceID(output_str);
        devices[did].push_back(oid);
    }
}

uint64_t ServerRack::getDeviceID(const std::string &device)
{
    std::map<std::string, uint64_t>::iterator dit = map.find(device);
    if (dit != map.end())
    {
        return dit->second;
    }

    uint64_t next_id = devices.size();

    map[device] = next_id;
    devices.push_back({});

    return next_id;
}

uint64_t ServerRack::countPaths(uint64_t in, uint64_t out)
{
    return countPaths(in, out, 0, 0, true, true);
}

uint64_t ServerRack::countPaths(uint64_t in, uint64_t out, uint64_t dac, uint64_t fft, bool has_dac, bool has_fft)
{
    has_dac = (in == dac) ? true : has_dac;
    has_fft = (in == fft) ? true : has_fft;

    if (in == out)
    {
        return (has_dac && has_fft) ? 1 : 0;
    }

    uint64_t key = (in << 2) | ((uint64_t)has_dac << 1) | (uint64_t)has_fft;

    std::unordered_map<uint64_t, uint64_t>::iterator it = path_cache.find(key);
    if (it != path_cache.end())
    {
        return it->second;
    }

    uint64_t paths = 0;

    for (uint64_t did : devices[in])
    {
        paths += countPaths(did, out, dac, fft, has_dac, has_fft);
    }

    return path_cache[key] = paths;
}