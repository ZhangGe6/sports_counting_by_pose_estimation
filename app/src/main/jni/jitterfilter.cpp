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
//    freq = 7;
    freq = 25;
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