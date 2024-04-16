#include <string>
#include <iostream>
#include "image3b.h"
#include "utils.h"

using palette_t = std::vector<Pixel>;


uint8_t to_uint8(uint32_t v) 
{
    return static_cast<uint8_t>(std::clamp(v, 0U, 255U));
};

static std::vector<Pixel> get_palette_fake(const Image3b& src, size_t N)
{
    // Generate N random pixels
    std::vector<Pixel> palette;
    return palette;
}

static Pixel get_palette_color(const palette_t& palette, const Pixel& p)
{
    // Get the nearest palette pixel value
    return p;
}

static Image3b apply_palette(const Image3b& src, const palette_t& palette)
{
    // For each pixel, get the corresponding palette color
    Image3b dst(src.width(), src.height());

    // 1. For each pixel
    // 2. Assign palette color

    return dst;
}

// Median Cut
// https://indiegamedev.net/2020/01/17/median-cut-with-floyd-steinberg-dithering-in-c/
static Image3b median_cut(const Image3b& src, size_t N)
{
    const std::vector<Pixel> palette = get_palette_fake(src, N);
    const Image3b dst = apply_palette(src, palette);
    return dst;
}

int main(int argc, char** argv) 
{
    // Hard coded input data
    const std::string filepath = "C:/projects/corso_mdp/_dvc_code/tutorial_median_cut/data/parrot_01.jpg";
    const int N = 10;

    std::cout << "image: " << filepath << std::endl;
    std::cout << "N: " << N << std::endl;

    // Load image
    Image3b img = load_image3b(filepath);
    if (img.empty()) {
        std::cerr << "Invalid image" << std::endl;
        return -1;
    }
    std::cout << "size: " << img.width() << "x" << img.height() << std::endl;

    Image3b quant = median_cut(img, N);

    // Show results
    show_images({ img, quant });
    return 0;
}