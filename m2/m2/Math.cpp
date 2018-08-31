//
//  Math.cpp
//  m2
//
//  Created by Arthur Sun on 8/30/18.
//  Copyright © 2018 Arthur Sun. All rights reserved.
//

#include "Math.hpp"

namespace m2 {
    inline void Vec2::Set(float32_t x, float32_t y){
        this->x = x;
        this->y = y;
    }
    inline void Vec2::Set(const Vec2& v){
        x = v.x;
        y = v.y;
    }
    /// Set this vector to a unit vector of an angle
    void Vec2::SetAngle(float32_t a)
    {
        x = cosf(a);
        y = sinf(a);
    }
    float32_t Vec2::GetAngle() const
    {
        return atan2f(y, x);
    }
    inline void Vec2::Rotate(const Vec2& v)
    {
        float32_t _x = x;
        x = x*v.x - y*v.y;
        y = _x*v.y + y*v.x;
    }
    /// if possible, use this intead if Vec2::Mag()
    inline float32_t Vec2::MagSq() const
    {
        return x * x + y * y;
    }
    inline float32_t Vec2::Mag() const
    {
        return sqrtf(x * x + y * y);
    }
    inline float32_t Vec2::Normalize()
    {
        float32_t m = Mag();
        if(m < FLT_EPSILON) m = FLT_EPSILON;
        x *= 1.0f/m;
        y *= 1.0f/m;
        return m;
    }
    inline void Vec2::Normalize(float32_t& m)
    {
        if(m < FLT_EPSILON) m = FLT_EPSILON;
        x *= 1.0f/m;
        y *= 1.0f/m;
    }
    inline void Vec2::operator *= (float32_t a){
        x *= a;
        y *= a;
    }
    inline void Vec2::operator += (const Vec2& a){
        x += a.x;
        y += a.y;
    }
    inline void Vec2::operator -= (const Vec2& a){
        x -= a.x;
        y -= a.y;
    }
    /// Dot(v, other) = Cross(v.Skew(), other)
    inline Vec2 Vec2::Skew() const
    {
        return Vec2(-y, x);
    }
    /// a.GetInv() = Vec2(a.x, -a.y)
    inline Vec2 Vec2::GetInv() const
    {
        return Vec2(x, -y);
    }
    mat22::mat22(){
        SetIdentity();
    }
    mat22::mat22(float32_t n00, float32_t n01, float32_t n10, float32_t n11){
        x.Set(n00, n10);
        y.Set(n01, n11);
    }
    mat22::mat22(const Vec2& x, const Vec2& y){
        this->x = x;
        this->y = y;
    }
    inline Vec2 mat22::operator * (const Vec2& v) const
    {
        return Vec2(x.x*v.x+y.x*v.y, x.y*v.x+y.y*v.y);
    }
    inline void mat22::Set(float32_t n00, float32_t n01, float32_t n10, float32_t n11){
        x.Set(n00, n10);
        y.Set(n01, n11);
    }
    inline void mat22::Set(const Vec2& x, const Vec2& y){
        this->x = x;
        this->y = y;
    }
    inline void mat22::Set(const mat22& m){
        x.Set(m.x);
        y.Set(m.y);
    }
    inline Vec2 mat22::Solve(const Vec2 &a) const
    {
        float32_t d = det();
        if(d != 0.0f) d = 1.0f/d;
        return Vec2(d*(y.y*a.x-y.x*a.y), d*(x.y*a.x-x.x*a.y));
    }
    inline void mat22::SetRotation(const Vec2 &q)
    {
        x = q;
        y = q.Skew();
    }
    inline mat22 mat22::GetInv() const
    {
        float32_t d = det();
        if(d != 0.0f) d = 1.0f/d;
        return mat22(d*y.y, -d*y.x, -d*x.y, d*x.x);
    }
    inline mat22 mat22::operator * (const mat22 &a) const
    {
        return mat22(x.x*a.x.x + y.x*a.x.y, x.x*a.y.x + y.x*a.y.y, x.y*a.x.x + y.y*a.x.y, x.y*a.y.x + y.y*a.y.y);
    }
    inline float32_t mat22::det() const
    {
        return x.x*y.y - x.y*y.x;
    }
    inline void mat22::SetIdentity()
    {
        x.Set(1.0f, 0.0f);
        y.Set(0.0f, 1.0f);
    }
    AABB::AABB(const Vec2& lower, const Vec2& upper){
        lowerBound = lower;
        upperBound = upper;
    }
    void AABB::Combine(const AABB& a, const AABB& b)
    {
        lowerBound = Vec2(min(a.lowerBound.x, b.lowerBound.x), min(a.lowerBound.y, b.lowerBound.y));
        upperBound = Vec2(min(a.upperBound.x, b.upperBound.x), min(a.upperBound.y, b.upperBound.y));
    }
    bool AABB::In(const AABB& a) const
    {
        return lowerBound.x>=a.lowerBound.x && lowerBound.y>=a.lowerBound.y && upperBound.x<=a.upperBound.x && upperBound.y<=a.upperBound.y;
    }
    inline bool AABB::Contains(const AABB& a) const
    {
        return a.In(*this);
    }
    inline Vec2 AABB::GetCenter() const
    {
        return 0.5f * (lowerBound + upperBound);
    }
    float32_t AABB::GetArea() const
    {
        float32_t wx = upperBound.x - lowerBound.x;
        float32_t wy = upperBound.y - lowerBound.y;
        return wx * wy;
    }
    inline Vec2 AABB::GetExtents() const
    {
        return upperBound-lowerBound;
    }
    float32_t AABB::GetPerimeter() const
    {
        float32_t wx = upperBound.x - lowerBound.x;
        float32_t wy = upperBound.y - lowerBound.y;
        return 2.0f * (wx + wy);
    }
    bool AABB::vsAABB(const AABB& a) const
    {
        return lowerBound.x<=a.upperBound.x && upperBound.x>=a.lowerBound.x && lowerBound.y<=a.upperBound.y && upperBound.y>=a.lowerBound.y;
    }
    bool AABB::vsPoint(const Vec2& a) const
    {
        return a.x>=lowerBound.x && a.x<=upperBound.x && a.y>=lowerBound.y && a.y<=upperBound.y;
    }
}
