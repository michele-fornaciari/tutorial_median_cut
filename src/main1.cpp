#include <string>
#include <iostream>
#include "image3b.h"
#include "utils.h"


int main(int argc, char** argv) 
{
    // Hard coded input data
    const std::string filepath = "../data/parrot_01.jpg";
    std::cout << "image: " << filepath << std::endl;

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