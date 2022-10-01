// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef MOVENET_H
#define MOVENET_H

#include <opencv2/core/core.hpp>

#include <net.h>
struct keypoint
{
    float x;
    float y;
    float score;
};

class MoveNet
{
public:
    MoveNet();

    int load(const char* modeltype, int target_size, const float* mean_vals, const float* norm_vals, bool use_gpu = false, int sport_id=0);
    int load(AAssetManager* mgr, const char* modeltype, int target_size, const float* mean_vals, const float* norm_vals, bool use_gpu=false, int sport_id=0);

    void preprocess(cv::Mat &rgb, ncnn::Mat& in_processed, int& hpad, int& wpad, float& scale);
    void detect(cv::Mat &rgb, std::vector<keypoint> &points);
    void draw(cv::Mat& rgb, std::vector<keypoint> &points);
    void count(std::vector<keypoint>& points);

    int sport_kind;
    int count_number;

private:
    ncnn::Net poseNet;
    int num_joints;
    int feature_size;
    int target_size;
    float mean_vals[3];
    float norm_vals[3];
    bool count_lock;

    ncnn::UnlockedPoolAllocator blob_pool_allocator;
    ncnn::PoolAllocator workspace_pool_allocator;
};

#endif // MOVENET_H
