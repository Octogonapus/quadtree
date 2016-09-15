#pragma once

#include <D:\Documents\C++_Programs\eigen\Eigen\Dense>
#include "intersectData.h"
#include "point.h"

class AABB
{
public:
	AABB(const Eigen::Vector2f& centerPos, const Eigen::Vector2f& dimensions):
		m_centerPos(centerPos),
		m_dimensions(dimensions) {}

	inline const bool intersectWithPoint(const Point& other) const
	{
		return !(getMaxExtents().x < other.getX() ||
				 getMaxExtents().y < other.getY() ||
				 getMinExtents().x > other.getX() ||
				 getMinExtents().y > other.getY());
	}

	//Get coordinates of bottom right point
	inline const Eigen::Vector2f& getMinExtents() const { return m_centerPos - (m_dimensions / 2); }

	//Get coordinates of top left point
	inline const Eigen::Vector2f& getMaxExtents() const { return m_centerPos + (m_dimensions / 2); }

	inline const Eigen::Vector2f& getCenter() const { return m_centerPos; }
	inline void setCenter(const Eigen::Vector2f& centerPos) { m_centerPos = centerPos; }
private:
	Eigen::Vector2f m_centerPos, m_dimensions;
};