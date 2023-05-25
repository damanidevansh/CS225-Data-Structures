#include <iterator>
#include <cmath>

#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

using namespace std;
using namespace cs225;

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {
  tolerance_ = tolerance; 
	png_ = png; 
	start_ = start;
	traversal.push(start);
	//BeenTo = new vector<vector<bool>>;
  BeenTo.resize(png_.width());
  for (unsigned i = 0; i < BeenTo.size(); i++) {
    BeenTo[i].resize(png_.height());
      for (unsigned j = 0; j < BeenTo[i].size(); j++) {
        BeenTo[i][j] = false;
      }
  }
  BeenTo[start.x][start.y] = true;
}

DFS::~DFS() {
    
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  	DFS * dfs = new DFS(png_, start_, tolerance_);
  	return ImageTraversal::Iterator(*dfs, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  	return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  	traversal.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
	Point top = traversal.top();
	traversal.pop();
	return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  	return traversal.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  	return traversal.empty();
}

bool DFS::getVisited(unsigned x, unsigned y) {
    return BeenTo[x][y];
}
void DFS::setVisit(unsigned x, unsigned y) {
    BeenTo[x][y] = true;
}
PNG * DFS::passPng() {
    return &png_;
}
double DFS::getTolerance() {
  return tolerance_;
}