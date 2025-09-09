// Copyright 2025 Justin Nacu
#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <glad/glad.h>
#include <opencv2/opencv.hpp>

// Load image with OpenCV and upload as OpenGL texture
bool LoadTexdureFromCVMat(const cv::Mat& mat, GLuint* out_texture,
                          int* out_width, int* out_height);

// Convenience wrapper: load from file using OpenCV imread
bool LoadTextureFromFile(const char* file_name, GLuint* out_texture,
                         int* out_width, int* out_height);

#endif  // IMAGE_LOADER_H
