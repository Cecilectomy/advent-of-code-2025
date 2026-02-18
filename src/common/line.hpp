#pragma once

#include "common/vector2.hpp"

namespace math
{
    template <typename T>
    struct Line
    {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");

        Vector2<T> a;
        Vector2<T> b;

        bool intersects(const Line<T> &l) const
        {
            // Todo: Replace with actual line intersection formula (this only works for axis aligned perpendicular lines)
            return (
                (a.x == b.x && l.a.y == l.b.y && l.a.x <= a.x && l.b.x >= a.x && l.a.y >= a.y && l.a.y <= b.y) ||
                (a.y == b.y && l.a.x == l.b.x && l.a.y <= a.y && l.b.y >= a.y && l.a.x >= a.x && l.a.x <= b.x)
            );
        }
    };

    typedef Line<float> Linef;
    typedef Line<double> Lined;
    typedef Line<int32_t> Linei;
    typedef Line<int64_t> Linel;

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

    typedef AABB<float> AABBf;
    typedef AABB<double> AABBd;
    typedef AABB<int32_t> AABBi;
    typedef AABB<int64_t> AABBl;
}
