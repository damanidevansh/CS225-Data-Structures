/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
	if (curDim < 0 || curDim >= Dim) {return false;}
    if(first[curDim] == second[curDim]) {return first < second;}
    return (first[curDim] < second[curDim]);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double TCb = 0.0, TP = 0.0;
    for(int i=0; i<Dim;i++){
       	TCb += ((target[i]-currentBest[i])*(target[i]-currentBest[i]));
       	TP += ((target[i]-potential[i])*(target[i]-potential[i]));
    }
    if(TCb == TP) {return potential < currentBest;}
    return (TP < TCb);
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>>& list, int d, unsigned left, unsigned right, unsigned pivotIndex){
  	Point<Dim> Value = list[pivotIndex];
  	Point<Dim> temp = list[pivotIndex];
  	list[pivotIndex] = list[right];
  	list[right] = temp;
  	unsigned storeIndex = left;
  	for(unsigned i = left; i < right; i++){
    	if(smallerDimVal(list[i],Value,d)){
      		temp = list[storeIndex];
      		list[storeIndex] = list[i];
      		list[i] = temp;
      		storeIndex++;
    	}
  	}
  	temp = list[storeIndex];
  	list[storeIndex] = list[right];
  	list[right] = temp;
  	return storeIndex;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::quickSelect(vector<Point<Dim>>& list, int d, unsigned left, unsigned right, unsigned k){
  	if(left == right) return list[left];
  	unsigned pivotIndex = k;
  	pivotIndex = partition(list,d,left,right,pivotIndex);
  	if(k==pivotIndex) return list[k];
  	else if(k < pivotIndex) 
    	return quickSelect(list, d, left, pivotIndex-1, k);
  	else return quickSelect(list, d, pivotIndex+1, right, k);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::makeTreehelper(vector<Point<Dim>>& values, int d, unsigned left, unsigned right){
  	if(values.empty() || left < 0 || right >= values.size() || right < 0 || left >= values.size()) {return NULL;}
  	if(left > right) {return NULL;}
  	unsigned median = (left + right)/2;
  	KDTreeNode* subRoot = new KDTreeNode(quickSelect(values,d%Dim,left,right,median));
  	size += 1;
  	d++;
  	subRoot->left = makeTreehelper(values,d,left,median-1);
  	subRoot->right = makeTreehelper(values,d,median+1,right);
 	return subRoot;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    size = 0;
    vector<Point<Dim>> values;
    values.assign(newPoints.begin(), newPoints.end());
    root = makeTreehelper(values, 0, 0, values.size()-1);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
	copierhelper(this->root, other.root);
	size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  	if (this != NULL) {deletify(root);}
  	copierhelper(this->root, rhs.root);
  	size = rhs.size;
  	return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  	deletify(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const {
    return findNearestNeighbor(root, query, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode * subroot, const Point<Dim>& query, int d) const {
	Point<Dim> currentBest = subroot->point;
	bool flag;
	if (subroot->left == NULL && subroot->right == NULL) return subroot->point;
	if (smallerDimVal(query, subroot->point, d)) {
		if (subroot->left == NULL)
			currentBest = findNearestNeighbor(subroot->right, query, (d + 1) % Dim);
		else
			currentBest = findNearestNeighbor(subroot->left, query, (d + 1) % Dim);
		flag = true;
	}

	else {
		if (subroot->right == NULL) {
			currentBest = findNearestNeighbor(subroot->left, query, (d + 1) % Dim);
		}
		else {
			currentBest = findNearestNeighbor(subroot->right, query, (d + 1) % Dim);
		}
		flag = false;
	}
	
	if (shouldReplace(query, currentBest, subroot->point)) currentBest = subroot->point;
	

	double radius = 0;
	for (int i = 0; i < Dim; i++) {
		radius += (query[i] - currentBest[i]) * (query[i] - currentBest[i]);
	}
	double split_distance = subroot->point[d] - query[d];
	split_distance = split_distance * split_distance;

	if (split_distance <= radius) {
		KDTreeNode * need_to_check = flag ? subroot->right : subroot->left;
		if (need_to_check != NULL) {
			Point<Dim> otherBest = findNearestNeighbor(need_to_check, query, (d + 1) % Dim);
			if (shouldReplace(query, currentBest, otherBest)) {currentBest = otherBest;}
		}
	}
	return currentBest;
}

template <int Dim>
void KDTree<Dim>::deletify(KDTreeNode * subroot) {
	if (subroot == NULL) {return;}
	if (subroot->left != NULL) {deletify(subroot->left);}
	if (subroot->right != NULL) {deletify(subroot->right);}
	delete subroot;
	subroot = NULL;
}

template <int Dim>
void KDTree<Dim>::copierhelper(KDTreeNode * subroot, KDTreeNode * othersubroot) {
	subroot = new KDTreeNode();
	subroot->point = othersubroot->point;
	copierhelper(subroot->left, othersubroot->left);
	copierhelper(subroot->right, othersubroot->right);
}