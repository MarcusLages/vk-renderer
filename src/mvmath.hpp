#pragma once
#include <cmath>
#include <tuple>

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
        constexpr vec3(vec2 v2, float z = 0) : x(v2.x), y(v2.y), z(z) {}

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

    struct vec4 {
        union {
            float coord[4] = {0, 0, 0, 0};
            struct {
                float x;
                float y;
                float z;
                float w;
            };
        };

        constexpr vec4() = default;
        constexpr vec4(float x, float y, float z, float w) 
            : x(x), y(y), z(z), w(w) {}
        constexpr vec4(float fill) : x(fill), y(fill), z(fill), w(fill) {}
        constexpr vec4(vec3 v3, float w = 0) 
            : x(v3.x), y(v3.y), z(v3.z), w(w) {}
        constexpr vec4(vec2 v2, float z = 0, float w = 0) 
            : x(v2.x), y(v2.y), z(z), w(w) {}

        constexpr vec4 operator+=(vec4 v) {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }
        
        constexpr vec4 operator-=(vec4 v) {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }

        constexpr vec4 operator+(vec4 v) const{
            vec4 res(*this);
            return res += v;
        }

        constexpr vec4 operator-(vec4 v) const {
            vec4 res(*this);
            return res -= v;
        }

        constexpr vec4 operator*=(float sc) {
            x *= sc;
            y *= sc;
            z *= sc;
            w *= sc;
            return *this;
        }
        
        constexpr vec4 operator/=(float sc) {
            x /= sc;
            y /= sc;
            z /= sc;
            w /= sc;
            return *this;
        }
        
        constexpr vec4 operator*(float sc) const {
            vec4 res(*this);
            return res *= sc;
        }

        constexpr vec4 operator/(float sc) const {
            vec4 res(*this);
            return res /= sc;
        }
        
        bool operator==(vec4 v) const {
            return std::fabs(x - v.x) < eps &&
                   std::fabs(y - v.y) < eps &&
                   std::fabs(z - v.z) < eps &&
                   std::fabs(w - v.w) < eps;
        }

        bool operator!=(vec4 v) const {
            return !(*this == v);
        }

        constexpr float& operator[](int i) {
            return coord[i];
        }

        constexpr const float& operator[](int i) const {
            return coord[i];
        }

        constexpr float dot(vec4 v) const {
            return x * v.x +
                   y * v.y +
                   z * v.z +
                   w * v.w;
        }

        constexpr vec4 sc_mult(float sc) const {
            return *this * sc;
        }

        constexpr vec4 sc_div(float sc) const {
            return *this / sc;
        }

        float len() const {
            return std::sqrt(x * x + y * y + z * z + w * w);
        }

        vec4 norm() const {
            float l = this->len();
            if(l < eps) 
                return vec4();
            return *this / l;
        }

        // Slices z and w coord
        vec2 to_vec2() const {
            return {x, y};
        }

        // Slices z coord
        vec3 to_vec3() const {
            return {x, y, z};
        }

        constexpr static vec4 one() { return vec4(1.); }
    };
    
    struct mat3 {
        union {
            float coord[3][3] = {
                {0, 0, 0},
                {0, 0, 0},
                {0, 0, 0}
            };
            float coord_flat[9];
            struct {
                float ix, jx, kx;
                float iy, jy, ky;
                float iz, jz, kz;
            };
        };

        enum Col {
            X_COL = 0,
            Y_COL = 1,
            Z_COL = 2
        };

        enum Row {
            X_ROW = 0,
            Y_ROW = 1,
            Z_ROW = 2
        };
        
        constexpr mat3() = default;
        constexpr mat3(
            float ix, float jx, float kx,
            float iy, float jy, float ky,
            float iz, float jz, float kz
        ) : coord{
            {ix, jx, kx},
            {iy, jy, ky},
            {iz, jz, kz}
        } {}

        constexpr mat3(vec3 i, vec3 j, vec3 k) 
        : coord{
            {i.x, j.x, k.x},
            {i.y, j.y, k.y},
            {i.z, j.z, k.z}
        } {}

        constexpr mat3(float fill) 
        : coord{
            {fill, fill, fill},
            {fill, fill, fill},
            {fill, fill, fill}
        } {}

        constexpr mat3 operator+=(mat3 m) {
            // TODO: take out 9s and 16s
            for(int i = 0; i < 9; i++) {
                coord_flat[i] += m.coord_flat[i];
            }
            return *this;
        }

        constexpr mat3 operator-=(mat3 m) {
            for(int i = 0; i < 9; i++) {
                coord_flat[i] -= m.coord_flat[i];
            }
            return *this;
        }

        constexpr const mat3 operator+(mat3 m) const {
            mat3 res(*this);
            return res += m;
        }

        constexpr const mat3 operator-(mat3 m) const {
            mat3 res(*this);
            return res -= m;
        }

        constexpr mat3 operator*=(float sc) {
            for(int i = 0; i < 9; i++) {
                coord_flat[i] *= sc;
            }
            return *this;
        }

        constexpr mat3 operator/=(float sc) {
            for(int i = 0; i < 9; i++) {
                coord_flat[i] /= sc;
            }
            return *this;
        }

        constexpr const mat3 operator*(float sc) const {
            mat3 res(*this);
            return res *= sc;
        }

        constexpr const mat3 operator/(float sc) const {
            mat3 res(*this);
            return res /= sc;
        }

        constexpr mat3 operator*=(mat3 m) {
            float _ix = ix * m.ix + jx * m.iy + kx * m.iz;
            float _iy = iy * m.ix + jy * m.iy + ky * m.iz;
            float _iz = iz * m.ix + jz * m.iy + kz * m.iz;
                
            float _jx = ix * m.jx + jx * m.jy + kx * m.jz;
            float _jy = iy * m.jx + jy * m.jy + ky * m.jz;
            float _jz = iz * m.jx + jz * m.jy + kz * m.jz;
                
            float _kx = ix * m.kx + jx * m.ky + kx * m.kz;
            float _ky = iy * m.kx + jy * m.ky + ky * m.kz;
            float _kz = iz * m.kx + jz * m.ky + kz * m.kz;

            ix = _ix; jx = _jx; kx = _kx;
            iy = _iy; jy = _jy; ky = _ky;
            iz = _iz; jz = _jz; kz = _kz;

            return *this;
        }
        
        constexpr const vec3 operator*(const vec3 v) const {
            return {
                ix * v.x + jx * v.y + kx * v.z,
                iy * v.x + jy * v.y + ky * v.z,
                iz * v.x + jz * v.y + kz * v.z
            };
        }

        constexpr const mat3 operator*(mat3 m) const {
            mat3 res(*this);
            return res *= m;
        }
        
        constexpr float* operator[](const int i) {
            return coord[i];
        }

        constexpr const float* operator[](const int i) const {
            return coord[i];
        }

        constexpr float& operator()(const int i, const int j) {
            return coord[i][j];
        }

        constexpr const float& operator()(const int i, const int j) const {
            return coord[i][j];
        }

        constexpr const vec3 row(const Row row) {
            return {coord[row][0], coord[row][1], coord[row][2]};
        }
        
        constexpr const vec3 col(const Col col) {
            return {coord[0][col], coord[1][col], coord[2][col]};
        }

        constexpr static mat3 one() { return mat3(1.); }

        constexpr static mat3 id() {
            return {
                {1., 0., 0.},
                {0., 1., 0.},
                {0., 0., 1.}
            };
        }

        constexpr const float det() const {
            return ix * (jy * kz - ky * jz)
                 - jx * (kz * iy - iz * ky)
                 + kx * (iy * jz - jy * iz);
        }

        constexpr const mat3 transpose() const {
            return {
                ix, iy, iz,
                jx, jy, jz,
                kx, ky, kz
            };
        }

    };

    struct mat4 {
        union {
            float coord[4][4] = {
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            };
            float coord_flat[16];
            struct {
                float ix, jx, kx, lx;
                float iy, jy, ky, ly;
                float iz, jz, kz, lz;
                float iw, jw, kw, lw;
            };
        };

        enum Col {
            X_COL = 0,
            Y_COL = 1,
            Z_COL = 2,
            W_COL = 3
        };

        enum Row {
            X_ROW = 0,
            Y_ROW = 1,
            Z_ROW = 2,
            W_ROW = 3
        };

        constexpr mat4() = default;
        constexpr mat4(
            float ix, float jx, float kx, float lx,
            float iy, float jy, float ky, float ly,
            float iz, float jz, float kz, float lz,
            float iw, float jw, float kw, float lw
        ): coord{
            {ix, jx, kx, lx},
            {iy, jy, ky, ly},
            {iz, jz, kz, lz},
            {iw, jw, kw, lw}
        } {}

        constexpr mat4(vec4 i, vec4 j, vec4 k,  vec4 l) 
        : coord{
            {i.x, j.x, k.x, l.x},
            {i.y, j.y, k.y, l.y},
            {i.z, j.z, k.z, l.z},
            {i.w, j.w, k.w, l.w}
        } {}

        constexpr mat4(float fill) 
        : coord{
            {fill, fill, fill, fill},
            {fill, fill, fill, fill},
            {fill, fill, fill, fill},
            {fill, fill, fill, fill}
        } {}

        constexpr mat4 operator+=(mat4 m) {
            for(int i = 0; i < 16; i++) {
                coord_flat[i] += m.coord_flat[i];
            }
            return *this;
        }

        constexpr mat4 operator-=(mat4 m) {
            for(int i = 0; i < 16; i++) {
                coord_flat[i] -= m.coord_flat[i];
            }
            return *this;
        }

        constexpr const mat4 operator+(mat4 m) const {
            mat4 res(*this);
            return res += m;
        }

        constexpr const mat4 operator-(mat4 m) const {
            mat4 res(*this);
            return res -= m;
        }

        constexpr mat4 operator*=(float sc) {
            for(int i = 0; i < 16; i++) {
                coord_flat[i] *= sc;
            }
            return *this;
        }

        constexpr mat4 operator/=(float sc) {
            for(int i = 0; i < 16; i++) {
                coord_flat[i] /= sc;
            }
            return *this;
        }

        constexpr const mat4 operator*(float sc) const {
            mat4 res(*this);
            return res *= sc;
        }

        constexpr const mat4 operator/(float sc) const {
            mat4 res(*this);
            return res /= sc;
        }

        constexpr mat4 operator*=(mat4 m) {
            float _ix = ix * m.ix + jx * m.iy + kx * m.iz + lx * m.iw;
            float _iy = iy * m.ix + jy * m.iy + ky * m.iz + ly * m.iw;
            float _iz = iz * m.ix + jz * m.iy + kz * m.iz + lz * m.iw;
            float _iw = iw * m.ix + jw * m.iy + kw * m.iz + lw * m.iw;
            
            float _jx = ix * m.jx + jx * m.jy + kx * m.jz + lx * m.jw;
            float _jy = iy * m.jx + jy * m.jy + ky * m.jz + ly * m.jw;
            float _jz = iz * m.jx + jz * m.jy + kz * m.jz + lz * m.jw;
            float _jw = iw * m.jx + jw * m.jy + kw * m.jz + lw * m.jw;
            
            float _kx = ix * m.kx + jx * m.ky + kx * m.kz + lx * m.kw;
            float _ky = iy * m.kx + jy * m.ky + ky * m.kz + ly * m.kw;
            float _kz = iz * m.kx + jz * m.ky + kz * m.kz + lz * m.kw;
            float _kw = iw * m.kx + jw * m.ky + kw * m.kz + lw * m.kw;
            
            float _lx = ix * m.lx + jx * m.ly + kx * m.lz + lx * m.lw;
            float _ly = iy * m.lx + jy * m.ly + ky * m.lz + ly * m.lw;
            float _lz = iz * m.lx + jz * m.ly + kz * m.lz + lz * m.lw;
            float _lw = iw * m.lx + jw * m.ly + kw * m.lz + lw * m.lw;
            
            ix = _ix; iy = _iy; iz = _iz; iw = _iw;
            jx = _jx; jy = _jy; jz = _jz; jw = _jw;
            kx = _kx; ky = _ky; kz = _kz; kw = _kw;
            lx = _lx; ly = _ly; lz = _lz; lw = _lw;
            
            return *this;
        }

        constexpr const vec4 operator*(const vec4 v) const {
            return {
                ix * v.x + jx * v.y + kx * v.z + lx * v.w,
                iy * v.x + jy * v.y + ky * v.z + ly * v.w,
                iz * v.x + jz * v.y + kz * v.z + lz * v.w,
                iw * v.x + jw * v.y + kw * v.z + lw * v.w
            };
        }

        constexpr const mat4 operator*(mat4 m) const {
            mat4 res(*this);
            return res *= m;
        }

        // ! Returns row
        constexpr float* operator[](const int i) {
            return coord[i];
        }

        // ! Returns row
        constexpr const float* operator[](const int i) const {
            return coord[i];
        }

        constexpr float& operator()(const int i, const int j) {
            return coord[i][j];
        }

        constexpr const float& operator()(const int i, const int j) const {
            return coord[i][j];
        }

        constexpr const vec4 row(const Row row) {
            return {coord[row][0], coord[row][1], coord[row][2], coord[row][3]};
        }
        
        constexpr const vec4 col(const Col col) {
            return {coord[0][col], coord[1][col], coord[2][col], coord[3][col]};
        }

        constexpr static mat4 one() { return mat4(1.); }

        constexpr static mat4 id() {
            return {
                {1., 0., 0., 0.},
                {0., 1., 0., 0.},
                {0., 0., 1., 0.},
                {0., 0., 0., 1.}
            };
        }

        constexpr const float det() const {
            // Calculate cofactors first
            float c00 = jy*(kz*lw - lz*kw) - ky*(jz*lw - lz*jw) + ly*(jz*kw - kz*jw);
            float c01 = iy*(kz*lw - lz*kw) - ky*(iz*lw - lz*iw) + ly*(iz*kw - kz*iw);
            float c02 = iy*(jz*lw - lz*jw) - jy*(iz*lw - lz*iw) + ly*(iz*jw - jz*iw);
            float c03 = iy*(jz*kw - kz*jw) - jy*(iz*kw - kz*iw) + ky*(iz*jw - jz*iw);

            return ix*c00 - jx*c01 + kx*c02 - lx*c03;
        }

        constexpr const mat4 transpose() const {
            return {
                ix, iy, iz, iw,
                jx, jy, jz, jw,
                kx, ky, kz, kw,
                lx, ly, lz, lw
            };
        }

        constexpr static mat4 scaling(vec3 v) {
            float x = v.x;
            float y = v.y;
            float z = v.z;
            return {
                x, 0, 0, 0,
                0, y, 0, 0,
                0, 0, z, 0,
                0, 0, 0, 1
            };
        }
        
        constexpr static mat4 translate(vec3 v) {
            return {
                1, 0, 0, v.x,
                0, 1, 0, v.y,
                0, 0, 1, v.z,
                0, 0, 0, 1
            };
        }

        constexpr static mat4 rotate_x(float rad) {
            float c = cos(rad);
            float s = sin(rad);
            return {
                1, 0, 0, 0,
                0, c, s, 0,
                0,-s, c, 0,
                0, 0, 0, 1
            };
        }

        constexpr static mat4 rotate_y(float rad) {
            float c = cos(rad);
            float s = sin(rad);
            return {
                c, 0,-s, 0,
                0, 1, 0, 0,
                s, 0, c, 0,
                0, 0, 0, 1
            };
        }

        constexpr static mat4 rotate_z(float rad) {
            float c = cos(rad);
            float s = sin(rad);
            return {
                c, s, 0, 0,
               -s, c, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            };
        }

        // ! Rotation is done on the XYZ pivot order
        constexpr static mat4 rotate(vec3 euler_rad) {
            return rotate_x(euler_rad.x) * 
                   rotate_y(euler_rad.y) * 
                   rotate_z(euler_rad.z);
        }

        // ! Needless to say, but prev_rot should be orthonormal as a rotation matrix
        inline static mat4 look_at(
            vec3 from, 
            vec3 to,
            vec3 up,                   // Normalized direction vector
            mat4 prev_rot = mat4::id() // Only used for the case of looking directly upwards/downwards
        ) {
            vec3 k = (to - from).norm();
            
            // Handles the case when k == up (which can cause zero-division on 
            // the cross product)
            float k_dot_up = k.dot(up);
            if(std::fabs(k_dot_up) > (1 - eps)) {
                
                // Redoing rotation matrix just because it's faster to get/use 
                // cos/sin directly instead of calculating the acos or acos and
                // passing the angle to mvmath::mat4::rotate_x(theta)
                vec3 k_prev = prev_rot.row(Z_ROW).to_vec3();

                // Signed sine and cosine
                float c = k_prev.dot(k);
                float s = k_prev.cross(k).len();
                if(k_dot_up < 0) s = -s; // Recover the sign lost from len() if k == -up

                mat4 from_prev_rot = 
                    { 1, 0, 0, 0,
                      0, c, s, 0,
                      0,-s, c, 0,
                      0, 0, 0, 1 };

                return from_prev_rot * prev_rot;
            }
            
            vec3 i = up.cross(k).norm();
            vec3 j = k.cross(i).norm();
            vec4 l = {0, 0, 0, 1};
            return mat4(vec4(i), vec4(j), vec4(k), l);
        }

    };

    inline constexpr vec2 vec2_ZERO = vec2();
    inline constexpr vec2 vec2_ONE  = vec2::one();

    inline constexpr vec3 vec3_ZERO = vec3();
    inline constexpr vec3 vec3_ONE  = vec3::one();

    inline constexpr vec4 vec4_ZERO = vec4();
    inline constexpr vec4 vec4_ONE  = vec4::one();

    inline constexpr mat3 mat3_ZERO = mat3();
    inline constexpr mat3 mat3_ONE  = mat3::one();
    inline constexpr mat3 mat3_ID   = mat3::id();

    inline constexpr mat4 mat4_ZERO = mat4();
    inline constexpr mat4 mat4_ONE  = mat4::one();
    inline constexpr mat4 mat4_ID   = mat4::id();

    // * Utils Functions

    constexpr float deg_to_rad(float deg) {
        return (deg * M_PI) / 180;
    }

    constexpr float rad_to_deg(float rad) {
        return (rad * 180) / M_PI;
    }
    
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

    // ! Mus safely clip the object when v.z == camera.z
    constexpr mvmath::vec3 persp_project_tr(
        vec3 v,
        vec3 camera
    ) {
        return v / (1 - v.z / camera.z);
    }

    inline mvmath::vec3 persp_project(
        vec3 v,
        vec3 camera,
        vec3 proj_plane // Indicates the origin of the projection plane
    ) {
        return {
            ((v.x - camera.x) / (v.z - camera.z)) * (proj_plane.z - camera.z) + camera.x,
            ((v.y - camera.y) / (v.z - camera.z)) * (proj_plane.z - camera.z) + camera.y,
            v.z
        };
    }

    inline mvmath::vec3 persp_project(
        vec3 v,
        vec3 camera,
        float fov_rad, // Angle of field of view of the camera
        float max_proj_val
    ) {
        float proj_z = (max_proj_val - camera.x) / tan(M_PI - fov_rad / 2) + camera.z;
        return {
            ((v.x - camera.x) / (v.z - camera.z)) * (proj_z - camera.z) + camera.x,
            ((v.y - camera.y) / (v.z - camera.z)) * (proj_z - camera.z) + camera.y,
            v.z
        };
    }

};