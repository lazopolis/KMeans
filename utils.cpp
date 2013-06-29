#include <cassert>
#include <cmath>
#include "utils.h"

double euclidDistance(const DataPoint &p1, const DataPoint &p2)
{
    assert(p1.coords.size() == p2.coords.size());

    double res = 0;
    for (int i=0; i<p1.coords.size(); ++i)
        res += pow(p1.coords[i] - p2.coords[i], 2.0);

    return res;
}

bool evaluateCond(const std::vector<DataPoint> &old_centroids,
                  const std::vector<DataPoint> &new_centroids,
                  double error)
{
    assert(old_centroids.size() == new_centroids.size());

    for (int i=0; i<old_centroids.size(); ++i)
        if (sqrt(euclidDistance(old_centroids[i], new_centroids[i])) >= error)
            return false;
    return true;
}
