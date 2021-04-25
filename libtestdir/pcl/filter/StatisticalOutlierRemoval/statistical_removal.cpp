#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h> // 统计离群去除过滤器
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

    // Create the filtering object
    pcl::StatisticalOutlierRemoval<pcl::PointXYZI> sor;
    sor.setInputCloud(cloudIntensity);
    sor.setMeanK(50); // 要分析的近邻点数
    sor.setStddevMulThresh(1.0); // 标准倍数设置为1
    sor.filter(*cloud_filtered);

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudIntensityRGB (new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudFilteredRGB (new pcl::PointCloud<pcl::PointXYZRGB>);

    CloudIntensityToRGB(cloudIntensity, cloudIntensityRGB);
    CloudIntensityToRGB(cloud_filtered, cloudFilteredRGB);

    pcl::visualization::PCLVisualizer::Ptr viewer;
    viewer = rgbVis(cloudIntensityRGB);
    pcl::visualization::PCLVisualizer::Ptr viewer1;
    viewer1 = rgbVis(cloudFilteredRGB);

    while (!viewer->wasStopped()
            && !viewer->wasStopped())
    {
        viewer->spinOnce(100);
        viewer1->spinOnce(100);
        std::this_thread::sleep_for(100ms);
    }

    return 0;
}
