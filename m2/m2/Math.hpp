//
//  Math.hpp
//  m2
//
//  Created by Arthur Sun on 8/24/18.
//  Copyright © 2018 Arthur Sun. All rights reserved.
//

#ifndef Math_hpp
#define Math_hpp

#include "Common.hpp"
#include <cmath>
#include <cfloat>

typedef float float32_t;
typedef double float64_t;

#define M2_PI 3.14159265358979323846f
#define M2_PHI 1.6180339887498948482f

namespace m2 {
    inline float32_t map(const float32_t& a, const float32_t& b, const float32_t& c, const float32_t& d, const float32_t& e)
    {
        return (a-b)/(c-b)*(e-d)+d;
    }
    /// @return a number to another number by a fraction a + (b-a) * u
    inline float32_t lerp(const float32_t& a, const float32_t& b, const float32_t& u)
    {
        return a + (b-a) * u;
    }
    template <typename T>
    inline T min(T a, T b){
        return a < b ? a : b;
    }
    template <typename T>
    inline T max(T a, T b){
        return a > b ? a : b;
    }
    template <typename T>
    inline T Constrain(T a, T b, T c){
        return a < b ? b : (a > c ? c : a);
    }
    template <typename T>
    inline T abs(T a){
        return a >= T(0) ? a : -a;
    }
    struct Transform;
    struct Vec2
    {
        float32_t x;
        float32_t y;
        Vec2(){}
        Vec2(float32_t x, float32_t y) : x(x), y(y){}
        void SetAngle(float32_t a);
        Vec2(float32_t a){
            SetAngle(a);
        }
        void Set(float32_t x, float32_t y);
        void Set(const Vec2& v);
        /// Set this vector to a unit vector of an angle
        float32_t GetAngle() const;
        void Rotate(const Vec2& v);
        void ApplyTransform(const Transform&);
        /// if possible, use this intead if Vec2::Mag()
        float32_t MagSq() const;
        float32_t Mag() const;
        float32_t Normalize();
        void Lerp(const Vec2& v, float32_t u);
        void Normalize(float32_t& m);
        void operator *= (float32_t a);
        void operator += (const Vec2& a);
        void operator -= (const Vec2& a);
        /// Dot(v, other) = Cross(v.Skew(), other)
        inline Vec2 Skew() const
        {
            return Vec2(-y, x);
        }
        /// a.Inv() = Vec2(a.x, -a.y)
        inline Vec2 Inv() const
        {
            return Vec2(x, -y);
        }
    };
    struct mat22
    {
        Vec2 x;
        Vec2 y;
        mat22();
        mat22(float32_t n00, float32_t n01, float32_t n10, float32_t n11);
        mat22(const Vec2& x, const Vec2& y);
        Vec2 operator * (const Vec2& v) const
        {
            return Vec2(x.x*v.x+y.x*v.y, x.y*v.x+y.y*v.y);
        }
        void Set(float32_t n00, float32_t n01, float32_t n10, float32_t n11);
        void Set(const Vec2& x, const Vec2& y);
        void Set(const mat22& m);
        Vec2 Solve(const Vec2 &a) const;
        void SetRotation(const Vec2 &q);
        bool GetInv(mat22& m) const;
        inline mat22 T() const
        {
            return mat22(x.x, x.y, y.x, y.y);
        }
        inline mat22 operator * (const mat22& a) const
        {
            return mat22(x.x*a.x.x + y.x*a.x.y, x.x*a.y.x + y.x*a.y.y, x.y*a.x.x + y.y*a.x.y, x.y*a.y.x + y.y*a.y.y);
        }
        inline float32_t det() const
        {
            return x.x*y.y - x.y*y.x;
        }
        void SetIdentity();
    };
    //
    inline Vec2 operator * (float32_t a, const Vec2& v){
        return Vec2(a*v.x, a*v.y);
    }
    inline Vec2 operator - (const Vec2& a){
        return Vec2(-a.x, -a.y);
    }
    inline float32_t Dot(const Vec2& a, const Vec2& b){
        return a.x*b.x + a.y*b.y;
    }
    inline float32_t Cross(const Vec2& a, const Vec2& b){
        return a.x*b.y - a.y*b.x;
    }
    inline Vec2 operator + (const Vec2& v1, const Vec2& v2){
        return Vec2(v1.x+v2.x, v1.y+v2.y);
    }
    inline Vec2 operator - (const Vec2& v1, const Vec2& v2){
        return Vec2(v1.x-v2.x, v1.y-v2.y);
    }
    inline bool operator == (const Vec2& v1, const Vec2& v2){
        return v1.x == v2.x && v1.y == v2.y;
    }
    inline bool operator != (const Vec2& v1, const Vec2& v2){
        return v1.x != v2.x || v1.y != v2.y;
    }
    //
    struct Transform
    {
        Vec2 p;
        Vec2 q;
        Transform(){
            q.Set(1.0f, 0.0f);
        }
        Transform(const Vec2& a, const Vec2& b){
            p.Set(a);
            q.Set(b);
        }
        Transform(const Vec2& a, float32_t b){
            p.Set(a);
            q.SetAngle(b);
        }
        inline void Set(const Vec2& a, const Vec2& b){
            p.Set(a);
            q.Set(b);
        }
        inline void Set(const Vec2& a, float32_t b){
            p.Set(a);
            q.SetAngle(b);
        }
        inline float32_t GetAngle() const
        {
            return atan2f(q.y, q.x);
        }
        inline Vec2 operator * (const Vec2& v) const
        {
            return Vec2((q.x*v.x - q.y*v.y) + p.x, (q.y*v.x + q.x*v.y) + p.y);
        }
    };
    struct AABB
    {
        Vec2 lowerBound;
        Vec2 upperBound;
        AABB(){}
        AABB(const Vec2& lower, const Vec2& upper);
        void Combine(const AABB& a, const AABB& b);
        bool In(const AABB& a) const;
        bool Contains(const AABB& a) const;
        Vec2 GetCenter() const;
        float32_t GetArea() const;
        Vec2 GetExtents() const;
        float32_t GetPerimeter() const;
        bool vsAABB(const AABB& a) const;
        bool vsPoint(const Vec2& a) const;
    };
    /// @brief Add these rotation vectors
    inline Vec2 Mul(const Vec2& a, const Vec2& b){
        return Vec2(a.x*b.x - a.y*b.y, a.y*b.x + a.x*b.y);
    }
    /// @brief rotate a vector by another
    /// @param a The vector to be rotated
    inline Vec2 Rot(const Vec2& a, const Vec2& b){
        Vec2 t = a;
        t.Rotate(b);
        return t;
    }
    /// @brief Apply a transform on another
    inline Transform Mul(const Transform &a, const Transform &b)
    {
        return Transform(Rot(b.p , a.q)+ a.p, Mul(a.q, b.q));
    }
    inline void Vec2::ApplyTransform(const Transform& t)
    {
        this->Set(t * *this);
    }
}

#endif /* Math_hpp */
