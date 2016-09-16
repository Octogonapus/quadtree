#pragma once

#include <vector>
#include "point.h"
#include "aabb.h"

class Quadtree
{
public:
	Quadtree(const AABB& aabb);
	~Quadtree();

	bool insert(Point p);
	void subdivide();
	std::vector<Point> queryRange(AABB range);
private:
	Quadtree* m_nw;
	Quadtree* m_ne;
	Quadtree* m_sw;
	Quadtree* m_se;

	AABB m_boundary;

	static const int m_capacity = 4;
	std::vector<Point> m_objects;
};