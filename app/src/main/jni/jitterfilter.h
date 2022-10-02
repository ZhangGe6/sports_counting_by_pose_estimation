//
// Created by ZhangGe on 2022/10/1.
// reference: // https://programtalk.com/vs4/python/HectorPulido/Vtuber-Framework-Unity-and-Python/source/TrackingBackend/pose_models/one_euro_filter.py/
//
#include <chrono>
#include <math.h>
#include <vector>

class LowPassFilter {
private:
    float prev_x;
public:
    LowPassFilter();
    float filter(float x, float alpha=0.8);
};

class LowPassFilterJoints {
public:
    std::vector<std::pair<LowPassFilter, LowPassFilter>> filters;
    LowPassFilterJoints();
};


class OneEuroFilter {
private:
    float freq;
    float min_cutoff;
    float beta;
    float d_cutoff;

    LowPassFilter x_filter, dx_filter;
    float prev_x;
    float dx;

public:
    OneEuroFilter();
    float filter(float x);
};

class OneEuroFilterJoints {
public:
    std::vector<std::pair<OneEuroFilter, OneEuroFilter>> filters;
    OneEuroFilterJoints();
};
