#pragma once
#include <cmath>
#include <stdexcept>

namespace mvmath {

    inline constexpr float eps = 1e-5f;
    
    struct vec2 {
        union {
            float coord[2] = {0, 0};
            struct {
                float x;
                float y;
            };
        };

        constexpr vec2() = default;
        constexpr vec2(float x, float y) : x(x), y(y) {}

        constexpr vec2 operator+(vec2 v) const{
            return { 
                x + v.x,
                y + v.y
            };
        }

        constexpr vec2 operator-(vec2 v) const {
            return { 
                x - v.x,
                y - v.y
            };
        }

        constexpr void operator+=(vec2 v) {
            x += v.x;
            y += v.y;
        }
        
        constexpr void operator-=(vec2 v) {
            x -= v.x;
            y -= v.y;
        }

        constexpr vec2 operator*(float sc) const {
            return { 
                x * sc,
                y * sc
            };
        }

        constexpr vec2 operator/(float sc) const {
            return { 
                x / sc,
                y / sc
            };
        }

        constexpr void operator*=(float sc) {
            x *= sc;
            y *= sc;
        }
        
        constexpr void operator/=(float sc) {
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

        constexpr float& operator[](int i) {
            return coord[i];
        }
        
        constexpr const float& operator[](int i) const {
            return coord[i];
        }

        constexpr float dot(vec2 v) const {
            return x * v.x + y * v.y;
        }

        constexpr vec2 sc_mult(float sc) const {
            return *this * sc;
        }

        constexpr vec2 sc_div(float sc) const {
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
        union {
            float coord[3] = {0, 0, 0};
            struct {
                float x;
                float y;
                float z;
            };
        };

        constexpr vec3() = default;
        constexpr vec3(float x, float y, float z) : x(x), y(y), z(z) {}

        constexpr vec3 operator+(vec3 v) const{
            return { 
                x + v.x,
                y + v.y,
                z + v.z
            };
        }

        constexpr vec3 operator-(vec3 v) const {
            return { 
                x - v.x,
                y - v.y,
                z - v.z
            };
        }

        constexpr void operator+=(vec3 v) {
            x += v.x;
            y += v.y;
            z += v.z;
        }
        
        constexpr void operator-=(vec3 v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        constexpr vec3 operator*(float sc) const {
            return { 
                x * sc,
                y * sc,
                z * sc
            };
        }

        constexpr vec3 operator/(float sc) const {
            return { 
                x / sc,
                y / sc,
                z / sc
            };
        }

        constexpr void operator*=(float sc) {
            x *= sc;
            y *= sc;
            z *= sc;
        }
        
        constexpr void operator/=(float sc) {
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

        constexpr float& operator[](int i) {
            return coord[i];
        }

        constexpr const float& operator[](int i) const {
            return coord[i];
        }

        constexpr float dot(vec3 v) const {
            return x * v.x + y * v.y + z * v.z;
        }
    
        constexpr vec3 cross(vec3 v) const {
            return {
                z * v.y - y * v.z,
                x * v.z - z * v.x,
                y * v.x - x * v.y 
            };
        }

        constexpr vec3 sc_mult(float sc) const {
            return *this * sc;
        }

        constexpr vec3 sc_div(float sc) const {
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
    
    // Orthogonal projection to the center of the screen from a model
    inline mvmath::vec2 central_ortho_project(
        mvmath::vec3 v,
        std::tuple<float, float> v_range,
        std::tuple<int, int> frame
    ) {
        auto [min, max] = v_range;
        auto [width, height] = frame;

        // We use height for both x and y so everything fits on the center
        // square of the frame and it doesn't get stretched or cut
        return {
            (height / (max - min)) * v.x + width / 2.f,
            (height / (max - min)) * v.y + height / 2.f
        };
    }
};