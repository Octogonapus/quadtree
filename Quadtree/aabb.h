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
		return !(getMaxExtents()[0] < other.getX() ||
				 getMaxExtents()[1] < other.getY() ||
				 getMinExtents()[0] > other.getX() ||
				 getMinExtents()[1] > other.getY());
	}

	inline const bool intersectWithAABB(const AABB& other) const
	{
		return !(getMaxExtents()[0] < other.getMinExtents()[0] ||
				 getMaxExtents()[1] < other.getMinExtents()[1] ||
				 getMinExtents()[0] > other.getMaxExtents()[0] ||
				 getMinExtents()[1] > other.getMaxExtents()[1]);
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