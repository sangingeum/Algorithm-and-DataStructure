#include "GrahamScan.hpp"
// O(nlog(n))
// Find the points that form the convex hull of the given points using Graham's scan algorithm 
std::vector<typename GrahamScan::Point> GrahamScan::convexHull(std::vector<Point>& points) {
	if (points.size() < 3)
		throw std::invalid_argument("points.size() should be greater than or equal to 3");

	// Place the bottom most, left most point to the front of the vector
	MoveInitialPoint(points);
	Point origin = points[0];
	// Sort the other points by angle with respect to the origin
	sortByAngle(points, origin);
	// Make a stack to store convex hull points 
	std::stack<Point> hull;
	hull.push(origin);
	hull.push(points[1]);

	size_t size = points.size();
	for (size_t i = 2; i < size; ++i) {
		Point next = points[i];
		Point top = hull.top(); hull.pop();
		// Remove points that make a clock-wise rotation
		while (!hull.empty() && cross(top, next, hull.top(), top) <= 0) {
			top = hull.top(); hull.pop();
		}
		hull.push(top);
		hull.push(next);
	}
	// Convert the stack to a vector and reverse it
	std::vector<Point> result;
	result.reserve(hull.size());
	while (!hull.empty()) { result.push_back(std::move(hull.top())); hull.pop(); }
	std::reverse(result.begin(), result.end());
	return result;
}

// Place the bottom most, left most point to the front of the vector
void GrahamScan::MoveInitialPoint(std::vector<Point>& points) {
	size_t size = points.size();
	for (size_t i = 1; i < size; ++i) {
		const auto& cur = points[i];
		const auto& front = points[0];
		if (front.second > cur.second)
			std::swap(points[0], points[i]);
		else if (front.second == cur.second)
			if (front.first > cur.first)
				std::swap(points[0], points[i]);
	}
}
float GrahamScan::cross(const Point& p1, const Point& p2) {
	return (p1.first * p2.second) - (p1.second * p2.first);
}
float GrahamScan::cross(const Point& p1, const Point& p2, const Point& origin1, const Point& origin2) {
	return cross({ p1.first - origin1.first,  p1.second - origin1.second },
		{ p2.first - origin2.first,  p2.second - origin2.second });
}
float GrahamScan::distance(const Point& p) {
	return p.first * p.first + p.second * p.second;
}
bool GrahamScan::compare(const Point& p1, const Point& p2) {
	float ccw = cross(p1, p2);
	// This line of code is very important to deal with collinear points
	if (abs(ccw) < FLT_EPSILON)
		return distance(p1) < distance(p2);
	return ccw > 0;
}
void GrahamScan::sortByAngle(std::vector<Point>& points, Point origin) {
	std::sort(points.begin() + 1, points.end(),
		[&origin](const Point& p1, const Point& p2) {
			return compare({ p1.first - origin.first,  p1.second - origin.second },
				{ p2.first - origin.first,  p2.second - origin.second });
		});
}