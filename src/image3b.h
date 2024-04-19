#ifndef MDP_IMAGE3B_H
#define MDP_IMAGE3B_H

#include "pixel.h"
#include <vector>

class Image3b {
	uint32_t m_w, m_h;
	std::vector<Pixel> m_data;

public:
	Image3b();
	Image3b(uint32_t w, uint32_t h);
	Image3b(uint32_t w, uint32_t h, const uint8_t* arr);
	
	uint32_t width() const;
	uint32_t height() const;
	uint32_t channels() const;
	uint32_t size() const;
	bool empty() const;

	std::vector<Pixel>& pixels();
	const std::vector<Pixel>& pixels() const;

	Pixel& operator() (uint32_t r, uint32_t c);
	const Pixel& operator() (uint32_t r, uint32_t c) const;

	uint8_t* data();
	const uint8_t* data() const;
};

#endif // MDP_IMAGE3B_H