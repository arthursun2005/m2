//
//  Color.cpp
//  m2
//
//  Created by Arthur Sun on 9/1/18.
//  Copyright © 2018 Arthur Sun. All rights reserved.
//

#include "Color.hpp"

namespace m2 {
    void Color::Set(float32_t r, float32_t g, float32_t b, float32_t a){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    void Color::Set(float32_t r, float32_t g, float32_t b){
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 1.0f;
    }
    void Color::Set(float32_t c, float32_t a){
        this->r = c;
        this->g = c;
        this->b = c;
        this->a = a;
    }
    void Color::Set(float32_t c){
        this->r = c;
        this->g = c;
        this->b = c;
        this->a = 1.0f;
    }
    void Color::Set(uint32_t hex, ColorMode mode){
        switch (mode) {
            case RRGGBBAA:
                r = (mode >> 24) & 0xff;
                g = (mode >> 16) & 0xff;
                b = (mode >> 8) & 0xff;
                a = mode & 0xff;
                break;
            case AARRGGBB:
                a = (mode >> 24) & 0xff;
                r = (mode >> 16) & 0xff;
                g = (mode >> 8) & 0xff;
                b = mode & 0xff;
                break;
            default:
                break;
        }
    }
    void Color::Add(const Color* const c)
    {
        float32_t a0 = 1.0f-c->a;
        r = a0*r + c->r*c->a;
        g = a0*g + c->g*c->a;
        b = a0*b + c->b*c->a;
        a = a0*a + c->a*c->a;
    }
    void Color::Lerp(const Color* const c, float32_t u)
    {
        r += (c->r-r) * u;
        g += (c->g-g) * u;
        b += (c->b-b) * u;
        a += (c->a-a) * u;
    }
    uint32_t Color::getHex(ColorMode mode) const
    {
        uint8_t r0 = (uint8_t)(r*255.0f);
        uint8_t g0 = (uint8_t)(g*255.0f);
        uint8_t b0 = (uint8_t)(b*255.0f);
        uint8_t a0 = (uint8_t)(a*255.0f);
        switch(mode)
        {
            case RRGGBBAA:
                return (r0 << 24) | (g0 << 16) | (b0 << 8) | a0;
            case AARRGGBB:
                return (a0 << 24) | (r0 << 16) | (g0 << 8) | b0;
            default: break;
        }
    }
    void MixColors(Color* const a, Color* const b, float32_t u){
        Color t = *a;
        a->Lerp(b, u);
        b->Lerp(&t, u);
    }
}
