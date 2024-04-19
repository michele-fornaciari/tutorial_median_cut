#include <string>
#include <iostream>
#include "image3b.h"
#include "utils.h"

using palette_t = std::vector<Pixel>;


uint8_t to_uint8(uint32_t v) 
{
    return static_cast<uint8_t>(std::clamp(v, 0U, 255U));
};

static palette_t get_palette_fake(const Image3b& src, size_t N)
{
    // Generate N random pixels
    std::srand(std::time(NULL));

    palette_t palette(N);
    for (auto& p : palette)
    {
        p[Channel::RED] = rand() % 255;
        p[Channel::GREEN] = rand() % 255;
        p[Channel::BLUE] = rand() % 255;
    }
    return palette;
}

static Pixel get_palette_color(const palette_t& palette, const Pixel& p)
{
    // Get the palette color for current pixel
    auto it = std::min_element(palette.begin(), palette.end(), [p](const Pixel& lhs, const Pixel& rhs) 
    {
        // Compare according to distance with current pixel
        return Pixel::distance2(p, lhs) < Pixel::distance2(p, rhs);
    });
    return *it;
}

static Image3b apply_palette(const Image3b& src, const palette_t& palette)
{
    // For each pixel, get the corresponding palette color
    Image3b dst(src.width(), src.height());

    if (!palette.empty())
    {
        // 1. For each pixel
        for (int r = 0; r < src.height(); ++r)
        {
            for (int c = 0; c < src.width(); ++c)
            {
                // 2. Assign palette color
                dst(r, c) = get_palette_color(palette, src(r, c));
            }
        }
    }
    return dst;
}

// Median Cut
// https://indiegamedev.net/2020/01/17/median-cut-with-floyd-steinberg-dithering-in-c/
static Image3b median_cut(const Image3b& src, size_t N)
{
    // 1. Get palette with N colors
    const palette_t palette = get_palette_fake(src, N);

    // 2. Apply palette to input image
    const Image3b dst = apply_palette(src, palette);
    return dst;
}

int main(int argc, char** argv) 
{
    // Hard coded input data
    const std::string filepath = "C:/projects/corso_mdp/_dvc_code/tutorial_median_cut/data/parrot_01.jpg";
    const size_t N = 10;

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