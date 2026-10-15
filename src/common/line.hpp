#pragma once

#include "common/vector2.hpp"

namespace math
{
    template <typename T>
    using Point = Vector2<T>;

    template <typename T>
    struct Line
    {
        static_assert(std::is_arithmetic<T>::value, "T must be a numeric type");

        Point<T> a;
        Point<T> b;

        int8_t winding(const Point<T> &c) const
        {
            int64_t val = ((b.y - a.y) * (c.x - b.x)) - ((b.x - a.x) * (c.y - b.y));
            return (val > 0 ? 1 : (val < 0 ? - 1 : 0));
        }

        bool bounds_contains(const Point<T> &p) const
        {
            return (
                std::min(a.x, b.x) <= p.x <= std::max(a.x, b.x)
                && std::min(a.y, b.y) <= p.y <= std::max(a.y, b.y)
            );
        }

        bool intersects(const Line<T> &l) const
        {
            if (
                std::max(a.x, b.x) < std::min(l.a.x, l.b.x)
                || std::max(l.a.x, l.b.x) < std::min(a.x, b.x)
                || std::max(a.y, b.y) < std::min(l.a.y, l.b.y)
                || std::max(l.a.y, l.b.y) < std::min(a.y, b.y)
            )
            {
                return false;
            }

            int64_t o1 = winding(l.a);
            int64_t o2 = winding(l.b);
            int64_t o3 = l.winding(a);
            int64_t o4 = l.winding(b);

            if (o1 != o2 && o3 != o4)
            {
                return true;
            }

            if (o1 == 0 && bounds_contains(l.a)) return true;
            if (o2 == 0 && bounds_contains(l.b)) return true;
            if (o3 == 0 && l.bounds_contains(a)) return true;
            if (o4 == 0 && l.bounds_contains(b)) return true;

            return false;
        }
    };

    template <typename T>
    struct AABB : public Line<T>
    {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");

        bool intersects(const Line<T> &l) const
        {
            return (
                (l.a.x >= Line<T>::a.x && l.a.x <= Line<T>::b.x && l.a.y >= Line<T>::a.y && l.a.y <= Line<T>::b.y) ||
                (l.b.x >= Line<T>::a.x && l.b.x <= Line<T>::b.x && l.b.y >= Line<T>::a.y && l.b.y <= Line<T>::b.y) ||
                (Line<T>{Line<T>::a, {Line<T>::b.x, Line<T>::a.y}}).intersects(l) ||
                (Line<T>{{Line<T>::a.x, Line<T>::b.y}, Line<T>::b}).intersects(l) ||
                (Line<T>{Line<T>::a, {Line<T>::a.x, Line<T>::b.y}}).intersects(l) ||
                (Line<T>{{Line<T>::b.x, Line<T>::a.y}, Line<T>::b}).intersects(l)
            );
        }
    };
}
