#ifndef KMEANS_H
#define KMEANS_H
#include <vector>
#include <string>
#include <inttypes.h>
#include "cluster.h"

using namespace std;

class Kmeans {
public:
    Kmeans(uint number_of_cluster, const vector<DataPoint>&);
    Kmeans(uint number_of_cluster, uint num_of_dimensions, std::string);

private:
    std::vector<DataPoint> _data_set;
    std::vector<Cluster> _clusters;
    uint _number_of_clusters;

public:
    void perform(double);
    double totalWeight();
    void print();

private:
    int _parsePoints(std::string, uint);
    void _initialize();
    void _performIter();
    int _findNearestCluster(const DataPoint&);
    void _updateCentroids();
    void _clearClusters();
    std::vector<DataPoint> _getCentroids();
};

#endif
