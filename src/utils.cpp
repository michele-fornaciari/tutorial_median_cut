#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "utils.h"
#include <format>
#include <iostream>

using namespace cimg_library;

// STB / CImg
// https://stackoverflow.com/a/66331370/5008845

Image3b load_image3b(const std::string& filepath)
{
    int w, h, comp;
    uint8_t* data = stbi_load(filepath.c_str(), &w, &h, &comp, 0);
    if (!data)
    {
        return Image3b();
    }
    Image3b img(w, h, data);
    stbi_image_free(data);
    return img;
}

CImg<uint8_t> convert_to_cimg(const Image3b& img)
{
    CImg<uint8_t> image(img.data(), img.channels(), img.width(), img.height(), 1, false);
    image.permute_axes("yzcx");
    return image;
}

void show_images(std::vector< std::reference_wrapper<Image3b>> images)
{
    assert(images.size() <= 10);

    std::vector<CImgDisplay> displays;
    displays.reserve(images.size());

    for (size_t i = 0; i < images.size(); ++i) {
        displays.emplace_back(convert_to_cimg(images[i]), std::format("Image {}", i).c_str());
    }
    
    while (true)
    {
        bool do_close = false;
        for (const auto& disp : displays)
        {
            do_close = do_close || (disp.is_closed() || disp.is_keyESC() || disp.is_keyQ());
        }

        if (do_close) {
            break;
        }
        CImgDisplay::wait_all();
    }
}

std::chrono::high_resolution_clock::time_point tic()
{
    return std::chrono::high_resolution_clock::now();
}

long long toc(std::chrono::high_resolution_clock::time_point t0, std::string_view desc)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << desc << ": " << ms << "ms" << std::endl;
    return ms;
}