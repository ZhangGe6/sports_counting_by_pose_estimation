//
// Created by ZhangGe on 2022/10/1.
//

#include "jitterfilter.h"

LowPassFilter::LowPassFilter() {
    prev_x = 0;
}

float LowPassFilter::filter(float x, float alpha) {
    float filtered_x = alpha * x + (1 - alpha) * prev_x;
    prev_x = filtered_x;
    return filtered_x;
}

LowPassFilterJoints::LowPassFilterJoints() {
    const int num_joints = 17;
    for (int i = 0; i < num_joints; ++i) {
        LowPassFilter filter_y, filter_x;
        filters.push_back({filter_y, filter_x});
    }
}

float get_alpha(float rate=30, float cutoff=1) {
    float tau = 1 / (2 * 3.1415926 * cutoff);
    float te = 1 / rate;
    return te / (te + tau);
}

//OneEuroFilter::OneEuroFilter(float freq_, float min_cutoff_, float beta_, float d_cutoff_) : x_filter(), dx_filter()
OneEuroFilter::OneEuroFilter() : x_filter(), dx_filter()
{
    freq = 7;
    min_cutoff = 1;
    beta = 0.05;
    d_cutoff = 1;
    prev_x = 0;
}

float OneEuroFilter::filter(float x) {
    dx = (x - prev_x) * freq;
    float dx_smoothed = dx_filter.filter(dx, get_alpha(freq, d_cutoff));
    float cutoff = min_cutoff + beta * abs(dx_smoothed);
    float x_filtered = x_filter.filter(x, get_alpha(freq, cutoff));
    prev_x = x;

    return x_filtered;
}

OneEuroFilterJoints::OneEuroFilterJoints() {
    const int num_joints = 17;
    for (int i = 0; i < num_joints; ++i) {
        filters.push_back({OneEuroFilter(), OneEuroFilter()});
    }
};

//OneEuroFilterJoints::OneEuroFilterJoints() : filters(17, {OneEuroFilter(), OneEuroFilter()})
//{
//}

//static float smoothing_factor(float t_e, float cutoff) {
//    float r = 2 * 3.1415 * cutoff * t_e;
//    return r / (r + 1);
//}
//
//static float exponential_smoothing(float alpha, float x, float prev_x) {
//    return alpha * x + (1 - alpha) * prev_x;
//}
//
////OneEuroFilter::OneEuroFilter(clock_t t, float min_cutoff_, float beta_, float d_cutoff_) {
////    min_cutoff = min_cutoff_;
////    beta = beta_;
////    d_cutoff = d_cutoff_;
////
////    // initialize `prev` data
////    prev_t = t;
////    prev_x = 0;
////    prev_dot_hat_x = 0;
////}
//
//OneEuroFilter::OneEuroFilter() {
//    min_cutoff = 0.004;
//    beta = 0.05;
//    d_cutoff = 1;
//
//    // initialize `prev` data
//    prev_t = clock();
//    prev_x = 0;
//    prev_dot_hat_x = 0;
//}
//
//float OneEuroFilter::filter(clock_t t, float x) {
//    float t_e = (double)(t - prev_t) / CLOCKS_PER_SEC;
//
//    float alpha_d = smoothing_factor(t_e, d_cutoff);
//    float dot_x = (x - prev_x) / t_e;
//    float dot_hat_x = exponential_smoothing(alpha_d, dot_x, prev_dot_hat_x);
//
//    float cutoff = min_cutoff + beta * abs(dot_hat_x);
//    float alpha = smoothing_factor(t_e, cutoff);
//    float x_hat = exponential_smoothing(alpha, x, prev_x);
//
//    prev_x = x;
//    prev_dot_hat_x = dot_hat_x;
//    prev_t = t;
//
//    return x_hat;
//}
//
//OneEuroFilterJoints::OneEuroFilterJoints() {
//    const int num_joints = 17;
//    for (int i = 0; i < num_joints; ++i) {
//        OneEuroFilter filter_y, filter_x;
//        filters.push_back({filter_y, filter_x});
//    }
//}