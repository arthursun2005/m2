//
//  Math.cpp
//  m2
//
//  Created by Arthur Sun on 8/30/18.
//  Copyright © 2018 Arthur Sun. All rights reserved.
//

#include "Math.hpp"

namespace m2 {
    void Vec2::Set(float32_t x, float32_t y){
        this->x = x;
        this->y = y;
    }
    void Vec2::Set(const Vec2& v){
        x = v.x;
        y = v.y;
    }
    void Vec2::SetAngle(float32_t a)
    {
        x = cosf(a);
        y = sinf(a);
    }
    float32_t Vec2::GetAngle() const
    {
        return atan2f(y, x);
    }
    void Vec2::Rotate(const Vec2& v)
    {
        float32_t _x = x;
        x = x*v.x - y*v.y;
        y = _x*v.y + y*v.x;
    }
    float32_t Vec2::MagSq() const
    {
        return x * x + y * y;
    }
    float32_t Vec2::Mag() const
    {
        return sqrtf(x * x + y * y);
    }
    void Vec2::Lerp(const Vec2 &v, float32_t u)
    {
        x += (v.x-x)*u;
        y += (v.y-y)*u;
    }
    float32_t Vec2::Normalize()
    {
        float32_t m = Mag();
        if(m < FLT_EPSILON) m = FLT_EPSILON;
        x *= 1.0f/m;
        y *= 1.0f/m;
        return m;
    }
    void Vec2::Normalize(float32_t& m)
    {
        if(m < FLT_EPSILON) m = FLT_EPSILON;
        x *= 1.0f/m;
        y *= 1.0f/m;
    }
    void Vec2::operator *= (float32_t a){
        x *= a;
        y *= a;
    }
    void Vec2::operator += (const Vec2& a){
        x += a.x;
        y += a.y;
    }
    void Vec2::operator -= (const Vec2& a){
        x -= a.x;
        y -= a.y;
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
    
    void mat22::Set(float32_t n00, float32_t n01, float32_t n10, float32_t n11){
        x.Set(n00, n10);
        y.Set(n01, n11);
    }
    void mat22::Set(const Vec2& x, const Vec2& y){
        this->x = x;
        this->y = y;
    }
    void mat22::Set(const mat22& m){
        x.Set(m.x);
        y.Set(m.y);
    }
    Vec2 mat22::Solve(const Vec2& a) const
    {
        float32_t d = det();
        if(d != 0.0f) d = 1.0f/d;
        return Vec2(d*(y.y*a.x-y.x*a.y), d*(x.y*a.x-x.x*a.y));
    }
    void mat22::SetRotation(const Vec2& q)
    {
        x = q;
        y = q.Skew();
    }
    bool mat22::GetInv(mat22& m) const
    {
        float32_t d = det();
        if(d != 0.0f){
            m.Set(d*y.y, -d*y.x, -d*x.y, d*x.x);return true;
        }else{
            return false;
        }
    }
    void mat22::SetIdentity()
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
    bool AABB::Contains(const AABB& a) const
    {
        return a.In(*this);
    }
    Vec2 AABB::GetCenter() const
    {
        return 0.5f * (lowerBound + upperBound);
    }
    float32_t AABB::GetArea() const
    {
        float32_t wx = upperBound.x - lowerBound.x;
        float32_t wy = upperBound.y - lowerBound.y;
        return wx * wy;
    }
    Vec2 AABB::GetExtents() const
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
