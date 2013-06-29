#include <iostream>
#include <sstream>
#include <cstdlib>
#include "cluster.h"
#include "utils.h"

DataPoint::DataPoint(const std::vector<double> &vv, double w)
    : coords(vv), weight(w)
{}

DataPoint::DataPoint(const std::string line, const uint num_of_dimensions)
{
    std::istringstream iss(line);
    std::string buffer;                  //coordinates
    for (uint i=0; i<num_of_dimensions; ++i) {
        std::getline(iss, buffer, ' ');
        coords.push_back(atof(buffer.c_str()));
    }
    std::getline(iss, buffer, ' ');      //weight
    weight = atof(buffer.c_str());
}

std::string DataPoint::print()
{
    std::stringstream s;
    for (uint i=0; i<coords.size(); ++i)
        s << coords[i] << " ";
    s << "weight: " << weight;
    return s.str();
}

Cluster::Cluster(const DataPoint& centroid): _centroid(centroid)
{}

void Cluster::updateCentroid()
{
    std::vector<double> zero(_centroid.coords.size(),0.0);
    DataPoint new_centroid(zero,0.0);
    for (int j=0; j<_points.size(); ++j) {
        for (int i=0; i<_points[j].coords.size(); ++i) {
            new_centroid.coords[i] += _points[j].coords[i] / (double)_points.size();
        }
        new_centroid.weight += _points[j].weight;
    }
    _centroid = new_centroid;
}

DataPoint Cluster::getCentroid()
{
    return _centroid;
}

void Cluster::push(const DataPoint &p)
{
    _points.push_back(p);
}

void Cluster::clear()
{
    _points.clear();
}

double Cluster::loss()
{
    double loss = 0.;
    for (int i=0; i<_points.size(); ++i)
        loss += euclidDistance(_points[i], _centroid);
    return loss;
}
