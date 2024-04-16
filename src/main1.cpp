#include <string>
#include <iostream>
#include "image3b.h"
#include "utils.h"


static std::vector<Pixel> get_palette(const Image3b& src, size_t N)
{
    std::vector<Pixel> palette(N);
    return palette;
}

static Image3b apply_palette(const Image3b& src, const std::vector<Pixel>& palette)
{
    Image3b dst = src;
    return dst;
}

// Median Cut
// https://indiegamedev.net/2020/01/17/median-cut-with-floyd-steinberg-dithering-in-c/
static Image3b median_cut(const Image3b& src, size_t N)
{
    const std::vector<Pixel> palette = get_palette(src, N);
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

    // Show results
    show_images({ img });
    return 0;
}