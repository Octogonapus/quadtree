#include <D:\Documents\C++_Programs\eigen\Eigen\Dense>
#include "quadtree.h"

Quadtree::Quadtree(const AABB& aabb):
	m_boundary(aabb)
{
	m_nw = nullptr;
	m_ne = nullptr;
	m_sw = nullptr;
	m_se = nullptr;

	m_objects = std::vector<Point>();
}

Quadtree::~Quadtree()
{
	delete m_nw;
	delete m_ne;
	delete m_sw;
	delete m_se;
}

bool Quadtree::insert(Point p)
{
	if (!m_boundary.intersectWithPoint(p))
		return false;

	if (m_objects.size() < m_capacity)
	{
		m_objects.push_back(p);
		return true;
	}

	if (m_nw == nullptr)
		subdivide();

	if (m_nw->insert(p))
		return true;

	if (m_ne->insert(p))
		return true;

	if (m_sw->insert(p))
		return true;

	if (m_se->insert(p))
		return true;

	return false;
}

void Quadtree::subdivide()
{
	Point qSize(m_boundary.getCenter()[0], m_boundary.getCenter()[1]);

	Point qCenter(m_boundary.getCenter()[0] - qSize.getX(), m_boundary.getCenter()[1] - qSize.getY());
	m_nw = new Quadtree(AABB(Eigen::Vector2f(qCenter.getX(), qCenter.getY()), Eigen::Vector2f(qSize.getX(), qSize.getY())));

	qCenter = Point(m_boundary.getCenter()[0] + qSize.getX(), m_boundary.getCenter()[1] - qSize.getY());
	m_ne = new Quadtree(AABB(Eigen::Vector2f(qCenter.getX(), qCenter.getY()), Eigen::Vector2f(qSize.getX(), qSize.getY())));

	qCenter = Point(m_boundary.getCenter()[0] - qSize.getX(), m_boundary.getCenter()[1] + qSize.getY());
	m_sw = new Quadtree(AABB(Eigen::Vector2f(qCenter.getX(), qCenter.getY()), Eigen::Vector2f(qSize.getX(), qSize.getY())));

	qCenter = Point(m_boundary.getCenter()[0] + qSize.getX(), m_boundary.getCenter()[1] + qSize.getY());
	m_se = new Quadtree(AABB(Eigen::Vector2f(qCenter.getX(), qCenter.getY()), Eigen::Vector2f(qSize.getX(), qSize.getY())));
}

std::vector<Point> Quadtree::queryRange(AABB range)
{
	std::vector<Point> inRange = std::vector<Point>();

	if (!m_boundary.intersectWithAABB(range))
		return inRange;

	for(auto&& object : m_objects)
		if (range.intersectWithPoint(object))
			inRange.push_back(object);

	if (m_nw == nullptr)
		return inRange;

	std::vector<Point> temp = m_nw->queryRange(range);
    inRange.insert(inRange.end(), temp.begin(), temp.end());

    temp = m_ne->queryRange(range);
    inRange.insert(inRange.end(), temp.begin(), temp.end());

    temp = m_sw->queryRange(range);
    inRange.insert(inRange.end(), temp.begin(), temp.end());

    temp = m_se->queryRange(range);
    inRange.insert(inRange.end(), temp.begin(), temp.end());

    return inRange;
}