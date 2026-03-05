#pragma once
#include <cmath>
#include <stdexcept>

namespace mvmath {

    inline constexpr float eps = 1e-5f;
    
    struct vec2 {
        float x;
        float y;

        constexpr vec2(float x = 0, float y = 0) : x(x), y(y) {}

        vec2 operator+(vec2 v) const{
            return { 
                x + v.x,
                y + v.y
            };
        }

        vec2 operator-(vec2 v) const {
            return { 
                x - v.x,
                y - v.y
            };
        }

        void operator+=(vec2 v) {
            x += v.x;
            y += v.y;
        }
        
        void operator-=(vec2 v) {
            x -= v.x;
            y -= v.y;
        }

        vec2 operator*(float sc) const {
            return { 
                x * sc,
                y * sc
            };
        }

        vec2 operator/(float sc) const {
            return { 
                x / sc,
                y / sc
            };
        }

        void operator*=(float sc) {
            x *= sc;
            y *= sc;
        }
        
        void operator/=(float sc) {
            x /= sc;
            y /= sc;
        }
        
        bool operator==(vec2 v) const {
            return std::fabs(x - v.x) < eps &&
                   std::fabs(y - v.y) < eps;
        }

        bool operator!=(vec2 v) const {
            return std::fabs(x - v.x) >= eps ||
                   std::fabs(y - v.y) >= eps;
        }

        float& operator[](int i) {
            switch(i) {
            case 0: return x; break;
            case 1: return y; break;
            default: throw std::out_of_range("Index " + std::to_string(i) + " is out of bounds.");
            }
        }

        const float& operator[](int i) const {
            switch(i) {
            case 0: return x; break;
            case 1: return y; break;
            default: throw std::out_of_range("Index " + std::to_string(i) + " is out of bounds.");
            }
        }

        float dot(vec2 v) const {
            return x * v.x + y * v.y;
        }

        vec2 sc_mult(float sc) const {
            return *this * sc;
        }

        vec2 sc_div(float sc) const {
            return *this / sc;
        }

        float len() const {
            return std::sqrt(x * x + y * y);
        }

        vec2 norm() const {
            float l = this->len();
            if(l < eps) 
                return vec2();
            return *this / l;
        }
    };
    
    struct vec3 {
        float x;
        float y;
        float z;

        constexpr vec3(float x = 0, float y = 0, float z = 0) 
            : x(x), y(y), z(z) {}

        vec3 operator+(vec3 v) const{
            return { 
                x + v.x,
                y + v.y,
                z + v.z
            };
        }

        vec3 operator-(vec3 v) const {
            return { 
                x - v.x,
                y - v.y,
                z - v.z
            };
        }

        void operator+=(vec3 v) {
            x += v.x;
            y += v.y;
            z += v.z;
        }
        
        void operator-=(vec3 v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        vec3 operator*(float sc) const {
            return { 
                x * sc,
                y * sc,
                z * sc
            };
        }

        vec3 operator/(float sc) const {
            return { 
                x / sc,
                y / sc,
                z / sc
            };
        }

        void operator*=(float sc) {
            x *= sc;
            y *= sc;
            z *= sc;
        }
        
        void operator/=(float sc) {
            x /= sc;
            y /= sc;
            z /= sc;
        }
        
        bool operator==(vec3 v) const {
            return std::fabs(x - v.x) < eps &&
                   std::fabs(y - v.y) < eps &&
                   std::fabs(z - v.z) < eps;
        }

        bool operator!=(vec3 v) const {
            return std::fabs(x - v.x) >= eps ||
                   std::fabs(y - v.y) >= eps ||
                   std::fabs(z - v.z) >= eps;
        }

        float& operator[](int i) {
            switch(i) {
            case 0: return x; break;
            case 1: return y; break;
            case 2: return z; break;
            default: throw std::out_of_range("Index " + std::to_string(i) + " is out of bounds.");
            }
        }

        const float& operator[](int i) const {
            switch(i) {
            case 0: return x; break;
            case 1: return y; break;
            case 2: return z; break;
            default: throw std::out_of_range("Index " + std::to_string(i) + " is out of bounds.");
            }
        }

        float dot(vec3 v) const {
            return x * v.x + y * v.y + z * v.z;
        }
    
        vec3 cross(vec3 v) const {
            return {
                z * v.y - y * v.z,
                x * v.z - z * v.x,
                y * v.x - x * v.y 
            };
        }

        vec3 sc_mult(float sc) const {
            return *this * sc;
        }

        vec3 sc_div(float sc) const {
            return *this / sc;
        }

        float len() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        vec3 norm() const {
            float l = this->len();
            if(l < eps) 
                return vec3();
            return *this / l;
        }
    };

    inline constexpr vec2 Vec2Zero = {0.0f, 0.0f};
    inline constexpr vec3 Vec3Zero = {0.0f, 0.0f, 0.0f};
    
};