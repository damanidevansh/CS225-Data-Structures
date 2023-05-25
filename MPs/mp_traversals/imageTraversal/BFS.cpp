#include <iterator>
#include <cmath>

#include <queue>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace std;
using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
    tolerance_ = tolerance; 
    png_ = png; 
    start_ = start;
    traversal.push(start);
    //BeenTo = vector<vector<bool>>;
    BeenTo.resize(png_.width());
    unsigned i = 0;
    while (i < BeenTo.size()) {
        BeenTo[i].resize(png_.height());
        for (unsigned j = 0; j < BeenTo[i].size(); j++) {
            BeenTo[i][j] = false;
        }
        i++;
    }
    BeenTo[start.x][start.y] = true;
}

BFS::~BFS() {
    
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
    BFS * BFSNew = new BFS(png_, start_, tolerance_);
    return ImageTraversal::Iterator(*BFSNew, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
    return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
    traversal.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
    Point head = traversal.front();
    traversal.pop();
    return head;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
    return traversal.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
    return traversal.empty();
}

bool BFS::getVisited(unsigned x, unsigned y) {
    return BeenTo[x][y];
}
void BFS::setVisit(unsigned x, unsigned y) {
    BeenTo[x][y] = true;
}
PNG * BFS::passPng() {
    return &png_;
}
double BFS::getTolerance() {
    return tolerance_;
}