#pragma once

class Point
{
public:
	Point(const float x, const float y):
		m_x(x),
		m_y(y) {}

	inline const float getX() const { return m_x; }
	inline const float getY() const { return m_y; }
private:
	float m_x, m_y;
};