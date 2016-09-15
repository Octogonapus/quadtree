#pragma once

#include <D:\Documents\C++_Programs\eigen\Eigen\Dense>

class IntersectData
{
public:
	IntersectData(const bool doesIntersect, const Eigen::Vector2f& direction) :
		m_doesIntersect(doesIntersect),
		m_direction(direction) {}

	inline bool GetDoesIntersect() const { return m_doesIntersect; }
	inline float GetDistance() const { return m_direction.norm(); }
	inline const Eigen::Vector2f& GetDirection() const { return m_direction; }
protected:
private:
	const bool m_doesIntersect;
	const Eigen::Vector2f m_direction;
};