#ifndef MDP_UTILS_H
#define MDP_UTILS_H

#include <string>
#include <vector>
#include <chrono>
#include "image3b.h"
#include "cimg/CImg.h"

Image3b load_image3b(const std::string& filepath);
cimg_library::CImg<uint8_t> convert_to_cimg(const Image3b& img);
void show_images(std::vector<std::reference_wrapper<Image3b>> images);
std::chrono::high_resolution_clock::time_point tic();
long long toc(std::chrono::high_resolution_clock::time_point t0, std::string_view desc = "elapsed");


#endif // MDP_UTILS_H