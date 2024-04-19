#include <string>
#include <iostream>
#include "image3b.h"
#include "utils.h"

using palette_t = std::vector<Pixel>;

uint8_t to_uint8(uint32_t v) 
{
    return static_cast<uint8_t>(std::clamp(v, 0U, 255U));
};

struct RangeInfo
{
    uint8_t max_range = 0;
    Channel max_channel = Channel::RED;
};

struct Box
{
    std::vector<Pixel> m_pixels;
    Box(const std::vector<Pixel>& pixels) : m_pixels(pixels) 
    {
        m_info = get_range_info(m_pixels);
    };

    uint8_t max_range() const { return m_info.max_range; }

    // Split pixels according to median value on the selected channel
    std::tuple<Box, Box> split_on_median()
    {
        //------
        // TODO
        //------

        // 1. Find median position
        // 2. Get left portion
        Box left({});
        // 3. Get right portion
        Box right({});

        return { left, right };
    }

    // Get the mean pixel value
    Pixel mean_pixel() const
    {
        //------
        // TODO
        //------

        // Compute the mean value for all pixels
        const uint8_t r = to_uint8(0);
        const uint8_t g = to_uint8(0);
        const uint8_t b = to_uint8(0);
        return Pixel(r, g, b);
    }


private:
    
    RangeInfo m_info;

    // Get the channel with the highest range, and the range value
    static RangeInfo get_range_info(const std::vector<Pixel>& pixels)
    {
        //------
        // TODO
        //------

        // 1. Get min and max values for each channel
        // 2. Compute the range for each channel
        // 2.1 Get the largest range value
        // 2.2 Get the largest range channel

        RangeInfo info;
        info.max_range = 0;
        info.max_channel = Channel::RED;

        return info;
    }
};

static std::vector<Box> split_space_in_boxes(const Image3b& src, size_t N)
{
    //------
    // TODO
    //------
    
    // 1. Init box with all pixels
    std::vector<Box> boxes = { Box(src.pixels()) };
    
    // 2. Loop until you find N boxes
    while (boxes.size() < N)
    {
        break; // remove me
        // 2.1 Find the box with the largest color range
        // 2.2 Split the range at median value        
        // 2.3 Remove this box from 'boxes'
        // 2.4 Add the two splitted boxes to 'boxes'
    }

    return boxes;
}



static palette_t get_palette(const Image3b& src, size_t N)
{
    palette_t palette;

    // 1. Divide the colorspace in boxes
    const std::vector<Box> boxes = split_space_in_boxes(src, N);

    // 2. Get the mean pixel value for each box
    palette.reserve(boxes.size());
    for (const auto& box : boxes)
    {
        palette.push_back(box.mean_pixel());
    }

    return palette;
}

static Pixel get_palette_color(const palette_t& palette, const Pixel& p)
{
    // Get the palette color for current pixel
    auto it = std::min_element(palette.begin(), palette.end(), [p](const Pixel& lhs, const Pixel& rhs) {
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
    const palette_t palette = get_palette(src, N);

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