#include <string>
#include <iostream>
#include "image3b.h"
#include "utils.h"

#include "cli11/CLI11.hpp"

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
        // 1. Find median position
        const size_t half_pos = m_pixels.size() / 2;
        std::nth_element(m_pixels.begin(), std::next(m_pixels.begin(), half_pos), m_pixels.end(), [ch = m_info.max_channel](const Pixel& lhs, const Pixel& rhs) {
            return lhs[ch] < rhs[ch];
        });
        auto half_it = std::next(m_pixels.begin(), half_pos);
         
        // 2. Get left portion
        Box left(std::vector<Pixel>(m_pixels.begin(), half_it));

        // 3. Get right portion
        Box right(std::vector<Pixel>(half_it, m_pixels.end()));

        return { left, right };
    }

    // Get the mean pixel value
    Pixel mean_pixel() const
    {
        uint32_t R = 0;
        uint32_t G = 0;
        uint32_t B = 0;

        for (const auto& p : m_pixels)
        {
            R += p.r();
            G += p.g();
            B += p.b();
        }

        const size_t N_PIXELS = m_pixels.size();
        R = R / N_PIXELS;
        G = G / N_PIXELS;
        B = B / N_PIXELS;

        const uint8_t r = to_uint8(R);
        const uint8_t g = to_uint8(G);
        const uint8_t b = to_uint8(B);

        return Pixel(r, g, b);
    }


private:
    
    RangeInfo m_info;

    // Get the channel with the highest range, and the range value
    static RangeInfo get_range_info(const std::vector<Pixel>& pixels)
    {
        uint8_t min_r = 255;
        uint8_t max_r = 0;

        uint8_t min_g = 255;
        uint8_t max_g = 0;

        uint8_t min_b = 255;
        uint8_t max_b = 0;

        for (const auto& p : pixels)
        {
            min_r = std::min(min_r, p.r());
            max_r = std::max(max_r, p.r());

            min_g = std::min(min_g, p.g());
            max_g = std::max(max_g, p.g());

            min_b = std::min(min_b, p.b());
            max_b = std::max(max_b, p.b());
        }

        std::array<int, 3> ranges =
        {
            (max_r - min_r),
            (max_g - min_g),
            (max_b - min_b),
        };

        const auto it = std::max_element(ranges.begin(), ranges.end());

        RangeInfo info;
        info.max_range = to_uint8(*it);
        info.max_channel = Channel(std::distance(ranges.begin(), it));

        return info;
    }
};

static std::vector<Box> split_space_in_boxes(const Image3b& src, size_t N)
{
    
    // 1. Init box with all pixels
    std::vector<Box> boxes = { Box(src.pixels()) };
    
    // 2. Loop until you find N boxes
    while (boxes.size() < N)
    {
        // 2.1 Find the box with the largest color range
        auto largest_it = std::max_element(boxes.begin(), boxes.end(), [](const Box& lhs, const Box& rhs) {
            return lhs.max_range() < rhs.max_range();
        });

        // 2.2 Split the range at median value        
        auto [left, right] = largest_it->split_on_median();

        // 2.3 Remove this box from 'boxes'
        boxes.erase(largest_it);

        // 2.4 Add the two splitted boxes to 'boxes'
        boxes.push_back(left);
        boxes.push_back(right);
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
    const std::string default_filepath = "C:/projects/corso_mdp/_dvc_code/tutorial_median_cut/data/parrot_01.jpg";
    const size_t default_N = 10;

    std::string filepath = default_filepath;
    int N = default_N;

    CLI::App app("Median Cut");
    app.add_option("file, -f, --file", filepath, "filepath to image");
    app.add_option("n, -n", N, "median cut N");
    CLI11_PARSE(app, argc, argv);

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