#include <iostream>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/io/pcd_io.h>
#include "../../tools/PCLPCDViewer.h"
#include <pcl/visualization/pcl_visualizer.h>
#include <thread>

using namespace std::literals::chrono_literals;

int main()
{
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloudIntensity (new pcl::PointCloud<pcl::PointXYZI>);
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZI>);

    // Open PCD file
    if (pcl::io::loadPCDFile<pcl::PointXYZI>("../../data/room.pcd", *cloudIntensity) == -1)
    {
        std::cout << "Failed to open pcd file" << std::endl;
        return -1;
    }

    // Create the filtering object
    pcl::PassThrough<pcl::PointXYZI> pass;
    pass.setInputCloud(cloudIntensity);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.0, 1.0);
    pass.filter(*cloud_filtered);

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudIntensityRGB (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudFilteredRGB (new pcl::PointCloud<pcl::PointXYZRGB>);

    CloudIntensityToRGB(cloudIntensity, cloudIntensityRGB);
    CloudIntensityToRGB(cloud_filtered, cloudFilteredRGB);

    pcl::visualization::PCLVisualizer::Ptr viewer;
    viewer = rgbVis(cloudIntensityRGB);
    pcl::visualization::PCLVisualizer::Ptr viewer1;
    viewer1 = rgbVis(cloudFilteredRGB);

    while (!viewer->wasStopped()
            && !viewer1->wasStopped())
    {
        viewer->spinOnce(100);
        viewer1->spinOnce(100);
        std::this_thread::sleep_for(100ms);
    }

    return 0;
}

