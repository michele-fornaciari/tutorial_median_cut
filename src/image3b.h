#ifndef MDP_IMAGE3B_H
#define MDP_IMAGE3B_H

#include "pixel.h"
#include <vector>

class Image3b {
	uint32_t m_w, m_h;
	std::vector<Pixel> m_data;

public:
	Image3b() : m_w(0), m_h(0) {}
	Image3b(uint32_t w, uint32_t h) : m_w(w), m_h(h), m_data(w*h) {}
	Image3b(uint32_t w, uint32_t h, const uint8_t* arr) : m_w(w), m_h(h), m_data(((Pixel*)arr), ((Pixel*)arr) + (w*h)) {};
	
	uint32_t width() const { return m_w; }
	uint32_t height() const { return m_h; }
	uint32_t channels() const { return 3; }
	uint32_t size() const { return m_w * m_h; }
	bool empty() const { return m_data.empty(); }

	std::vector<Pixel>& pixels() { return m_data; }
	const std::vector<Pixel>& pixels() const { return m_data; }

	Pixel& operator() (uint32_t r, uint32_t c) { return m_data[r*m_w + c]; }
	const Pixel& operator() (uint32_t r, uint32_t c) const { return m_data[r*m_w + c]; }

	uint8_t* data() { return reinterpret_cast<uint8_t*>(m_data.data()); }
	const uint8_t* data() const { return reinterpret_cast<const uint8_t*>(m_data.data()); }
};

#endif // MDP_IMAGE3B_H