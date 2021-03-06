//
//  Timer.hpp
//  m2
//
//  Created by Arthur Sun on 8/26/18.
//  Copyright © 2018 Arthur Sun. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>
#include <vector>
#include <string>
#include <unordered_map>

namespace m2 {
    template <class _clock_, class _time_point_>
    struct _timer_
    {
    protected:
        _clock_ clock;
        _time_point_ last;
        _time_point_ start;
        std::unordered_map<std::string, float> times;
        std::unordered_map<std::string, float> progress;
    public:
        double delta = 0.0f;
        _timer_(){
            Reset();
        }
        /// @return the time elapsed between the last update
        /// @brief this should be called once every frame
        double update(){
            _time_point_ now = clock.now();
            std::chrono::duration<float> elapsed = now-last;
            for(auto& p : progress){
                p.second += elapsed.count();
            }
            last = now;
            delta = elapsed.count();
            return delta;
        }
        void Reset(){
            start = clock.now();
            last = start;
        }
        /// @return the time between now and the start
        float GetTime() const
        {
            _time_point_ now = clock.now();
            std::chrono::duration<float> elapsed = now-start;
            return elapsed.count();
        }
        /// @return check if a timer is up
        bool Finished(const std::string& s){
            if(progress[s] >= times[s]){
                progress[s] = 0.0f;
                return true;
            }else{
                return false;
            }
        }
        /// @brief adds a new timer to the map
        void Set(const std::string& s, float v){
            times[s] = v;
            progress[s] = 0.0f;
        }
        double Get(const std::string& s){
            return progress[s]/times[s];
        }
        void Remove(const std::string& s)
        {
            times.erase(s);
            progress.erase(s);
        }
        void Clear(){
            times.clear();
            progress.clear();
        }
        inline double operator [] (const std::string& s) const
        {
            return times[s];
        }
        inline double operator () (const std::string& s) const
        {
            return progress[s];
        }
        inline double& operator [] (const std::string& s)
        {
            return times[s];
        }
        inline double& operator () (const std::string& s)
        {
            return progress[s];
        }
    };
    
    typedef _timer_<std::chrono::high_resolution_clock, std::chrono::high_resolution_clock::time_point> h_timer;
    
    typedef _timer_<std::chrono::system_clock, std::chrono::system_clock::time_point> s_timer;
}

#endif /* Timer_hpp */
