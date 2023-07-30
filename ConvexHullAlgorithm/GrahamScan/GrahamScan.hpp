#pragma once
#include <stack>
#include <cfloat>
#include <vector>
#include <algorithm>
#include <stdexcept>

class GrahamScan
{
public:
	using Point = typename std::pair<float, float>;
	static std::vector<Point> convexHull(std::vector<Point>& points);
private:
	static void MoveInitialPoint(std::vector<Point>& points);
	static float cross(const Point& p1, const Point& p2);
	static float cross(const Point& p1, const Point& p2, const Point& origin1, const Point& origin2);
	static float distance(const Point& p);
	static bool compare(const Point& p1, const Point& p2);
	static void sortByAngle(std::vector<Point>& points, Point origin);
};

