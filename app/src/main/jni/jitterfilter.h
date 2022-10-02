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
//    OneEuroFilter(float freq_=15, float min_cutoff_=1, float beta_=0.05, float d_cutoff_=1);
    OneEuroFilter();
    float filter(float x);
};

class OneEuroFilterJoints {
public:
    std::vector<std::pair<OneEuroFilter, OneEuroFilter>> filters;
    OneEuroFilterJoints();
};

//class OneEuroFilter {
//private:
//    float min_cutoff;
//    float beta;
//    float d_cutoff;
//    clock_t prev_t;
//    float prev_x;
//    float prev_dot_hat_x;
//
//public:
////    OneEuroFilter(clock_t t=clock(), float min_cutoff_=1.7, float beta_=0.3, float d_cutoff_=30);
////    OneEuroFilter(clock_t t=clock(), float min_cutoff_=0.00000004, float beta_=0.7, float d_cutoff_=1);
////    OneEuroFilter(clock_t t=clock(), float min_cutoff_=0.004, float beta_=0.05, float d_cutoff_=1);
//    OneEuroFilter();
//
//    float filter(clock_t t, float x);
//};
//
//class OneEuroFilterJoints {
//public:
//    std::vector<std::pair<OneEuroFilter, OneEuroFilter>> filters;
//    OneEuroFilterJoints();
//};