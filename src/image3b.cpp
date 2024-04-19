#include "image3b.h"

Image3b::Image3b() : m_w(0), m_h(0) {}
Image3b::Image3b(uint32_t w, uint32_t h) : m_w(w), m_h(h), m_data(w* h) {}
Image3b::Image3b(uint32_t w, uint32_t h, const uint8_t* arr) : m_w(w), m_h(h), m_data(((Pixel*)arr), ((Pixel*)arr) + (w * h)) {};

uint32_t Image3b::width() const { return m_w; }
uint32_t Image3b::height() const { return m_h; }
uint32_t Image3b::channels() const { return 3; }
uint32_t Image3b::size() const { return m_w * m_h; }
bool Image3b::empty() const { return m_data.empty(); }

std::vector<Pixel>& Image3b::pixels() { return m_data; }
const std::vector<Pixel>& Image3b::pixels() const { return m_data; }

Pixel& Image3b::operator() (uint32_t r, uint32_t c) { return m_data[r * m_w + c]; }
const Pixel& Image3b::operator() (uint32_t r, uint32_t c) const { return m_data[r * m_w + c]; }

uint8_t* Image3b::data() { return reinterpret_cast<uint8_t*>(m_data.data()); }
const uint8_t* Image3b::data() const { return reinterpret_cast<const uint8_t*>(m_data.data()); }