#ifndef CLUSTER_H
#define CLUSTER_H
#include <string>
#include <vector>

typedef unsigned int uint;

struct DataPoint {
    std::vector<double> coords;
    double weight;

    DataPoint(const std::vector<double> & ,double);
    DataPoint(const std::string, const uint);
    DataPoint() {};
    std::string print();
};

class Cluster {
public:
    Cluster(const DataPoint &);

private:
    std::vector<DataPoint> _points;
    DataPoint _centroid;

public:
    void updateCentroid();
    void setCentroid(const DataPoint&);
    DataPoint getCentroid();
    void push(const DataPoint &);
    void clear();
    double loss();
};

#endif // CLUSTER_H
