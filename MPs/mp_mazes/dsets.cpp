/* Your code here! */
#include "dsets.h"

using namespace std;

void DisjointSets::addelements (int num) {
    int i = 0;
    while (i < num) {
        elements.push_back(-1);
        i++;
    }
}

int DisjointSets::find (int elem) {
    if (elements[elem] < 0) {return elem;}
    else {
        elements[elem] = find(elements[elem]);
        return (elements[elem]);
    }
}

void DisjointSets::setunion (int a, int b) {
    while (elements[a] >= 0) {
        a = elements[a];
    }
    while (elements[b] >= 0) {
        b = elements[b];
    }
    int totalsize = elements[a] + elements[b];
    if (elements[a] <= elements[b]) {
        elements[b] = a;
        elements[a] = totalsize;
    }
    else {
        elements[a] = b;
        elements[b] = totalsize;
    }
}

int DisjointSets::size (int elem) {
    while (elements[elem]>= 0) {elem = elements[elem];}
    return (elements[elem] * -1);
}