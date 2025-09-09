// Copyright 2025 Justin Nacu

#include "image_loader.h"

bool LoadTextureFromCVMat(const cv::Mat& mat, GLuint* out_texture,
                          int* out_width, int* out_height)
{
    if (mat.empty())
        return false;

    cv::Mat image;
    if (mat.channels() == 3)
        cv::cvtColor(mat, image, cv::COLOR_BGR2RGBA);
    else if (mat.channels() == 4)
        cv::cvtColor(mat, image, cv::COLOR_BGRA2RGBA);
    else if (mat.channels() == 1)
        cv::cvtColor(mat, image, cv::COLOR_GRAY2RGBA);
    else
        return false;


    *out_width = image.cols;
    *out_height = image.rows;

    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload to GPU
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image.data);

    *out_texture = image_texture;
    return true;
}

/* EXAMPLE USAGE OF LoadTextureFromFile WITH IMGUI
    if (uiState.imageLoader.my_image_texture == 0)
    {
        if (!LoadTextureFromFile("Acadian_Flycatcher.jpg",
                                 &uiState.imageLoader.my_image_texture,
                                 &uiState.imageLoader.my_image_width,
                                 &uiState.imageLoader.my_image_height))
        {
            std::cerr << "Failed to load texture!" << std::endl;
        }
    }

    ImGui::Begin("Image Example");
    if (uiState.imageLoader.my_image_texture)
    {
        ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(
                         uiState.imageLoader.my_image_texture)),
                     ImVec2(uiState.imageLoader.my_image_width,
                            uiState.imageLoader.my_image_height));
    }
    ImGui::End();
*/
bool LoadTextureFromFile(const char* file_name, GLuint* out_texture,
                         int* out_width, int* out_height)
{
    cv::Mat mat = cv::imread(file_name, cv::IMREAD_UNCHANGED);
    if (mat.empty())
        return false;

    return LoadTextureFromCVMat(mat, out_texture, out_width, out_height);
}
