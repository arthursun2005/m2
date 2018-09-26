//
//  Color.hpp
//  m2
//
//  Created by Arthur Sun on 8/31/18.
//  Copyright © 2018 Arthur Sun. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

typedef float float32_t;
typedef double float64_t;
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

enum ColorMode
{
    RRGGBBAA, AARRGGBB
};

namespace m2 {
    struct Color
    {
        float32_t r;
        float32_t g;
        float32_t b;
        float32_t a;
        Color(){
            Set();
        }
        Color(float32_t r, float32_t g, float32_t b, float32_t a){
            Set(r, g, b, a);
        }
        Color(float32_t r, float32_t g, float32_t b){
            Set(r, g, b);
        }
        Color(float32_t c, float32_t a){
            Set(c, a);
        }
        Color(float32_t c){
            Set(c);
        }
        void Set(float32_t r, float32_t g, float32_t b, float32_t a);
        void Set(float32_t r, float32_t g, float32_t b);
        void Set(float32_t c, float32_t a);
        void Set(float32_t c);
        void Set(const Color& c);
        void Set(uint32_t hex, ColorMode mode);
        void Set(){
            this->r = 0.0f;
            this->g = 0.0f;
            this->b = 0.0f;
            this->a = 1.0f;
        }
        void Blend(const Color* const c);
        Color Lerp(const Color* const c, const float32_t& u) const
        {
            return Color(r+(c->r-r)*u, g+(c->g-g)*u, b+(c->b-b)*u, a+(c->a-a)*u);
        }
        uint32_t getHex(ColorMode mode) const;
    };
    void MixColors(Color* const a, Color* const b, float32_t u);
}


#endif /* Color_hpp */
