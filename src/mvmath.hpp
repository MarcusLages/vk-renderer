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
        constexpr vec2(float fill) : x(fill), y(fill) {}
        
        constexpr vec2 operator+=(vec2 v) {
            x += v.x;
            y += v.y;
            return *this;
        }
        
        constexpr vec2 operator-=(vec2 v) {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        constexpr vec2 operator+(vec2 v) const{
            vec2 res(*this);
            return res += v;
        }

        constexpr vec2 operator-(vec2 v) const {
            vec2 res(*this);
            return res -= v;
        }

        constexpr vec2 operator*=(float sc) {
            x *= sc;
            y *= sc;
            return *this;
        }
        
        constexpr vec2 operator/=(float sc) {
            x /= sc;
            y /= sc;
            return *this;
        }
        
        constexpr vec2 operator*(float sc) const {
            vec2 res(*this);
            return res *= sc;
        }

        constexpr vec2 operator/(float sc) const {
            vec2 res(*this);
            return res /= sc;
        }
        
        bool operator==(vec2 v) const {
            return std::fabs(x - v.x) < eps &&
                   std::fabs(y - v.y) < eps;
        }

        bool operator!=(vec2 v) const {
            return !(*this == v);
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

        constexpr static vec2 one() { return vec2(1.); }

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
        constexpr vec3(float fill) : x(fill), y(fill), z(fill) {}

        constexpr vec3 operator+=(vec3 v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        
        constexpr vec3 operator-=(vec3 v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        constexpr vec3 operator+(vec3 v) const{
            vec3 res(*this);
            return res += v;
        }

        constexpr vec3 operator-(vec3 v) const {
            vec3 res(*this);
            return res -= v;
        }

        constexpr vec3 operator*=(float sc) {
            x *= sc;
            y *= sc;
            z *= sc;
            return *this;
        }
        
        constexpr vec3 operator/=(float sc) {
            x /= sc;
            y /= sc;
            z /= sc;
            return *this;
        }
        
        constexpr vec3 operator*(float sc) const {
            vec3 res(*this);
            return res *= sc;
        }

        constexpr vec3 operator/(float sc) const {
            vec3 res(*this);
            return res /= sc;
        }
        
        bool operator==(vec3 v) const {
            return std::fabs(x - v.x) < eps &&
                   std::fabs(y - v.y) < eps &&
                   std::fabs(z - v.z) < eps;
        }

        bool operator!=(vec3 v) const {
            return !(*this == v);
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
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x 
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

        // Slices z coord
        vec2 to_vec2() const {
            return {x, y};
        }
        
        constexpr static vec3 one() { return vec3(1.); }
    };

    inline constexpr vec2 vec2_ZERO = vec2();
    inline constexpr vec2 vec2_ONE  = vec2::one();

    inline constexpr vec3 vec3_ZERO = vec3();
    inline constexpr vec3 vec3_ONE  = vec3::one();
    
    // This version uses cross product so it performs more calculations and
    // executes more code, but it is a cool naive formula
    inline float signed_tri_area_cross(vec2 a, vec2 b, vec2 c) {
        vec3 ab = {b.x - a.x, b.y - a.y, 1};
        vec3 ac = {c.x - a.x, c.y - a.y, 1};
        return ab.cross(ac).z / 2;
    }

    // Uses Gauss shoelace formula (basically calculates the determinant of 3x3)
    // It's order dependent, but it's faster and .obj files make sure to always
    // follow a counter clockwise order so there's no problem
    inline float signed_tri_area(vec2 a, vec2 b, vec2 c) {
        return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) * 0.5;
    }

    // Orthogonal projection to the center of the screen from a model
    inline mvmath::vec2 central_ortho_project(
        vec3 v,
        std::tuple<float, float> v_range,
        std::tuple<int, int> frame
    ) {
        auto [min, max] = v_range;
        auto [width, height] = frame;

        // We use height for both x and y so everything fits on the center
        // square of the frame and it doesn't get stretched or cut
        return {
            ((v.x - min) * height) / (max - min),
            ((v.y - min) * height) / (max - min)
        };
    }

    // Similar to the normal central orthographic projection function above 
    // (central_ortho_project), but instead also normalizes the z coordinate
    // instead of ignoring it (0=nearest, 1=farthest)
    // (use in z-buffer calculations)
    inline mvmath::vec3 central_ortho_project_z(
        vec3 v,
        std::tuple<float, float> v_range,
        std::tuple<int, int> frame
    ) {
        auto [min, max] = v_range;
        auto [width, height] = frame;

        // We use height for both x and y so everything fits on the center
        // square of the frame and it doesn't get stretched or cut

        return {
            ((v.x - min) * height) / (max - min),
            ((v.y - min) * height) / (max - min),
            1 - ((v.z - min) / (max - min)) // -1 to make 0=nearest, 1=farthest
        };
    }

};