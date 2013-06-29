#ifndef UTILS_H
#define UTILS_H
#include "cluster.h"

double euclidDistance(const DataPoint&, const DataPoint&);
bool evaluateCond(const std::vector<DataPoint>&,
                  const std::vector<DataPoint>&,
                  double);

#endif // UTILS_H
