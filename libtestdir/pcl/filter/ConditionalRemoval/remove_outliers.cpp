#include <iostream>
#include <pcl/point_types.h>
#include <pcl/filters/radius_outlier_removal.h> // 半径离群去除过滤器
#include <pcl/filters/conditional_removal.h> // 条件去除过滤器
#include <thread>
#include "../../tools/PCLPCDViewer.h"

using namespace std::literals::chrono_literals;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "please specify command line arg '-r' or '-c'" << std::endl;
        return 1;
    }
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloudIntensity (new pcl::PointCloud<pcl::PointXYZI>);
    pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZI>);

    // Open PCD file
    if (pcl::io::loadPCDFile<pcl::PointXYZI>("../../data/room.pcd", *cloudIntensity) == -1)
    {
        std::cout << "Failed to open pcd file" << std::endl;
        return -1;
    }

    if (strcmp(argv[1], "-r") == 0)
    {
        // 半径离群去除
        pcl::RadiusOutlierRemoval<pcl::PointXYZI> outrem;
        // Optional
        outrem.setInputCloud(cloudIntensity);
        outrem.setRadiusSearch(0.01); // 设置搜索半径
        outrem.setMinNeighborsInRadius(10); // 在半径内设置最小近邻阈值
        outrem.setKeepOrganized(false); // 保持有为组织点云
        outrem.filter(*cloud_filtered);
    }
    else if (strcmp(argv[1], "-c") == 0)
    {
        // 过滤器条件对象
        pcl::ConditionAnd<pcl::PointXYZI>::Ptr range_cond(new pcl::ConditionAnd<pcl::PointXYZI>);
        // 添加条件 Z轴大于0
        range_cond->addComparison(pcl::FieldComparison<pcl::PointXYZI>::ConstPtr (new pcl::FieldComparison<pcl::PointXYZI> ("z", pcl::ComparisonOps::GT, 0.0)));
        // 添加条件 Z轴小于0.8
        range_cond->addComparison(pcl::FieldComparison<pcl::PointXYZI>::ConstPtr (new pcl::FieldComparison<pcl::PointXYZI> ("z", pcl::ComparisonOps::LT, 0.8)));
        // 条件去除过滤器
        pcl::ConditionalRemoval<pcl::PointXYZI> condrem;
        condrem.setCondition(range_cond);
        condrem.setInputCloud(cloudIntensity);
        condrem.setKeepOrganized(true); // 保持有为组织点云
        condrem.filter(*cloud_filtered);
    }
    else 
    {
        std::cerr << "please specify command line arg '-r' or '-c'" << std::endl;
        return 1;
    }

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
