#pragma once

#include <type_traits>
#include <cmath>
#include <cstdint>

namespace math
{
    template <typename T>
    struct Vector2
    {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");

        T x = 0;
        T y = 0;

        Vector2() : x(0), y(0) {};
        Vector2(const T s) : x(s), y(s) {};
        Vector2(const T x, const T y) : x(x), y(y) {};
        Vector2(const Vector2<T> &v) : x(v.x), y(v.y) {};

        ~Vector2() = default;

        bool operator==(const Vector2<T> &v)
        {
            return (x == v.x && y == v.y);
        }

        void operator=(const Vector2<T> &v)
        {
            x = v.x;
            y = v.y;
        }

        void operator=(const T s)
        {
            x = s;
            y = s;
        }

        void operator+=(const Vector2<T> &v)
        {
            x += v.x;
            y += v.y;
        }

        void operator+=(const T s)
        {
            x += s;
            y += s;
        }

        void operator-=(const Vector2<T> &v)
        {
            x -= v.x;
            y -= v.y;
        }

        void operator-=(const T s)
        {
            x -= s;
            y -= s;
        }

        void operator*=(const Vector2<T> &v)
        {
            x *= v.x;
            y *= v.y;
        }

        void operator*=(const T s)
        {
            x *= s;
            y *= s;
        }

        void operator/=(const Vector2<T> &v)
        {
            x /= v.x;
            y /= v.y;
        }

        void operator/=(const T s)
        {
            x /= s;
            y /= s;
        }

        Vector2<T> operator+(const Vector2<T> &v)
        {
            return Vector2<T>(x + v.x, y + v.y);
        }

        Vector2<T> operator+(const T s)
        {
            return Vector2<T>(x + s, y + s);
        }

        Vector2<T> operator-(const Vector2<T> &v)
        {
            return Vector2<T>(x - v.x, y - v.y);
        }

        Vector2<T> operator-(const T s)
        {
            return Vector2<T>(x - s, y - s);
        }

        Vector2<T> operator-()
        {
            return Vector2<T>(-x, -y);
        }

        Vector2<T> operator*(const Vector2<T> &v)
        {
            return Vector2<T>(x * v.x, y * v.y);
        }

        Vector2<T> operator*(const T s)
        {
            return Vector2<T>(x * s, y * s);
        }

        Vector2<T> operator/(const Vector2<T> &v)
        {
            return Vector2<T>(x / v.x, y / v.y);
        }

        Vector2<T> operator/(const T s)
        {
            return Vector2<T>(x / s, y / s);
        }

        Vector2<T> add(const Vector2<T> &v)
        {
            return Vector2<T>(x + v.x, y + v.y);
        }

        Vector2<T> add(const T s)
        {
            return Vector2<T>(x + s, y + s);
        }

        Vector2<T> subtract(const Vector2<T> &v)
        {
            return Vector2<T>(x - v.x, y - v.y);
        }

        Vector2<T> subtract(const T s)
        {
            return Vector2<T>(x - s, y - s);
        }

        Vector2<T> negate()
        {
            return Vector2<T>(-x, -y);
        }

        Vector2<T> multiply(const Vector2<T> &v)
        {
            return Vector2<T>(x * v.x, y * v.y);
        }

        Vector2<T> multiply(const T s)
        {
            return Vector2<T>(x * s, y * s);
        }

        Vector2<T> divide(const Vector2<T> &v)
        {
            return Vector2<T>(x / v.x, y / v.y);
        }

        Vector2<T> divide(const T s)
        {
            return Vector2<T>(x / s, y / s);
        }

        T length()
        {
            return (T)std::abs(std::sqrt((x * x) + (y * y)));
        }

        T magnitude()
        {
            return (T)std::abs(std::sqrt((x * x) + (y * y)));
        }

        T magnitudeSq()
        {
            return (T)std::abs((x * x) + (y * y));
        }

        T distance(const Vector2<T> &v)
        {
            return subtract(v).magnitude();
        }

        T distanceSq(const Vector2<T> &v)
        {
            return subtract(v).magnitudeSq();
        }

        T dot(const Vector2<T> &v)
        {
            return (T)((x * v.x) + (y * v.y));
        }

        Vector2<T> normal()
        {
            return Vector2<T>(-y, x);
        }

        Vector2<T> normalize()
        {
            T mag = magnitude();

            return Vector2<T>(
                (T)(mag > 0 ? (x / mag) : 0),
                (T)(mag > 0 ? (y / mag) : 0)
            );
        }

        Vector2<T> limit(const T s)
        {
            if (magnitude() > s)
            {
                return normalize().multiply(s);
            }

            return Vector2<T>(x, y);
        }
    };

    typedef Vector2<float> Vector2f;
    typedef Vector2<double> Vector2d;
    typedef Vector2<int32_t> Vector2i;
    typedef Vector2<int64_t> Vector2l;
}
