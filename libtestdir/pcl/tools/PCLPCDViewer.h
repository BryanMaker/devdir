#ifndef PCLPCDVIEWER
#define PCLPCDVIEWER

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

pcl::visualization::PCLVisualizer::Ptr simpleVis(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud);
pcl::visualization::PCLVisualizer::Ptr rgbVis(pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr cloud);

void CloudIntensityToRGB(pcl::PointCloud<pcl::PointXYZI>::Ptr cloudIntensity, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudRGB);
#endif
