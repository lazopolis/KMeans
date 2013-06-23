/** testing UserInterface.*:
 *
 * Achilleas Lazopoulos, lazopoli@phys.ethz.ch
 */

#include <iostream>
#include <cmath>
#include "boost/unordered_map.hpp"
#include "kmeans.h"

using namespace std;

#include "gtest/gtest.h"


void  giveRandPoints(vector<DataPoint>& res,int N,int D)
{
     srand (time_t(NULL));
     for (int i=0;i<N;++i)
          {
          DataPoint curp;
          for (int j=0;j<D;++j)
               {
               curp.coords.push_back(double(rand()) / double(RAND_MAX));
               }
          curp.weight=1.0;//(-1.0 + 2.0 * double(rand()) / double(RAND_MAX)) * 100.0;
          res.push_back(curp);
          
          }
}

TEST(kmeans_test,initial)
{
     int dim = 2;
     int N =1000;
     int clust_num = 9;
     vector<DataPoint> all_points;
     giveRandPoints(all_points,N, dim);
     Kmeans my_kmeans(clust_num,all_points);
     my_kmeans.perform(1e-15);
     my_kmeans.print();
     EXPECT_EQ(my_kmeans.totalWeight(),N);
}



int main(int argc, char**argv)
{
    ::testing::InitGoogleTest(&argc, argv);
     
     return  RUN_ALL_TESTS();
     
     return 0;
}
