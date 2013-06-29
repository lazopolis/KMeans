#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include "kmeans.h"
#include "utils.h"

Kmeans::Kmeans(uint number_of_cluster,
               const std::vector<DataPoint> &data_set)
    : _data_set(data_set),
      _number_of_clusters(number_of_cluster)
{
    _initialize();

}

Kmeans::Kmeans(uint number_of_cluster, uint num_of_dimensions,
               std::string filename)
    : _number_of_clusters(number_of_cluster)
{
    _parsePoints(filename, num_of_dimensions);
    _initialize();
}

void Kmeans::perform(double error)
{
    int counter=0;
    bool done = true;
    do {
        std::cout << "\niteration " << ++counter;
        vector<DataPoint> old_centroids = _getCentroids();
        _performIter();
        vector<DataPoint> new_centroids = _getCentroids();
        done = evaluateCond(old_centroids, new_centroids, error);
    } while (!done);

}

double Kmeans::totalWeight()
{
    double res=0;
    for (int i=0; i<_clusters.size(); ++i)
        res += _clusters[i].getCentroid().weight;

    return res;
}

void Kmeans::print()
{
    for (int i=0; i<_clusters.size(); ++i)
       std::cout << "\n\n" << _clusters[i].getCentroid().print() << std::endl;
}

double Kmeans::overallLoss()
{
    double overall_loss = 0.;
    for (int i=0; i<_clusters.size(); ++i)
        overall_loss += _clusters[i].loss();
    return overall_loss;
}

int
Kmeans::_parsePoints(std::string filename, uint num_of_dimensions)
{
    std::string line;

    std::ifstream infile(filename.c_str());
    if (!infile.is_open()) {
        std::cerr << "_parsePoints(string): open(filename)" << std::endl;
        return -1;
    }
    while(std::getline(infile, line)) {
        if (line.find('#') != std::string::npos) {    //bypass comments
            continue;
        }
        try {
            DataPoint point(line, num_of_dimensions);
            _data_set.push_back(point);
        } catch (...) {
            infile.close();
            std::cerr << "_parsePoints(string): DataPoint(char*)" << std::endl;
            return -2;
        }
    }
    infile.close();
    return 0;
}

void Kmeans::_initialize()
{
    for (size_t i=0; i<_number_of_clusters; ++i) {
        int centroid_id = rand() % (int)_data_set.size();
        _clusters.push_back(_data_set[centroid_id]);
    }
}

void Kmeans::_performIter()
{
    _clearClusters();
    for (int i=0; i<_data_set.size(); ++i)
        _clusters[_findNearestCluster(_data_set[i])].push(_data_set[i]);

    _updateCentroids();
}

void Kmeans::_clearClusters()
{
    for (int i=0; i<_clusters.size(); ++i)
        _clusters[i].clear();
}

int Kmeans::_findNearestCluster(const DataPoint &p)
{
    int nearest_cluster_id = -1;
    double nearest_dist = 1e16;
    for (int cluster_id=0; cluster_id<_clusters.size(); ++cluster_id) {
        double cur_dist = euclidDistance(p, _clusters[cluster_id].getCentroid());
        if (cur_dist < nearest_dist) {
            nearest_dist = cur_dist;
            nearest_cluster_id = cluster_id;
        }
    }
    return nearest_cluster_id;
}

void Kmeans::_updateCentroids()
{
    for (int i=0; i<_clusters.size(); ++i)
        _clusters[i].updateCentroid();
}

std::vector<DataPoint> Kmeans::_getCentroids()
{
    std::vector<DataPoint> res;
    for (int i=0; i<_clusters.size(); ++i)
        res.push_back(_clusters[i].getCentroid());

    return res;
}
