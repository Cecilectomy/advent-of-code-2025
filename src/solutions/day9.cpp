#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

#include "common/line.hpp"

typedef math::Vector2l Point;
typedef math::Linel Line;
typedef math::AABBl AABB;

int main(int argc, char **argv)
{
    std::filesystem::path path(argc <= 1 ? "input/day9.txt" : argv[1]);
    if (!std::filesystem::exists(path))
    {
        std::cout << "File does not exist: " << path << std::endl;
        return 1;
    }
    std::ifstream input(path);

    uint64_t result[2] = {0, 0};

    Point shoelace = {0, 0};
    std::vector<Line> lines;
    std::vector<Line> outside;

    std::string line;
    while (std::getline(input, line))
    {
        Point p;
        sscanf(line.c_str(), "%ld , %ld", &p.x, &p.y);

        if(!lines.empty())
        {
            lines.back().b = p;

            shoelace.x += (lines.back().a.x * p.y);
            shoelace.y += (lines.back().a.y * p.x);
        }

        lines.push_back({p, {}});
    }

    input.close();

    lines.back().b = lines.front().a;

    shoelace.x += (lines.back().a.x * lines.back().b.y);
    shoelace.y += (lines.back().a.y * lines.back().b.x);

    char winding = ((shoelace.x - shoelace.y) / 2) > 0 ? -1 : 1;

    for (int i = 0; i < lines.size(); i++)
    {
        Line *line = &lines[i];
        Line *prev = i > 0 ? &lines[i - 1] : &lines[lines.size() - 1];
        Line *next = i < lines.size() - 1 ? &lines[i + 1] : &lines[0];

        Point line_n = ((*line).b - (*line).a).normal().normalize() * winding;
        Point prev_n = ((*prev).b - (*prev).a).normal().normalize() * winding;
        Point next_n = ((*next).b - (*next).a).normal().normalize() * winding;

        Line outer = {
            {line->a.x + line_n.x + prev_n.x, line->a.y + line_n.y + prev_n.y},
            {line->b.x + line_n.x + next_n.x, line->b.y + line_n.y + next_n.y}
        };

        outside.push_back(outer);
    }

    for (auto l1 = lines.begin(); l1 != lines.end(); ++l1)
    {
        for (auto l2 = (l1 + 1); l2 != lines.end(); ++l2)
        {
            AABB bb{
                Point{std::min(l1->a.x, l2->a.x), std::min(l1->a.y, l2->a.y)},
                Point{std::max(l1->a.x, l2->a.x), std::max(l1->a.y, l2->a.y)}
            };

            int64_t area = (std::abs(bb.b.x - bb.a.x) + 1) * (std::abs(bb.b.y - bb.a.y) + 1);
            result[0] = area > result[0] ? area : result[0];

            bool collision = false;
            for (auto l : outside)
            {
                if (collision = bb.intersects(l)) break;
            }

            result[1] = !collision && area >= result[1] ? area : result[1];
        }
    }

    std::cout << "Part 1: " << result[0] << "\n";
    std::cout << "Part 2: " << result[1] << "\n";
    std::cout << std::flush;
}
