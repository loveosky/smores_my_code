/*
    Copyright (c) 2014, <copyright holder> <email>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef PCL_OCTREE_IMPL_H
#define PCL_OCTREE_IMPL_H

#include <pcl/common/common.h>
#include <pcl/octree/octree.h>
#include <pcl/filters/voxel_grid.h>
#include <boost/signals2.hpp>
#include <octomap/octomap.h>
#include <octomap/OcTree.h>

class PCL_OCTREE_IMPL
{

public:
  PCL_OCTREE_IMPL(int width, int height);
  virtual ~PCL_OCTREE_IMPL();
  void AddPoint(double x, double y, double z);
  void AddScan(double* xPts, double* yPts, double* zPts, int nPoints, double poseX, double poseY, double poseZ);
  void DownSample(float voxelResolution);
  std::vector<pcl::PointXYZ> GetPoints();
  std::vector<octomap::point3d> GetVoxels(int max_depth, float &cubeSize);
  boost::signals2::signal<void ()> ocGridUpdatedSignal;

private:
  pcl::PointCloud<pcl::PointXYZ>::Ptr pCloud;
  pcl::VoxelGrid<pcl::PointXYZ> sor;
  pcl::octree::OctreePointCloud<pcl::PointXYZ> *octree;
  
	octomap::OcTree *octoMapTree;
};

#endif // PCL_OCTREE_IMPL_H
