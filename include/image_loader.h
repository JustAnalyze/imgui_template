// Copyright 2025 Justin Nacu
#ifndef IMNOTATOR_IMAGE_LOADER_H
#define IMNOTATOR_IMAGE_LOADER_H

using GLuint = unsigned int;

// Forward declaration for opencv Mat
namespace cv
{
class Mat;
}

// Load image with OpenCV and upload as OpenGL texture
bool LoadTexdureFromCVMat(const cv::Mat& mat, GLuint* out_texture,
                          int* out_width, int* out_height);

// Convenience wrapper: load from file using OpenCV imread
bool LoadTextureFromFile(const char* file_name, GLuint* out_texture,
                         int* out_width, int* out_height);

#endif  // IMAGE_LOADER_H
