/* Copyright 2021 iwatake2222

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
/*** Include ***/
/* for general */
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <memory>

/* for OpenCV */
#include <opencv2/opencv.hpp>

/* for My modules */
#include "common_helper.h"
#include "common_helper_cv.h"
#include "pose_engine.h"
#include "image_processor.h"

/*** Macro ***/
#define TAG "ImageProcessor"
#define PRINT(...)   COMMON_HELPER_PRINT(TAG, __VA_ARGS__)
#define PRINT_E(...) COMMON_HELPER_PRINT_E(TAG, __VA_ARGS__)

/*** Global variable ***/
std::unique_ptr<PoseEngine> s_engine;

/*** Function ***/
static void DrawFps(cv::Mat& mat, double time_inference, cv::Point pos, double font_scale, int32_t thickness, cv::Scalar color_front, cv::Scalar color_back, bool is_text_on_rect = true)
{
    char text[64];
    static auto time_previous = std::chrono::steady_clock::now();
    auto time_now = std::chrono::steady_clock::now();
    double fps = 1e9 / (time_now - time_previous).count();
    time_previous = time_now;
    snprintf(text, sizeof(text), "FPS: %.1f, Inference: %.1f [ms]", fps, time_inference);
    CommonHelper::DrawText(mat, text, cv::Point(0, 0), 0.5, 2, CommonHelper::CreateCvColor(0, 0, 0), CommonHelper::CreateCvColor(180, 180, 180), true);
}


int32_t ImageProcessor::Initialize(const ImageProcessor::InputParam& input_param)
{
    /*
    if (s_engine) {
        PRINT_E("Already initialized\n");
        return -1;
    }

    */
    
    s_engine.reset(new PoseEngine());
    if (s_engine->Initialize(input_param.work_dir, input_param.num_threads) != PoseEngine::kRetOk) {
        s_engine->Finalize();
        s_engine.reset();
        return -1;
    }
    return 0;
}

int32_t ImageProcessor::Finalize(void)
{
    if (!s_engine) {
        PRINT_E("Not initialized\n");
        return -1;
    }

    if (s_engine->Finalize() != PoseEngine::kRetOk) {
        return -1;
    }

    return 0;
}


int32_t ImageProcessor::Command(int32_t cmd)
{
    if (!s_engine) {
        PRINT_E("Not initialized\n");
        return -1;
    }

    switch (cmd) {
    case 0:
    default:
        PRINT_E("command(%d) is not supported\n", cmd);
        return -1;
    }
}

static const std::vector<std::pair<int32_t, int32_t>> kJointLineList {
    /* face */
    {0, 2},
    {2, 4},
    {0, 1},
    {1, 3},

    /* body */
    {6, 5},
    {5, 11},
    {11, 12},
    {12, 6},
    /* arm */
    {6, 8},
    {8, 10},
    {5, 7},
    {7, 9},
    /* leg */
    {12, 14},
    {14, 16},
    {11, 13},
    {13, 15},
};

static constexpr float kThresholdScoreKeyPoint = 0.2f;

int32_t ImageProcessor::Process(cv::Mat& mat, ImageProcessor::Result& result)
{

    if (!s_engine) {
        PRINT_E("Not initialized\n");
        return -1;
    }

    
    PoseEngine::Result pose_result;
    if (s_engine->Process(mat, pose_result) != PoseEngine::kRetOk) {
        return -1;
    }

    /* Display target area  */
    cv::rectangle(mat, cv::Rect(pose_result.crop.x, pose_result.crop.y, pose_result.crop.w, pose_result.crop.h), CommonHelper::CreateCvColor(0, 0, 0), 2);

    /* Display detection result and keypoint */
    for (size_t i = 0; i < 1; i++) {

        /* Display joint lines */
        const auto& keypoint = pose_result.keypoint_list[i];
        const auto& keypoint_score = pose_result.keypoint_score_list[i];
        for (const auto& jointLine : kJointLineList) {
            if (keypoint_score[jointLine.first] >= kThresholdScoreKeyPoint && keypoint_score[jointLine.second] >= kThresholdScoreKeyPoint) {
                int32_t x0 = keypoint[jointLine.first].first;
                int32_t y0 = keypoint[jointLine.first].second;
                int32_t x1 = keypoint[jointLine.second].first;
                int32_t y1 = keypoint[jointLine.second].second;
                cv::line(mat, cv::Point(x0, y0), cv::Point(x1, y1), CommonHelper::CreateCvColor(200, 200, 200), 2);
            }
        }

        /* Display joints */
        for (size_t j = 0; j < keypoint.size(); j++) {
            if (keypoint_score[j] >= kThresholdScoreKeyPoint) {
                const auto& p = keypoint[j];
                cv::circle(mat, cv::Point(p.first, p.second), 2, CommonHelper::CreateCvColor(0, 255, 0));
            }
        }
    }


    DrawFps(mat, pose_result.time_inference, cv::Point(0, 0), 0.5, 2, CommonHelper::CreateCvColor(0, 0, 0), CommonHelper::CreateCvColor(180, 180, 180), true);

    result.time_pre_process = pose_result.time_pre_process;
    result.time_inference = pose_result.time_inference;
    result.time_post_process = pose_result.time_post_process;

    return 0;
}
