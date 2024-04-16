#ifndef MDP_PIXEL_H
#define MDP_PIXEL_H

#include <cstdint>
#include <array>

enum Channel
{
	RED = 0,
	GREEN = 1,
	BLUE = 2,
};

class Pixel {

	std::array<uint8_t, 3> m_data;

public:

	Pixel() : m_data{} {}
	Pixel(uint8_t r, uint8_t g, uint8_t b) : m_data{ r, g, b } {}
	Pixel(const std::array<uint8_t, 3>& data) : m_data(data) {};
	
	uint8_t& operator[] (Channel ch)
	{
		return m_data[static_cast<size_t>(ch)]; 
	}
	const uint8_t& operator[] (Channel ch) const
	{
		return m_data[static_cast<size_t>(ch)];
	}

	uint8_t& r() { return m_data[0]; }
	uint8_t& g() { return m_data[1]; }
	uint8_t& b() { return m_data[2]; }

	const uint8_t r() const { return m_data[0]; }
	const uint8_t g() const { return m_data[1]; }
	const uint8_t b() const { return m_data[2]; }

	bool operator== (const Pixel& other) const 
	{
		return std::equal(m_data.begin(), m_data.end(), other.m_data.begin());
	}

	static float distance2(const Pixel& lhs, const Pixel& rhs)
	{
		const float d0 = static_cast<float>(lhs[Channel::RED]) - static_cast<float>(rhs[Channel::RED]);
		const float d1 = static_cast<float>(lhs[Channel::GREEN]) - static_cast<float>(rhs[Channel::GREEN]);
		const float d2 = static_cast<float>(lhs[Channel::BLUE]) - static_cast<float>(rhs[Channel::BLUE]);
		return (d0 * d0) + (d1 * d1) + (d2 * d2);
	}

};

#endif // MDP_PIXEL_H