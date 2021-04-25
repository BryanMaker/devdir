#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/ModelCoefficients.h> // 模型系数
#include <pcl/filters/project_inliers.h>
#include <thread>
#include "../../tools/PCLPCDViewer.h"

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

    // Create a set of planar confficients with X=Y=0, Z=1
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients());
    // ax+by+cz+d=0
    coefficients->values.resize(4);
    coefficients->values[0] = 0;
    coefficients->values[1] = 0;
    coefficients->values[2] = 1.0;
    coefficients->values[3] = 0;
    
    // Create the filtering object
    pcl::ProjectInliers<pcl::PointXYZI> proj;
    proj.setModelType(pcl::SACMODEL_PLANE);
    proj.setInputCloud(cloudIntensity);
    proj.setModelCoefficients(coefficients);
    proj.filter(*cloud_filtered);

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
