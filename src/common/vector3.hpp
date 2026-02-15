#pragma once

#include <type_traits>
#include <cmath>
#include <cstdint>

namespace math
{
    template <typename T>
    struct Vector3
    {
        static_assert(std::is_arithmetic<T>::value, "T must be numeric");

        T x = 0;
        T y = 0;
        T z = 0;

        Vector3() : x(0), y(0), z(0) {};
        Vector3(const T s) : x(s), y(s), z(s) {};
        Vector3(const T x, const T y) : x(x), y(y), z(0) {};
        Vector3(const T x, const T y, const T z) : x(x), y(y), z(z) {};
        Vector3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {};

        ~Vector3() = default;

        void operator=(const Vector3<T> &v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
        }

        void operator=(const T s)
        {
            x = s;
            y = s;
            z = s;
        }

        bool operator==(const Vector3<T> &v)
        {
            return x == v.x && y == v.y && z == v.z;
        }

        void operator+=(const Vector3<T> &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
        }

        void operator+=(const T s)
        {
            x += s;
            y += s;
            z += s;
        }

        void operator-=(const Vector3<T> &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        void operator-=(const T s)
        {
            x -= s;
            y -= s;
            z -= s;
        }

        void operator*=(const Vector3<T> &v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
        }

        void operator*=(const T s)
        {
            x *= s;
            y *= s;
            z *= s;
        }

        void operator/=(const Vector3<T> &v)
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;
        }

        void operator/=(const T s)
        {
            x /= s;
            y /= s;
            z /= s;
        }

        Vector3<T> operator+(const Vector3<T> &v)
        {
            return Vector3<T>(x + v.x, y + v.y, z + v.z);
        }

        Vector3<T> operator+(const T s)
        {
            return Vector3<T>(x + s, y + s, z + s);
        }

        Vector3<T> operator-(const Vector3<T> &v)
        {
            return Vector3<T>(x - v.x, y - v.y, z - v.z);
        }

        Vector3<T> operator-(const T s)
        {
            return Vector3<T>(x - s, y - s, z - s);
        }

        Vector3<T> operator-()
        {
            return Vector3<T>(-x, -y, -z);
        }

        Vector3<T> operator*(const Vector3<T> &v)
        {
            return Vector3<T>(x * v.x, y * v.y, z * v.z);
        }

        Vector3<T> operator*(const T s)
        {
            return Vector3<T>(x * s, y * s, z * s);
        }

        Vector3<T> operator/(const Vector3<T> &v)
        {
            return Vector3<T>(x / v.x, y / v.y, z / v.z);
        }

        Vector3<T> operator/(const T s)
        {
            return Vector3<T>(x / s, y / s, z / s);
        }

        Vector3<T> add(const Vector3<T> &v)
        {
            return Vector3<T>(x + v.x, y + v.y, z + v.z);
        }

        Vector3<T> add(const T s)
        {
            return Vector3<T>(x + s, y + s, z + s);
        }

        Vector3<T> subtract(const Vector3<T> &v)
        {
            return Vector3<T>(x - v.x, y - v.y, z - v.z);
        }

        Vector3<T> subtract(const T s)
        {
            return Vector3<T>(x - s, y - s, z - s);
        }

        Vector3<T> negate()
        {
            return Vector3<T>(-x, -y, -z);
        }

        Vector3<T> multiply(const Vector3<T> &v)
        {
            return Vector3<T>(x * v.x, y * v.y, z * v.z);
        }

        Vector3<T> multiply(const T s)
        {
            return Vector3<T>(x * s, y * s, z * s);
        }

        Vector3<T> divide(const Vector3<T> &v)
        {
            return Vector3<T>(x / v.x, y / v.y, z / v.z);
        }

        Vector3<T> divide(const T s)
        {
            return Vector3<T>(x / s, y / s, z / s);
        }

        T length()
        {
            return (T)std::abs(std::sqrt((x * x) + (y * y) + (z * z)));
        }

        T magnitude()
        {
            return (T)std::abs(std::sqrt((x * x) + (y * y) + (z * z)));
        }

        T magnitudeSq()
        {
            return (T)std::abs((x * x) + (y * y) + (z * z));
        }

        T distance(const Vector3<T> &v)
        {
            return subtract(v).magnitude();
        }

        T distanceSq(const Vector3<T> &v)
        {
            return subtract(v).magnitudeSq();
        }

        T dot(const Vector3<T> &v)
        {
            return (T)((x * v.x) + (y * v.y) + (z * v.z));
        }

        Vector3<T> cross(const Vector3<T> &v)
        {
            return Vector3<T>(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            );
        }

        Vector3<T> normalize()
        {
            float mag = magnitude();

            return Vector3<T>(
                (T)(mag > 0.0 ? (x / mag) : 0),
                (T)(mag > 0.0 ? (y / mag) : 0),
                (T)(mag > 0.0 ? (z / mag) : 0)
            );
        }

        Vector3<T> limit(const T s)
        {
            if (magnitude() > s)
            {
                return normalize().multiply(s);
            }

            return Vector3<T>(x, y, z);
        }
    };

    typedef Vector3<float> Vector3f;
    typedef Vector3<double> Vector3d;
    typedef Vector3<int32_t> Vector3i;
    typedef Vector3<int64_t> Vector3l;
}
