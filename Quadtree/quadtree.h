#pragma once

template <class T>
class Quadtree
{
public:
	Quadtree<T>();
	~Quadtree();

	bool insert(Point p);
	void subdivide();
	std::vector<Point> queryRange(AABB range);
};